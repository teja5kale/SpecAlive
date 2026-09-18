# 🔆 SpecAlive — Specs to a Live Solar Plant Model

**SpecAlive Hackathon 2026 · AI in Engineering / System Modelling · CCTech**

SpecAlive reads a solar plant's requirements in plain English, builds a validated
engineering **system model**, proves it meets every requirement by **simulation**,
and emits the exact **command plan** that drives the existing
*Solar-Design-Configurator* CAD tool — closing the loop from **spec → live model**.

> This is a standalone project. It **reads** the CAD tool's command/BOQ vocabulary
> but makes **no changes** to that repository.

Full write-up: [`docs/PITCH_AND_ARCHITECTURE.md`](docs/PITCH_AND_ARCHITECTURE.md).

---

## The loop

```
Requirements text → RequirementSet → PlantModel → Simulation → Validation
      → Refine (auto-fix) → Orchestrator command plan (SicaMcpHost)
```

## Quickstart

```bash
pip install -r requirements.txt          # pydantic + numpy are the only hard deps
python cli.py                            # runs on data/sample_spec_enrich.txt
python cli.py path/to/spec.txt --json    # your spec + dump design-intent JSON
streamlit run app.py                     # optional web UI
```

The pipeline runs fully **offline**. Set `ANTHROPIC_API_KEY` to use Claude for
requirement extraction; otherwise a built-in regex parser is used.

## What the demo shows

Running the default **Enrich** spec (`data/sample_spec_enrich.txt`):

- **8 requirements** extracted from an authentic Enrich Block-01 design basis.
- Initial model: **7/8 pass** — the classic **cold-Voc string oversizing** error
  fails (`string Voc @ 5 °C = 1580.8 V > 1500 V`).
- **Refine**: modules/string 30 → 28 → **8/8 ALL PASS**.
- Result: 5.005 MWp, DC/AC 1.25, GCR 0.45, specific yield 1783 kWh/kWp,
  **163 × MMS Table (32.2920 x 4.5760)**, **1956 C-section piles**, and an ordered
  **Orchestrator command plan** for the CAD tool.

Edit one threshold in the spec, re-run, and the whole model + validation
regenerates — the "specs to live models" money-shot.

### Authenticity / provenance

The Enrich spec and `data/tables.json` are grounded in the real
Solar-Design-Configurator codebase (read-only; nothing is written back):

| Authentic from the repo | Source |
|---|---|
| Customer **"Enrich"** (current production) and **"Waaree"** | `OrgControl/CustomerConfig.cs` |
| **MMS Table (32.2920 x 4.5760)** + 12 C-section piles/table | `Resources/tableData.json` |
| Default fixed-tilt table name | `MMSData.currTableName` |
| Terminology: Block, Inverter, ASB, SCB, LT Panel, Transformer | feature docs / cable-schedule template |
| Orchestrator command strings in the plan | `CLAUDE.md` command map / `Orchestrator.cs` |

Per-tender electrical inputs (module datasheet, inverter rating, DC/AC window,
GHI, min temperature, GCR/pitch/yield targets) are **not** stored in the repo —
they're set to representative values for a Khavda utility block and are listed in
the spec's own "Provenance note". `data/sample_spec_fixedtilt.txt` is a generic
alternative spec.

## Layout

```
specalive/
  schema.py       Pydantic model: Requirement, ModuleSpec, PlantModel, ...
  extract.py      spec text → requirements (+ hints); Claude or offline
  synthesize.py   requirements → PlantModel (maps to CAD tool block concepts)
  simulate.py     PV engineering KPIs (string sizing, DC/AC, yield, shading, drop, BOQ)
  validate.py     each requirement → PASS/FAIL + traceability
  refine.py       auto-correct failing requirements, re-simulate
  commands.py     Orchestrator command plan + design-intent JSON (SicaMcpHost bridge)
  sysml.py        SysML v2 textual emitter (parts, requirements, satisfy)
  modelica.py     runnable Modelica .mo emitter (one-day energy model)
  diagram.py      SysML-style Mermaid block diagram
  pipeline.py     end-to-end orchestrator (+ write_outputs)
cli.py            terminal runner
app.py            Streamlit UI
data/             tables.json (from CAD tool) + sample specs
out/              generated .sysml / .mo / .json / .mmd (created on run)
docs/             pitch + architecture
DECISIONS.md      design decision log (submission)
AI-LOG.md         AI usage / fair-play log (submission)
SLIDES.md         8-slide deck outline (submission)
```

## Track outputs (System Modelling with Agentic AI)

Every run also generates, in `out/`:
- **SysML v2** (`.sysml`) — `part def`s, `requirement def`s with constraints, `satisfy` relationships.
- **Modelica** (`.mo`) — a runnable one-day energy model (clear-sky irradiance →
  DC → inverter clipping → integrated AC energy). Run in OpenModelica:
  `loadFile("out/<name>.mo"); simulate(<Name>, stopTime=86400)`.
- **Design-intent JSON** + **Mermaid** diagram.

## Engineering (what the simulation computes)

- **String sizing:** `Voc(Tmin) = Voc·(1 + tc/100·(Tmin−25))`; max modules/string
  so string Voc stays ≤ the system limit.
- **Counts & DC/AC:** DC kWp, inverter count, actual DC/AC ratio.
- **GCR & shading:** `GCR = collector_width / pitch`; shading-loss proxy.
- **Yield:** annual POA irradiation × performance ratio → specific yield (kWh/kWp).
- **Cable drop:** 3-phase `√3·I·R·L / V` with parallel runs.
- **BOQ:** tables, piles, cable lengths, inverters — mirroring the tool's BOQ.
