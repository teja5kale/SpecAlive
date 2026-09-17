"""Validator — compare each Requirement to its simulated KPI.

Produces a ValidationReport: one Check per requirement (PASS/FAIL) plus a
traceability link (requirement id -> metric -> value -> target).
"""
from __future__ import annotations

from dataclasses import dataclass
from typing import List, Optional

from .schema import Op, RequirementSet
from .simulate import SimResult


@dataclass
class Check:
    req_id: str
    text: str
    metric: str
    value: Optional[float]
    operator: str
    target: object
    unit: str
    passed: bool
    detail: str

    @property
    def status(self) -> str:
        return "PASS" if self.passed else "FAIL"


@dataclass
class ValidationReport:
    checks: List[Check]

    @property
    def all_pass(self) -> bool:
        return all(c.passed for c in self.checks)

    @property
    def failed(self) -> List[Check]:
        return [c for c in self.checks if not c.passed]


def _fmt(t) -> str:
    if isinstance(t, (tuple, list)):
        return f"[{t[0]}, {t[1]}]"
    return str(t)


def validate(reqs: RequirementSet, sim: SimResult, tol: float = 1e-6) -> ValidationReport:
    checks: List[Check] = []
    for r in reqs.requirements:
        val = sim.metrics.get(r.metric)
        if val is None:
            checks.append(Check(r.id, r.text, r.metric, None, r.operator.value,
                                r.target, r.unit, False, "metric not simulated"))
            continue

        if r.operator == Op.LE:
            ok = val <= float(r.target) + tol            # type: ignore[arg-type]
        elif r.operator == Op.GE:
            ok = val >= float(r.target) - tol            # type: ignore[arg-type]
        elif r.operator == Op.EQ:
            ok = abs(val - float(r.target)) <= max(tol, 0.01 * abs(float(r.target)))  # type: ignore[arg-type]
        elif r.operator == Op.RANGE:
            lo, hi = r.target                            # type: ignore[misc]
            ok = (lo - tol) <= val <= (hi + tol)
        else:
            ok = False

        detail = f"{val} {r.operator.value} {_fmt(r.target)} {r.unit}".strip()
        checks.append(Check(r.id, r.text, r.metric, val, r.operator.value,
                            r.target, r.unit, ok, detail))
    return ValidationReport(checks=checks)
