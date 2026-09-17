"""Simulation engine — turns a PlantModel into engineering KPIs.

All standard PV design math, in pure NumPy (no AutoCAD, no external services),
so the demo always runs. Each KPI here is what a Requirement in the spec
constrains, so the Validator can line them up 1:1.
"""
from __future__ import annotations

import math
from dataclasses import dataclass, field
from typing import Dict, List

import numpy as np

from .schema import Mounting, PlantModel

# resistivity (ohm.mm^2/m)
RHO_AL = 0.0286
RHO_CU = 0.0175


@dataclass
class SimResult:
    metrics: Dict[str, float]                 # keyed by KNOWN_METRICS
    extras: Dict[str, float] = field(default_factory=dict)
    boq: Dict[str, float] = field(default_factory=dict)
    day_hours: List[float] = field(default_factory=list)
    day_ac_kw: List[float] = field(default_factory=list)

    def m(self, key: str) -> float:
        return self.metrics[key]


def voc_at_temp(voc_stc: float, tc_voc_pct: float, temp_c: float) -> float:
    """Open-circuit voltage at cell temperature (tc negative, so cold => higher V)."""
    return voc_stc * (1.0 + tc_voc_pct / 100.0 * (temp_c - 25.0))


def simulate(m: PlantModel) -> SimResult:
    mod, inv, site, cab = m.module, m.inverter, m.site, m.cable

    # ---- capacity / counts ----
    dc_kw = m.n_modules * mod.wp / 1000.0
    ac_kw = m.n_inverters * inv.ac_kw
    dc_ac = dc_kw / ac_kw if ac_kw else 0.0
    dc_mwp = dc_kw / 1000.0

    # ---- string sizing (cold Voc) ----
    voc_cold = voc_at_temp(mod.voc, mod.temp_coeff_voc, site.min_temp_c)
    string_voc_tmin = m.modules_per_string * voc_cold
    string_vmp_stc = m.modules_per_string * mod.vmp

    # ---- GCR & shading ----
    # collector slope-length = table N-S width; GCR = collector / pitch
    from .synthesize import _load_tables
    tinfo = _load_tables().get(m.table_name, {})
    collector_w = float(tinfo.get("width_m", 4.576))
    gcr = collector_w / m.row_pitch_m if m.row_pitch_m else 1.0

    # simple beam-shading loss proxy: grows with GCR beyond a "free" threshold
    shading_loss = float(np.clip(0.35 * (gcr - 0.30), 0.0, 0.15))

    # ---- energy yield (clear-sky, annualised) ----
    annual_ghi = site.ghi_kwh_m2_day * 365.0                     # kWh/m2/yr
    tilt_gain = 1.0 + 0.004 * m.tilt_deg if m.mounting == Mounting.FIXED_TILT else 1.12
    poa_annual = annual_ghi * tilt_gain                          # kWh/m2/yr on array
    losses = {
        "temperature": 0.08,
        "soiling": 0.03,
        "shading": shading_loss,
        "cable": 0.02,
        "inverter": 0.02,
        "mismatch": 0.02,
    }
    pr = float(np.prod([1.0 - v for v in losses.values()]))
    # clip loss if DC/AC pushes past inverter AC (energy limited)
    clip_loss = float(np.clip((dc_ac - 1.3) * 0.10, 0.0, 0.08))
    pr *= (1.0 - clip_loss)
    specific_yield = poa_annual * pr                            # kWh/kWp/yr

    # ---- cable voltage drop (3-phase) ----
    rho = RHO_CU if cab.copper else RHO_AL
    r_eff = rho / (cab.lt_area_mm2 * max(1, cab.n_parallel))     # ohm/m effective
    vdrop = math.sqrt(3) * cab.lt_current_a * r_eff * cab.lt_length_m
    vdrop_pct = vdrop / cab.lt_voltage_v * 100.0

    # ---- land use ----
    footprint = m.n_tables * float(tinfo.get("length_m", 32.292)) * m.row_pitch_m

    # ---- representative-day AC curve (for plotting) ----
    hours = np.linspace(5, 19, 29)
    day_frac = np.clip(np.sin((hours - 6) / 12 * math.pi), 0, None)
    peak_ac = min(dc_kw * 0.85, ac_kw)                          # midday, with clipping
    day_ac = (day_frac * peak_ac).round(1)

    metrics = {
        "dc_capacity_mwp": round(dc_mwp, 3),
        "dc_ac_ratio": round(dc_ac, 3),
        "string_voc_tmin": round(string_voc_tmin, 1),
        "gcr": round(gcr, 3),
        "row_pitch_m": round(m.row_pitch_m, 3),
        "lt_cable_drop_pct": round(vdrop_pct, 2),
        "specific_yield_kwh_kwp": round(specific_yield, 0),
        "site_area_used_m2": round(footprint, 0),
    }
    extras = {
        "dc_kw": round(dc_kw, 1),
        "ac_kw": round(ac_kw, 1),
        "voc_cold_per_module": round(voc_cold, 2),
        "string_vmp_stc": round(string_vmp_stc, 1),
        "pr": round(pr, 3),
        "poa_annual": round(poa_annual, 0),
        "shading_loss_pct": round(shading_loss * 100, 1),
        "n_modules": m.n_modules,
        "n_strings": m.n_strings,
        "n_inverters": m.n_inverters,
        "modules_per_string": m.modules_per_string,
    }
    boq = {
        "MMS Tables": m.n_tables,
        "Piles": m.n_piles,
        "Modules": m.n_modules,
        "Strings": m.n_strings,
        "Inverters": m.n_inverters,
        "LT cable (m, est.)": round(m.n_inverters * cab.lt_length_m * cab.n_parallel, 0),
    }
    return SimResult(metrics=metrics, extras=extras, boq=boq,
                     day_hours=[round(h, 2) for h in hours.tolist()],
                     day_ac_kw=day_ac.tolist())
