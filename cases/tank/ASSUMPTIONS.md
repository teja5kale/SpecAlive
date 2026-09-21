# L1 Two-Tank — Assumptions, Traceability & Honesty

Evidence layer for the L1 submission (PRD §7 layer 3, §8.2 "Honesty").
Single source of truth: [`ir.json`](ir.json). Outputs: [`TwoTankController.sysml`](TwoTankController.sysml),
[`TwoTankController.mo`](TwoTankController.mo).

## 1. Contradictions found and how they were resolved
| Item | Conflicting sources | Resolution | Authority |
|------|---------------------|------------|-----------|
| Tank 1 high setpoint | `0.78 m` (07_legacy_tank_demo.mo) vs `0.80 m` (12_operator_shift_notes.txt) | **0.80 m** | CR-004 (11 Mar 2026); operator confirmed at 09:06 ("Observed target is 0.80, not the 0.78 in the old model") |
| Post-transfer delay | legacy `10 s` vs approved | **12 s** | CR-004, closes action A-18 |
| Inter-cycle delay | legacy `10 s` vs approved | **8 s** | CR-004, closes action A-19 |
| STOP effect on delay timer | controls "freeze" vs simulation "restart" | **Freeze remaining delay** | DR-02 decision D-03 |

Contradictions were **flagged and resolved by cited authority**, not silently overwritten (PRD §6.3).

## 2. Assumptions made (stated, not invented)
| # | Assumption | Basis |
|---|-----------|-------|
| A1 | Valves are ideal on/off with constant volumetric flow when open | 07_legacy_tank_demo.mo uses fixed qFill/qTransfer/qDrain |
| A2 | Tanks are prismatic (constant area); level = volume / area | legacy model `der(level)=q/A` |
| A3 | SHUT drains with V2+V3 open together, V1 closed | DR-02 explicit exception to D-09 |
| A4 | START at 280 s is a **resume** (clears pause), not a new fill | D-04 ("START while running ignored") + operator note "does NOT go back to fill" |
| A5 | Command edge times (20/220/280/650/700 s) are **test stimulus**, not controller logic | 07_legacy_tank_demo.mo comment; operator notes |

## 3. Missing / unresolved information (surfaced, not fabricated)
- Explicit port media typing beyond `liquid`/`signal` is not given — assumed.
- Pre-CR-004 timer values were ambiguous in the legacy model; superseded by CR-004.
- E-stop behaviour is **out of scope** (operator notes) — deliberately not modelled.
- Valve dynamics / actuation time from `08_valve_datasheet.pdf` not yet incorporated (idealised as instant).

## 4. Traceability: input fragment → model element
| Input fragment | Model element |
|----------------|---------------|
| `11_partial_legacy_architecture.puml` topology | connections in `ir.json` / `connect` in SysML |
| PLC-101, XV-101/102/103, TK-101/102, LT-101/102 tags | parts in `ir.json` / part defs in SysML |
| 07_legacy_tank_demo.mo `der(tank1Level)=...` | `der(h1)`/`der(h2)` in `.mo` |
| DR-02 D-01…D-09 | `requirement def` + `satisfy` in SysML; guard logic in `.mo` |
| DR-02 D-03 "freeze remaining delay" | `der(tRun)=... if not paused` in `.mo` |
| CR-004 (0.80 / 12 s / 8 s) | parameters `h1High`, `wait2`, `wait3` |
| operator command timeline | `test_stimulus.edges_s` in `ir.json`; `when time>=` in `.mo` |

## 5. Honesty statement
- **No fabricated components, ports, or physics.** Every element in the IR traces to a
  cited input fragment or a declared assumption above.
- **General vs case-specific (PRD §8.3):** the *pipeline* (ingest → IR → SysML/Modelica →
  compile-check → repair → traceability) is general. **Case-specific to L1 in this
  deliverable:** the concrete IR content and the fixed command-edge stimulus times.
  Generalisation to L2–L4 is the next milestone; nothing here hard-codes "two tanks"
  in the generators — they read `ir.json`.

## 6. Hard-gate status
The Modelica model has **not yet been compiled** on this machine (OpenModelica not
installed here). Verify with:
```
python tools/compile_check.py cases/tank/TwoTankController.mo --simulate
```
If it reports errors, they feed the model-repair loop (PRD §5.2). This limitation is
stated rather than hidden.
