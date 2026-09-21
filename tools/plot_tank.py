"""Plot the L1 two-tank simulation result for the demo/submission.

Usage: python tools/plot_tank.py [result.csv] [out.png]
Defaults: TwoTankController_res.csv -> cases/tank/out/tank_levels.png
"""
from __future__ import annotations

import csv
import os
import sys

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt


def col(cols, name):
    for c in cols:
        if c.strip().strip('"') == name:
            return c
    return None


def main():
    res = sys.argv[1] if len(sys.argv) > 1 else "TwoTankController_res.csv"
    out = sys.argv[2] if len(sys.argv) > 2 else "cases/tank/out/tank_levels.png"
    os.makedirs(os.path.dirname(out), exist_ok=True)

    rows = list(csv.DictReader(open(res)))
    cols = rows[0].keys()
    t = [float(r[col(cols, "time")]) for r in rows]
    h1 = [float(r[col(cols, "h1")]) for r in rows]
    h2 = [float(r[col(cols, "h2")]) for r in rows]
    v1 = [float(r[col(cols, "valve1")]) for r in rows]
    v2 = [float(r[col(cols, "valve2")]) for r in rows]
    v3 = [float(r[col(cols, "valve3")]) for r in rows]

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(11, 6), sharex=True,
                                   gridspec_kw={"height_ratios": [3, 1]})
    ax1.plot(t, h1, label="Tank 1 (TK-101)", color="#2563eb", lw=2)
    ax1.plot(t, h2, label="Tank 2 (TK-102)", color="#f59e0b", lw=2)
    ax1.axhline(0.80, ls="--", c="#94a3b8", lw=1)
    ax1.text(5, 0.81, "h1High 0.80 (CR-004)", fontsize=8, color="#64748b")
    for x, lab in [(20, "START"), (220, "STOP"), (280, "START"), (650, "STOP"), (700, "SHUT")]:
        ax1.axvline(x, ls=":", c="#cbd5e1", lw=1)
        ax1.text(x + 3, 0.02, lab, rotation=90, fontsize=7, color="#64748b", va="bottom")
    ax1.set_ylabel("Level (m)")
    ax1.set_title("L1 Two-Tank Controller — SpecAlive-generated Modelica (OpenModelica)")
    ax1.legend(loc="upper right", fontsize=9)
    ax1.grid(alpha=0.25)

    ax2.step(t, [x + 0.0 for x in v1], where="post", label="V1", color="#2563eb")
    ax2.step(t, [x + 1.2 for x in v2], where="post", label="V2", color="#16a34a")
    ax2.step(t, [x + 2.4 for x in v3], where="post", label="V3", color="#dc2626")
    ax2.set_yticks([0.5, 1.7, 2.9])
    ax2.set_yticklabels(["V1", "V2", "V3"])
    ax2.set_xlabel("time (s)")
    ax2.set_title("Valve commands (note V2+V3 together only during SHUT)", fontsize=9)
    ax2.grid(alpha=0.25)

    fig.tight_layout()
    fig.savefig(out, dpi=130)
    print(f"saved {out}")


if __name__ == "__main__":
    main()
