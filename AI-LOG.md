# AI-LOG.md — SpecAlive

Honest record of how AI was used to build SpecAlive, for the hackathon's
fair-play requirement. Tool: **Claude Code (Claude Opus 4.8)**.

## Summary
AI was used as a pair-programmer and domain assistant throughout: exploring the
existing CAD codebase, scoping the project, writing the Python engine, and
generating the SysML v2 / Modelica emitters. All engineering formulas were
reviewed for correctness by the team; all numbers in the demo are traceable to
either the CAD repo or stated industry-typical inputs (see `DECISIONS.md` #6 and
the spec's provenance note). No fabricated repo facts were accepted — customer
names, table geometry, and command strings were verified against the actual
source before use.

## What AI did
| Area | AI contribution | Human oversight |
|------|-----------------|-----------------|
| Codebase exploration | Read `README.md`, `CLAUDE.md`, 67 feature docs, `Orchestrator.cs`, `CustomerConfig.cs`, `tableData.json` to extract real vocabulary | Team confirmed which facts are repo-authentic vs. per-tender inputs |
| Scoping | Proposed the requirements→model→sim→validate→refine→command-plan loop | Team chose domain (Enrich), sim depth, and toolchain alignment |
| Engine code | Wrote `schema/extract/synthesize/simulate/validate/refine/commands/diagram/pipeline` | Team reviewed PV formulas (string sizing, DC/AC, GCR, yield, cable drop) |
| SysML v2 + Modelica | Generated the emitters from the validated model | Team validated syntax against SysML v2 / Modelica references |
| Docs | Drafted pitch, architecture, this log, DECISIONS, slides | Team edited for accuracy |

## Engineering the team verified independently (not taken on trust)
- `Voc(Tmin) = Voc·(1 + tc/100·(Tmin−25))` and the 1500 V string limit.
- DC/AC ratio, inverter count rounding, GCR = collector_width / pitch.
- Specific-yield = annual POA × PR; 3-phase cable drop `√3·I·R·L/V`.
- That the demo's initial failure (Voc @ 5 °C = 1580.8 V) is a genuine over-voltage, not a contrived one.

## Prompts / workflow (representative)
1. "Read the Solar-Design-Configurator project, no code changes" → codebase map.
2. "Brainstorm/scope a spec→model→simulation project around it" → the SpecAlive loop.
3. "Build the project at D:\SpecAlive" → the Python package + CLI + Streamlit app.
4. "Wire in a real Enrich spec so the numbers are authentic" → repo-grounded sample + provenance.
5. "Add SysML v2 + Modelica emitters (track toolchain)" → `sysml.py`, `modelica.py`.

## Provenance discipline
When the model needed values the repo does not store (module datasheet, inverter
rating, GHI, min temperature), AI was instructed to mark them as industry-typical
inputs rather than present them as repo facts. This split is documented in the
spec file and `DECISIONS.md`.
