"""compile_check.py — verify a Modelica model compiles in OpenModelica.

This is the hard-gate check: it drives `omc` to load the .mo, check it, and
(optionally) simulate it, then prints a clean PASS/FAIL with the exact error
text. Designed to feed SpecAlive's model-repair loop: on FAIL, the error text
is what the LLM gets to propose a fix.

Usage:
    python tools/compile_check.py cases/tank/TwoTankController.mo
    python tools/compile_check.py cases/tank/TwoTankController.mo --simulate
    python tools/compile_check.py <file.mo> --omc "C:/Program Files/OpenModelica/bin/omc.exe"

Exit code 0 = compiled (gate passed), 1 = failed / omc not found.
"""
from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile


def find_omc(explicit: str | None) -> str | None:
    import glob

    if explicit and os.path.exists(explicit):
        return explicit
    on_path = shutil.which("omc")
    if on_path:
        return on_path
    # Versioned install dirs, e.g. "OpenModelica1.27.1-64bit". Check the fast
    # path (bin/omc.exe) first, then walk as a fallback.
    roots = []
    for parent in [r"C:\Program Files", r"C:\Program Files (x86)", r"C:\\", r"D:\\"]:
        roots += glob.glob(os.path.join(parent, "OpenModelica*"))
    for base in roots:
        direct = os.path.join(base, "bin", "omc.exe")
        if os.path.exists(direct):
            return direct
    for base in roots:
        for root, _dirs, files in os.walk(base):
            if "omc.exe" in files:
                return os.path.join(root, "omc.exe")
    return None


def model_name(mo_path: str) -> str:
    with open(mo_path, "r", encoding="utf-8") as f:
        txt = f.read()
    m = re.search(r"^\s*(?:model|class|block|package)\s+([A-Za-z_]\w*)", txt, re.M)
    return m.group(1) if m else os.path.splitext(os.path.basename(mo_path))[0]


def build_script(mo_path: str, name: str, simulate: bool) -> str:
    mo = mo_path.replace("\\", "/")
    lines = [
        f'loadFile("{mo}");',
        "getErrorString();",
    ]
    if simulate:
        lines += [
            f'simulate({name}, stopTime=900, outputFormat="csv");',
            "getErrorString();",
        ]
    else:
        lines += [
            f'checkModel({name});',
            "getErrorString();",
        ]
    return "\n".join(lines) + "\n"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("mo_file")
    ap.add_argument("--simulate", action="store_true",
                    help="also run simulate() (L1/L2 must simulate)")
    ap.add_argument("--omc", default=None, help="path to omc executable")
    args = ap.parse_args()

    mo_path = os.path.abspath(args.mo_file)
    if not os.path.exists(mo_path):
        print(f"[FAIL] file not found: {mo_path}")
        return 1

    omc = find_omc(args.omc)
    if not omc:
        print("[FAIL] OpenModelica 'omc' not found.")
        print("       Install it (see tools/INSTALL_OPENMODELICA.md), or pass --omc <path>.")
        return 1

    name = model_name(mo_path)
    script = build_script(mo_path, name, args.simulate)

    with tempfile.NamedTemporaryFile("w", suffix=".mos", delete=False,
                                     encoding="utf-8") as f:
        f.write(script)
        mos = f.name

    print(f"[info] omc     : {omc}")
    print(f"[info] model   : {name}")
    print(f"[info] action  : {'simulate' if args.simulate else 'checkModel'}")
    try:
        out = subprocess.run([omc, mos], capture_output=True, text=True, timeout=600)
    except subprocess.TimeoutExpired:
        print("[FAIL] omc timed out (>600 s).")
        return 1
    finally:
        try:
            os.unlink(mos)
        except OSError:
            pass

    text = (out.stdout or "") + (out.stderr or "")
    print("\n----- omc output -----")
    print(text.strip() or "(no output)")
    print("----------------------")

    low = text.lower()
    ok = ("error" not in low) and (
        "true" in low or "record simulationresult" in low or "simulation" in low
    )
    if args.simulate:
        ok = ("record simulationresult" in low) and ("error" not in low)
    else:
        # checkModel prints "Check of <M> completed successfully." on success
        ok = ("completed successfully" in low) or (("true" in low) and ("error" not in low))

    if ok:
        print(f"\n[PASS] {name} {'simulated' if args.simulate else 'compiles'} in OpenModelica. "
              f"Hard gate: OK")
        return 0
    print(f"\n[FAIL] {name} did not {'simulate' if args.simulate else 'compile'} cleanly. "
          f"Feed the error text above into the repair loop.")
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
