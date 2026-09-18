# SpecAlive — 8-Slide Deck

*SpecAlive Hackathon 2026 · Track: System Modelling with Agentic AI.*
One slide per section; speaker notes under each. Target: the 45-minute evaluation.

---

## Slide 1 — Title & Problem
**SpecAlive: Specs to a Live Solar Plant Model**

- A solar plant spec arrives as prose ("5 MWp fixed-tilt, DC/AC 1.2–1.3, Voc ≤ 1500 V…").
- Today: an engineer reads it, holds the design in their head, drives **75 CAD ribbon buttons** by hand, and **nothing verifies the drawing against the spec**.
- The missing link: a machine-readable, verifiable bridge from *requirements* to *model*.

> Speaker note: This is exactly the hackathon loop — Requirements → System Model → Simulation → Validation → Refine.

---

## Slide 2 — What is system modelling & why it matters here
- **MBSE**: one structured model as the single source of truth, with requirements traced onto it.
- For a PV plant the model *is* the engineering: modules → strings → SCB → inverter → cabling → piling.
- Without it, requirement compliance is tribal knowledge lost the moment the DWG ships.

> Speaker note: We express the model in **SysML v2** and simulate it in **Modelica** + a fast Python engine.

---

## Slide 3 — Architecture (the SpecAlive loop)
```
Requirements text
  → [Claude/offline] RequirementSet
  → PlantModel (single source of truth)
  → { SysML v2 · Modelica · Python KPIs }
  → Validation (PASS/FAIL + traceability)
  → Refine (agentic auto-fix) ↺
  → Orchestrator command plan → SicaMcpHost → live CAD
```
- One validated model → four coordinated outputs.
- **No changes** to the production CAD repo — SpecAlive reads its vocabulary, emits its inputs.

---

## Slide 4 — Role of AI (Agentic)
- **Extraction agent:** prose → structured, verifiable requirements (Claude; deterministic offline fallback).
- **Refine agent:** diagnoses a failing requirement, applies a *physically-correct* correction, re-simulates — autonomously, until all pass or no rule applies.
- AI writes the *model and the checks*, not just code. Fair-play logged in `AI-LOG.md`.

> Speaker note: Demo failure is real (cold-Voc oversizing), not staged.

---

## Slide 5 — SysML v2 + Modelica (the system model, live)
- **SysML v2:** `part def` for module/table/string/inverter, a plant assembly, `requirement def`s with constraints, and `satisfy` relationships — generated from the validated model.
- **Modelica:** a runnable `.mo` — clear-sky irradiance → DC power → inverter clipping → integrated AC energy; daily yield cross-checks the Python engine.
- Both regenerate when the spec changes.

---

## Slide 6 — Live example (Enrich Block-01)
- Authentic inputs: customer **Enrich**, **Waaree 550 Wp**, real **MMS Table (32.2920 × 4.5760)** + 12 piles/table.
- Extract **8 requirements** → initial model **7/8 PASS**.
- **FAIL:** string Voc @ 5 °C = **1580.8 V > 1500 V**.
- **Refine:** modules/string 30 → 28 → **8/8 ALL PASS**.
- Result: 5.005 MWp · DC/AC 1.25 · GCR 0.45 · 1783 kWh/kWp · 163 tables · 1956 piles.
- Edit one threshold → whole model + validation regenerate. **The money-shot.**

---

## Slide 7 — Grounded in a real product + what we submit
- Bridges to the real tool via its `Orchestrator` command plan (`PlaceTables → … → BOQ`) and the scaffolded **`SicaMcpHost`**.
- **Deliverables:** repo · `DECISIONS.md` · `AI-LOG.md` · this deck · CLI + Streamlit app · generated `.sysml` / `.mo`.
- Everything runs offline in <5 s; Modelica runs in OpenModelica.

---

## Slide 8 — Impact, roadmap, team
- **Impact:** requirements traceability + automatic compliance the CAD tool lacks today; a spec becomes a verified, buildable design.
- **Roadmap:** live `SicaMcpHost` round-trip; optimizer (max yield s.t. all requirements); tracker + multi-block; PDF spec ingestion.
- **Team & effort:** 4 members, ~12–15 focused hours, part-time. Roles: SysML, Modelica, Python/LLM, domain.

> Speaker note: Close on the one-liner — "SpecAlive turns a paragraph of requirements into a validated, simulatable, buildable solar plant."
