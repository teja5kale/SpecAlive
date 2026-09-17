"""Refiner — adjust design decisions to satisfy failing requirements, re-simulate.

Each rule targets one failing metric with a physically-correct correction, then
the whole model is re-derived and re-validated. Loops until all pass or no rule
makes progress (bounded iterations).
"""
from __future__ import annotations

import math
from dataclasses import dataclass
from typing import List

from .schema import PlantModel, RequirementSet
from .simulate import simulate, voc_at_temp
from .synthesize import refill
from .validate import ValidationReport, validate


@dataclass
class RefineStep:
    iteration: int
    action: str
    fixed_metric: str


def refine(model: PlantModel, reqs: RequirementSet, max_iter: int = 8):
    """Returns (final_model, final_report, [RefineStep])."""
    steps: List[RefineStep] = []
    m = model.model_copy(deep=True)

    for it in range(1, max_iter + 1):
        report = validate(reqs, simulate(m))
        if report.all_pass:
            return m, report, steps

        progressed = False
        for c in report.failed:
            action = _fix(m, reqs, c.metric)
            if action:
                m = refill(m)
                steps.append(RefineStep(it, action, c.metric))
                progressed = True
                break  # re-simulate after each single change

        if not progressed:
            break  # nothing left we know how to fix

    return m, validate(reqs, simulate(m)), steps


def _fix(m: PlantModel, reqs: RequirementSet, metric: str) -> str:
    """Apply one corrective change for `metric`. Return a human-readable action."""
    if metric == "string_voc_tmin":
        r = reqs.by_metric("string_voc_tmin")
        limit = float(r.target)  # type: ignore[arg-type]
        voc_cold = voc_at_temp(m.module.voc, m.module.temp_coeff_voc, m.site.min_temp_c)
        new_mps = int(limit // voc_cold)
        if new_mps < m.modules_per_string:
            old = m.modules_per_string
            m.modules_per_string = new_mps
            return (f"Reduced modules/string {old}->{new_mps} "
                    f"(Voc@{m.site.min_temp_c:g}C = {voc_cold:.2f} V/module, "
                    f"limit {limit:g} V)")
        return ""

    if metric == "dc_ac_ratio":
        r = reqs.by_metric("dc_ac_ratio")
        lo, hi = r.target if isinstance(r.target, (tuple, list)) else (r.target, r.target)  # type: ignore
        mid = (lo + hi) / 2
        dc_kw = m.n_modules * m.module.wp / 1000.0
        new_n = max(1, round(dc_kw / (m.inverter.ac_kw * mid)))
        if new_n != m.n_inverters:
            old = m.n_inverters
            m.n_inverters = new_n
            m.target_dc_ac = mid
            return f"Adjusted inverter count {old}->{new_n} to hit DC/AC ~{mid:g}"
        return ""

    if metric == "gcr":
        r = reqs.by_metric("gcr")
        cap = float(r.target)  # type: ignore[arg-type]
        from .synthesize import _load_tables
        collector_w = float(_load_tables().get(m.table_name, {}).get("width_m", 4.576))
        new_pitch = round(collector_w / cap, 3)
        if new_pitch > m.row_pitch_m:
            old = m.row_pitch_m
            m.row_pitch_m = new_pitch
            return f"Increased row pitch {old:g}->{new_pitch:g} m to meet GCR <= {cap:g}"
        return ""

    if metric == "row_pitch_m":
        r = reqs.by_metric("row_pitch_m")
        need = float(r.target)  # type: ignore[arg-type]
        if need > m.row_pitch_m:
            old = m.row_pitch_m
            m.row_pitch_m = need
            return f"Increased row pitch {old:g}->{need:g} m to meet minimum pitch"
        return ""

    return ""  # no known corrective rule
