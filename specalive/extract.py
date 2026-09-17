"""Spec ingestion: requirements text -> RequirementSet + design hints.

Two paths:
  * extract_with_claude(text)  — uses the Anthropic API for robust NL parsing
  * extract_offline(text)      — regex/keyword parser, no API key needed

`extract()` picks Claude when ANTHROPIC_API_KEY is set (and the SDK is
installed) and falls back to offline otherwise, so the demo always runs.
"""
from __future__ import annotations

import os
import re
from typing import Dict, Tuple

from .schema import Op, Requirement, RequirementSet

# design hints = flat dict of parsed component params (fed to the synthesizer)
Hints = Dict[str, float]


def _num(pattern: str, text: str, default=None, group: int = 1):
    m = re.search(pattern, text, re.IGNORECASE)
    if not m:
        return default
    return float(m.group(group).rstrip("."))


# --------------------------------------------------------------------------- #
# Offline parser
# --------------------------------------------------------------------------- #
def extract_offline(text: str) -> Tuple[RequirementSet, Hints]:
    reqs = []

    proj = re.search(r"Project\s*:\s*(.+)", text, re.IGNORECASE)
    project = proj.group(1).strip() if proj else "Untitled"

    cap = _num(r"([\d.]+)\s*MWp", text)
    if cap is not None:
        reqs.append(Requirement(id="REQ-CAP-01", text=f"Target DC capacity {cap} MWp",
                                metric="dc_capacity_mwp", operator=Op.GE,
                                target=cap * 0.98, unit="MWp"))

    voc_lim = _num(r"shall not exceed\s*([\d.]+)\s*V", text)
    if voc_lim is not None:
        reqs.append(Requirement(id="REQ-VOC-04",
                                text=f"String Voc at min temp shall not exceed {voc_lim} V",
                                metric="string_voc_tmin", operator=Op.LE,
                                target=voc_lim, unit="V"))

    dcac = re.search(r"DC/AC ratio shall be between\s*(\d+(?:\.\d+)?)\s*and\s*(\d+(?:\.\d+)?)", text, re.IGNORECASE)
    if dcac:
        reqs.append(Requirement(id="REQ-DCAC-06",
                                text=f"DC/AC ratio between {dcac.group(1)} and {dcac.group(2)}",
                                metric="dc_ac_ratio", operator=Op.RANGE,
                                target=(float(dcac.group(1)), float(dcac.group(2)))))

    gcr = _num(r"GCR\)?\s*shall not exceed\s*([\d.]+)", text) or _num(r"coverage ratio.*?([\d.]+)", text)
    if gcr is not None:
        reqs.append(Requirement(id="REQ-GCR-07", text=f"GCR shall not exceed {gcr}",
                                metric="gcr", operator=Op.LE, target=gcr))

    pitch = _num(r"pitch shall be at least\s*([\d.]+)\s*m", text)
    if pitch is not None:
        reqs.append(Requirement(id="REQ-PITCH-08", text=f"Row pitch >= {pitch} m",
                                metric="row_pitch_m", operator=Op.GE, target=pitch, unit="m"))

    drop = _num(r"voltage drop shall not exceed\s*([\d.]+)\s*%", text)
    if drop is not None:
        reqs.append(Requirement(id="REQ-DROP-09", text=f"LT cable drop <= {drop} %",
                                metric="lt_cable_drop_pct", operator=Op.LE, target=drop, unit="%"))

    sy = _num(r"specific yield of at least\s*([\d.]+)\s*kWh", text)
    if sy is not None:
        reqs.append(Requirement(id="REQ-YIELD-10", text=f"Specific yield >= {sy} kWh/kWp",
                                metric="specific_yield_kwh_kwp", operator=Op.GE,
                                target=sy, unit="kWh/kWp"))

    area = _num(r"site area.*?([\d.]+)\s*m2", text)
    if area is not None:
        reqs.append(Requirement(id="REQ-AREA-11", text=f"Site area used <= {area} m2",
                                metric="site_area_used_m2", operator=Op.LE,
                                target=area, unit="m2"))

    # ---- design hints (component params) ----
    hints: Hints = {}
    for key, pat in {
        "capacity_mwp_target": r"([\d.]+)\s*MWp",
        "tilt_deg": r"tilt angle of\s*([\d.]+)",
        "wp": r"([\d.]+)\s*Wp",
        "voc": r"Voc\s*([\d.]+)",
        "vmp": r"Vmp\s*([\d.]+)",
        "isc": r"Isc\s*([\d.]+)",
        "imp": r"Imp\s*([\d.]+)",
        "temp_coeff_voc": r"coefficient of Voc\s*(-?[\d.]+)",
        "min_temp_c": r"minimum site temperature\s*\(?\s*(-?[\d.]+)",
        "latitude": r"latitude\s*([\d.]+)",
        "ghi_kwh_m2_day": r"GHI approx\s*([\d.]+)",
        "inverter_ac_kw": r"([\d.]+)\s*kVA",
        "area_m2": r"site area.*?([\d.]+)\s*m2",
    }.items():
        v = _num(pat, text)
        if v is not None:
            hints[key] = v

    mm = re.search(r"dimensions\s*([\d.]+)\s*m\s*x\s*([\d.]+)\s*m", text, re.IGNORECASE)
    if mm:
        hints["mod_length_m"] = float(mm.group(1))
        hints["mod_width_m"] = float(mm.group(2))

    mppt = re.search(r"MPPT window of\s*([\d.]+)\s*V\s*to\s*([\d.]+)\s*V", text, re.IGNORECASE)
    if mppt:
        hints["mppt_low_v"] = float(mppt.group(1))
        hints["mppt_high_v"] = float(mppt.group(2))

    if re.search(r"tracker", text, re.IGNORECASE):
        hints["mounting"] = 1.0  # 1 = tracker, 0 = fixed_tilt
    else:
        hints["mounting"] = 0.0

    return RequirementSet(project=project, requirements=reqs), hints


# --------------------------------------------------------------------------- #
# Claude parser (optional)
# --------------------------------------------------------------------------- #
_CLAUDE_SYSTEM = """You extract solar-plant engineering requirements from a spec.
Return ONLY valid JSON with two keys: "requirements" and "hints".
Each requirement: {id, text, metric, operator, target, unit}.
Allowed metric: dc_capacity_mwp, dc_ac_ratio, string_voc_tmin, gcr, row_pitch_m,
lt_cable_drop_pct, specific_yield_kwh_kwp, site_area_used_m2.
operator is one of <=, >=, ==, range. For range, target is [low, high].
hints is a flat object of numeric design params you can read off the spec
(capacity_mwp_target, tilt_deg, wp, voc, vmp, isc, imp, temp_coeff_voc,
min_temp_c, latitude, ghi_kwh_m2_day, inverter_ac_kw, mppt_low_v, mppt_high_v,
mod_length_m, mod_width_m, area_m2, mounting[0=fixed_tilt,1=tracker])."""


def extract_with_claude(text: str, model: str = "claude-sonnet-5") -> Tuple[RequirementSet, Hints]:
    import json

    import anthropic  # type: ignore

    client = anthropic.Anthropic()
    msg = client.messages.create(
        model=model,
        max_tokens=2000,
        system=_CLAUDE_SYSTEM,
        messages=[{"role": "user", "content": text}],
    )
    raw = msg.content[0].text
    raw = raw[raw.find("{"): raw.rfind("}") + 1]
    data = json.loads(raw)
    reqs = []
    for r in data.get("requirements", []):
        tgt = r["target"]
        if isinstance(tgt, list):
            tgt = tuple(tgt)
        reqs.append(Requirement(id=r["id"], text=r["text"], metric=r["metric"],
                                operator=Op(r["operator"]), target=tgt, unit=r.get("unit", "")))
    proj = re.search(r"Project\s*:\s*(.+)", text)
    rs = RequirementSet(project=proj.group(1).strip() if proj else "Untitled", requirements=reqs)
    return rs, {k: float(v) for k, v in data.get("hints", {}).items()}


def extract(text: str) -> Tuple[RequirementSet, Hints]:
    """Auto-select Claude if available, else offline. Never raises on missing key."""
    if os.environ.get("ANTHROPIC_API_KEY"):
        try:
            return extract_with_claude(text)
        except Exception as e:  # noqa: BLE001 — demo must not crash on API issues
            print(f"[extract] Claude path failed ({e!s}); using offline parser.")
    return extract_offline(text)
