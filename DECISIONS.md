# DECISIONS.md — SpecAlive

Design decisions, most-recent last. Format: **what** · **why** · **date**.
Track: *System Modelling with Agentic AI* — SpecAlive Hackathon 2026.

| # | Decision | Rationale | Date |
|---|----------|-----------|------|
| 1 | Build **on top of** the real *Solar-Design-Configurator* CAD product rather than a toy domain | The theme is "Specs to live Models"; anchoring to a production tool (75 features, `Orchestrator.Main`, scaffolded `SicaMcpHost`) makes the "live model" real and the integration story concrete. | 2026-09-17 |
| 2 | **Standalone repo**, zero changes to the CAD codebase | The CAD product is production code we were asked not to modify; SpecAlive only *reads* its command/BOQ vocabulary and *emits* inputs for it. | 2026-09-17 |
| 3 | Intermediate **structured model (Pydantic)** as the single source of truth | Makes this MBSE, not "LLM writes code": every downstream artifact (SysML, Modelica, sim, command plan) derives from one validated model. | 2026-09-17 |
| 4 | **Offline regex extractor + optional Claude** for requirement parsing | Demo must never break on a missing API key or network; Claude is used when `ANTHROPIC_API_KEY` is set, else a deterministic fallback. | 2026-09-17 |
| 5 | **Python/SciPy** simulation engine for KPIs | Runs everywhere, instantly, in the demo — no external solver needed for the always-on validation loop. | 2026-09-17 |
| 6 | Sample spec = authentic **Enrich Block-01** | Grounded in repo facts: customer "Enrich" (`CustomerConfig.cs`), Waaree module vendor, real `MMS Table (32.2920 x 4.5760)` geometry + 12-pile config (`tableData.json`). Per-tender electrical inputs flagged in a provenance note. | 2026-09-17 |
| 7 | Demo failure = **cold-Voc string oversizing** | A real, subtle PV engineering error (string Voc @ Tmin > 1500 V) that a spec-vs-model check should catch — makes the refine loop meaningful, not staged. | 2026-09-17 |
| 8 | **Add SysML v2 + Modelica emitters** as first-class outputs | The track explicitly names SysML v2 + Modelica as the toolchain; the same validated model now emits a SysML v2 system model (parts, requirements, satisfy) and a runnable Modelica `.mo`. Python sim retained as the always-runs validator. | 2026-09-18 |
| 9 | Modelica model kept **library-free** (local `pi`, single `der`) | Must load/run in a clean OpenModelica without MSL version friction during the 45-min eval. | 2026-09-18 |
| 10 | Frame the pipeline as an **explicit agent loop** (extract → synthesize → simulate → validate → refine) | Matches the "Agentic AI" track; the refiner autonomously diagnoses a failing requirement and applies a physically-correct correction, then re-validates. | 2026-09-18 |

## Open decisions / to revisit
- Whether to run the Modelica model live in the demo (needs `omc` on the eval machine) or show the Python sim as primary and Modelica as the exported deliverable.
- Whether to wire the command plan into the live plugin via `SicaMcpHost` (stretch; adapter on the host side, still no change to the CAD repo).
