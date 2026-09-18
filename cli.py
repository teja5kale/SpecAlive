"""SpecAlive CLI — run the full loop on a spec file and print the report.

Usage:
    python cli.py [path/to/spec.txt]      (defaults to data/sample_spec_fixedtilt.txt)
    python cli.py spec.txt --json         (also dump design-intent JSON)
"""
from __future__ import annotations

import json
import os
import sys

# Windows terminals default to cp1252; force UTF-8 so unicode/emoji don't crash.
try:
    sys.stdout.reconfigure(encoding="utf-8")
except Exception:  # noqa: BLE001
    pass

from specalive.pipeline import run

DEFAULT_SPEC = os.path.join(os.path.dirname(__file__), "data", "sample_spec_enrich.txt")

G, R, Y, B, X = "\033[92m", "\033[91m", "\033[93m", "\033[96m", "\033[0m"


def _bar(title: str):
    print(f"\n{B}{'=' * 68}\n{title}\n{'=' * 68}{X}")


def _report(rep, title):
    _bar(title)
    for c in rep.checks:
        col = G if c.passed else R
        print(f"  {col}[{c.status}]{X} {c.req_id:<14} {c.detail}")
    n_pass = sum(c.passed for c in rep.checks)
    print(f"\n  {n_pass}/{len(rep.checks)} requirements satisfied "
          f"({G+'ALL PASS'+X if rep.all_pass else R+'FAILURES'+X})")


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    spec_path = args[0] if args else DEFAULT_SPEC
    with open(spec_path, "r", encoding="utf-8") as f:
        text = f.read()

    # --correct : size strings cold-Voc-aware from the start (no refine needed).
    # default   : naive sizing -> initial Voc failure -> refine fixes it.
    naive = "--correct" not in sys.argv
    mode = "naive (catch & fix)" if naive else "cold-Voc-aware (correct from start)"
    print(f"{Y}String-sizing mode: {mode}{X}   "
          f"[toggle with --correct]")

    res = run(text, naive_string_sizing=naive)

    _bar(f"① REQUIREMENTS EXTRACTED — {res.requirements.project}")
    for r in res.requirements.requirements:
        tgt = r.target if not isinstance(r.target, tuple) else f"[{r.target[0]}, {r.target[1]}]"
        print(f"  {r.id:<14} {r.metric:<24} {r.operator.value:<6} {tgt} {r.unit}")

    _bar("② INITIAL MODEL (synthesized)")
    m0 = res.model_initial
    print(f"  {m0.n_modules} modules · {m0.n_strings} strings × {m0.modules_per_string}/str "
          f"· {m0.n_inverters} inverter(s) · {m0.n_tables} tables · {m0.n_piles} piles")
    print(f"  mounting={m0.mounting.value}  tilt={m0.tilt_deg}°  pitch={m0.row_pitch_m} m")

    _report(res.report_initial, "③ VALIDATION — initial")

    _bar("④ REFINE")
    if res.steps:
        for s in res.steps:
            print(f"  {Y}iter {s.iteration}{X}  ({s.fixed_metric}) → {s.action}")
    else:
        print("  no changes needed — initial model already satisfies all requirements")

    _report(res.report_final, "⑤ VALIDATION — after refine")

    _bar("⑥ SIMULATED KPIs (final)")
    e = res.sim_final.extras
    print(f"  DC {e['dc_kw']:.0f} kW · AC {e['ac_kw']:.0f} kW · DC/AC "
          f"{res.sim_final.m('dc_ac_ratio')}")
    print(f"  String Voc@min-temp {res.sim_final.m('string_voc_tmin')} V "
          f"(={e['modules_per_string']}×{e['voc_cold_per_module']} V)")
    print(f"  GCR {res.sim_final.m('gcr')} · pitch {res.sim_final.m('row_pitch_m')} m "
          f"· shading loss {e['shading_loss_pct']}%")
    print(f"  PR {e['pr']} · specific yield {res.sim_final.m('specific_yield_kwh_kwp'):.0f} kWh/kWp")
    print(f"  LT drop {res.sim_final.m('lt_cable_drop_pct')}% · "
          f"land {res.sim_final.m('site_area_used_m2'):.0f} m²")

    _bar("⑦ BOQ ROLL-UP")
    for k, v in res.sim_final.boq.items():
        print(f"  {k:<22} {v:>10.0f}")

    _bar("⑧ LIVE-MODEL BRIDGE → Orchestrator command plan (SicaMcpHost)")
    for i, s in enumerate(res.command_plan, 1):
        dep = f"  (after {', '.join(s.depends_on)})" if s.depends_on else ""
        print(f"  {i:>2}. {B}{s.command}{X}{dep}\n      {s.purpose}")

    _bar("⑨ GENERATED SYSTEM-MODEL ARTIFACTS (SysML v2 + Modelica)")
    out_dir = os.path.join(os.path.dirname(__file__), "out")
    written = res.write_outputs(out_dir)
    for label, path in written.items():
        print(f"  {G}✓{X} {label:<22} {os.path.relpath(path)}")
    print(f"\n  Run the Modelica model with OpenModelica:")
    print(f"    omc  →  loadFile(\"{os.path.relpath(written['Modelica'])}\"); "
          f"simulate({res.model_final.project and ''.join(c if c.isalnum() else '_' for c in res.model_final.project).strip('_')}, stopTime=86400)")

    if "--json" in sys.argv:
        _bar("DESIGN INTENT (JSON)")
        print(json.dumps(res.design_intent, indent=2))


if __name__ == "__main__":
    main()
