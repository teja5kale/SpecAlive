"""Model synthesizer: RequirementSet + hints -> PlantModel.

This is where requirements become a concrete, parameterized system model.
It maps design intent onto the CAD tool's own block concepts (MMS tables,
strings, inverter groups, piles).

Note: the initial string-sizing rule here is deliberately *naive* (it sizes on
nominal Voc at STC, ignoring the cold-temperature Voc rise). The Validator
catches the resulting REQ-VOC failure and the Refiner corrects it — this is the
requirements-driven loop the hackathon is about.
"""
from __future__ import annotations

import json
import math
import os
from typing import Dict

from .schema import (CableSpec, InverterSpec, ModuleSpec, Mounting, PlantModel,
                     RequirementSet, SiteSpec)

_DATA = os.path.join(os.path.dirname(os.path.dirname(__file__)), "data", "tables.json")


def _load_tables() -> Dict:
    with open(_DATA, "r", encoding="utf-8") as f:
        return json.load(f)["tables"]


def _pick_table(mounting: Mounting) -> str:
    tables = _load_tables()
    for name, t in tables.items():
        if t["type"] == mounting.value:
            return name
    return next(iter(tables))


def synthesize(reqs: RequirementSet, hints: Dict[str, float],
               naive_string_sizing: bool = True) -> PlantModel:
    """Build a PlantModel from requirements + hints.

    naive_string_sizing=True  -> size strings on nameplate Voc (ignores the
        cold-temperature Voc rise). The initial model then FAILS the Voc
        requirement and the refiner corrects it -> the "catch & fix" demo.
    naive_string_sizing=False -> size strings on cold Voc from the start, so
        the model is correct on the first pass (no refine needed).
    """
    h = hints
    mounting = Mounting.TRACKER if h.get("mounting", 0.0) >= 0.5 else Mounting.FIXED_TILT

    module = ModuleSpec(
        wp=h.get("wp", 545.0),
        voc=h.get("voc", 49.5),
        vmp=h.get("vmp", 41.8),
        isc=h.get("isc", 13.90),
        imp=h.get("imp", 13.04),
        temp_coeff_voc=h.get("temp_coeff_voc", -0.27),
        length_m=h.get("mod_length_m", 2.279),
        width_m=h.get("mod_width_m", 1.134),
    )
    inverter = InverterSpec(
        ac_kw=h.get("inverter_ac_kw", 3800.0),
        mppt_low_v=h.get("mppt_low_v", 875.0),
        mppt_high_v=h.get("mppt_high_v", 1325.0),
    )
    site = SiteSpec(
        latitude=h.get("latitude", 23.85),
        min_temp_c=h.get("min_temp_c", 5.0),
        ghi_kwh_m2_day=h.get("ghi_kwh_m2_day", 5.6),
        area_m2=h.get("area_m2", 40000.0),
    )

    # target DC/AC: centre of the required window if present, else 1.25
    r_dcac = reqs.by_metric("dc_ac_ratio")
    if r_dcac and r_dcac.is_range():
        lo, hi = r_dcac.target  # type: ignore[misc]
        target_dc_ac = round((lo + hi) / 2, 3)
    else:
        target_dc_ac = 1.25

    # Pitch: satisfy both the minimum-pitch requirement AND the GCR cap.
    # collector slope-length = the MMS table's N-S width (from tables.json).
    tinfo = _load_tables().get(_pick_table(mounting), {})
    collector_w = float(tinfo.get("width_m", 4.576))
    r_pitch = reqs.by_metric("row_pitch_m")
    min_pitch = float(r_pitch.target) if r_pitch else 6.0  # type: ignore[arg-type]
    r_gcr = reqs.by_metric("gcr")
    gcr_cap = float(r_gcr.target) if r_gcr else 0.45  # type: ignore[arg-type]
    pitch_for_gcr = collector_w / gcr_cap
    row_pitch = round(max(min_pitch, pitch_for_gcr), 3)

    # String sizing: naive (nameplate Voc) vs cold-aware (Voc at min temp).
    if naive_string_sizing:
        mps = int(inverter.max_system_v // module.voc)
    else:
        from .simulate import voc_at_temp
        voc_cold = voc_at_temp(module.voc, module.temp_coeff_voc, site.min_temp_c)
        mps = int(inverter.max_system_v // voc_cold)

    model = PlantModel(
        project=reqs.project,
        capacity_mwp_target=h.get("capacity_mwp_target", 5.0),
        mounting=mounting,
        tilt_deg=h.get("tilt_deg", 25.0),
        row_pitch_m=row_pitch,
        module=module,
        inverter=inverter,
        cable=CableSpec(),
        site=site,
        modules_per_string=mps,
        target_dc_ac=target_dc_ac,
        table_name=_pick_table(mounting),
    )
    return _fill_derived(model)


def _fill_derived(m: PlantModel) -> PlantModel:
    """Recompute all n_* counts from the current design decisions."""
    tables = _load_tables()
    tinfo = tables.get(m.table_name, next(iter(tables.values())))

    # modules per table from geometry:
    #   along length: portrait modules side-by-side (module.width_m each)
    #   across width: how many module-lengths fit the table's slope width (2P => 2)
    along = max(1, int(tinfo["length_m"] // m.module.width_m))
    rows = max(1, round(tinfo["width_m"] / m.module.length_m))
    modules_per_table = along * rows
    m.modules_per_table = modules_per_table

    target_wp = m.capacity_mwp_target * 1e6
    m.n_modules = int(round(target_wp / m.module.wp))
    m.n_strings = max(1, round(m.n_modules / m.modules_per_string))
    # keep module count consistent with whole strings
    m.n_modules = m.n_strings * m.modules_per_string

    dc_kw = m.n_modules * m.module.wp / 1000.0
    # central-inverter sizing: round to nearest whole unit toward the target
    # DC/AC (don't add a full inverter for a fractional overshoot).
    m.n_inverters = max(1, round(dc_kw / (m.inverter.ac_kw * m.target_dc_ac)))

    m.n_tables = math.ceil(m.n_modules / modules_per_table)
    m.n_piles = m.n_tables * int(tinfo["piles"])
    return m


def refill(m: PlantModel) -> PlantModel:
    """Public helper used by the refiner after changing a design decision."""
    return _fill_derived(m)
