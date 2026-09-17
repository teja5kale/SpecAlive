# SpecAlive — Specs to a Live Solar Plant Model

**SpecAlive Hackathon 2026 · AI in Engineering / System Modelling · CCTech**
*Turning natural-language solar-plant requirements into a validated, executable system model that drives real CAD automation.*

---

## 1. The one-line pitch

> **SpecAlive reads a solar plant's requirements in plain English, builds a validated engineering model of the plant, proves it meets every requirement by simulation, and emits the exact command plan that drives the existing Solar-Design-Configurator CAD tool to produce the drawing — closing the loop from *spec* to *live model*.**

---

## 2. The problem

The team already has a powerful product — **Solar-Design-Configurator** (aka *Solar-Infra-CAD-Automate*): an AutoCAD 2024 plugin with **75 ribbon features** (piling, cabling, inverter grouping, BOQ, earthing, grading, …) that automates the drafting of a solar PV plant.

But today the workflow has a broken front-end:

1. A design **spec** arrives as a PDF / email / tender document:
   *"Design a 5 MWp fixed-tilt block. DC/AC ratio 1.2–1.3. String Voc at minimum temperature shall not exceed 1500 V. LT cable voltage drop ≤ 2%. GCR ≤ 0.45. Specific yield ≥ 1500 kWh/kWp."*
2. An engineer **reads it and holds the design in their head**.
3. They **manually drive 75 ribbon buttons** in the correct order to produce the CAD layout.
4. **Nothing checks** that the finished drawing actually satisfies the original spec. Traceability is manual, error-prone, and lost the moment the drawing is delivered.

**The gap:** there is no machine-readable, verifiable bridge between *requirements* and the *model* the tool produces. That is exactly the hackathon theme:

```
Requirements → System Model → Simulation → Validation → Refine → Design → Iterate
```

---

## 3. The solution — the SpecAlive loop

SpecAlive is a **standalone layer that sits on top of** Solar-Design-Configurator. It **does not modify** the CAD codebase; it consumes its vocabulary (features, commands, BOQ concepts) and produces inputs for it.

```
┌─────────────────────────────────────────────────────────────────────┐
│ ① REQUIREMENTS (plain text / spec sheet / "shall" statements)         │
│    "5 MWp fixed-tilt, DC/AC 1.2–1.3, Voc ≤ 1500V, cable drop ≤ 2% …"  │
└───────────────┬─────────────────────────────────────────────────────┘
                │  Claude API → strict Pydantic schema (extraction)
                ▼
┌─────────────────────────────────────────────────────────────────────┐
│ ② PLANT SYSTEM MODEL  (MBSE — the single source of truth)             │
│    Blocks map 1:1 to the tool's own concepts:                         │
│    MMS Tables · Strings · SCB/Inverter groups · DC/LT/HT cables ·     │
│    Piling.  Rendered as a SysML-style block diagram + parameter table │
│    with requirement IDs traced onto each block.                       │
└───────────────┬─────────────────────────────────────────────────────┘
                │  Python / SciPy / NumPy  (real PV engineering)
                ▼
┌─────────────────────────────────────────────────────────────────────┐
│ ③ SIMULATION  (no AutoCAD needed — always runs in the demo)          │
│    • String sizing: Voc@Tmin ≤ 1500 V, Vmp window vs inverter MPPT    │
│    • Array counts → DC capacity → inverter count → DC/AC ratio        │
│    • GCR from row pitch & table size → inter-row shading loss         │
│    • Clear-sky irradiance → DC power → inverter clipping → AC yield   │
│    • Cable voltage drop / I²R losses from estimated lengths           │
│    • BOQ roll-up (tables, piles, cable lengths) — mirrors tool's BOQ  │
└───────────────┬─────────────────────────────────────────────────────┘
                │
                ▼
┌─────────────────────────────────────────────────────────────────────┐
│ ④ VALIDATION                                                          │
│    Every requirement → PASS / FAIL vs the computed KPI                │
│    + full traceability matrix (requirement ↔ model block ↔ KPI)      │
└───────────────┬─────────────────────────────────────────────────────┘
                │  if any FAIL
                ▼
┌─────────────────────────────────────────────────────────────────────┐
│ ⑤ REFINE  (auto-adjust and re-simulate)                              │
│    e.g. Voc@Tmin > 1500 V → reduce modules/string                    │
│         DC/AC out of band → adjust inverter/module count             │
│         shading loss too high → increase row pitch (lowers GCR)       │
└───────────────┬─────────────────────────────────────────────────────┘
                │  once all PASS
                ▼
┌─────────────────────────────────────────────────────────────────────┐
│ ⑥ ★ LIVE-MODEL BRIDGE                                                 │
│    Emit the exact Orchestrator command plan that builds the drawing:  │
│    PlaceTables → PilePlacement → INV_PILING → AutoGrouping →          │
│    LTCable → sectionmark → BOQ …                                      │
│    → machine-readable design intent that plugs into SicaMcpHost.      │
└─────────────────────────────────────────────────────────────────────┘
```

**The money-shot (live demo):** change one line in the spec — *"DC/AC shall be 1.2–1.3"* → tighten to *"= 1.15"* — and the block diagram, the KPI plots, the PASS/FAIL matrix, **and** the generated command plan all regenerate live. Spec → model → validation, on screen, in one keystroke.

---

## 4. Why this wins

- **On-theme, literally.** "Specs to live Models" — and the *live model* here is a real production CAD tool, not a toy.
- **Grounded in a real product.** It leverages Solar-Design-Configurator's 75 features, its `Orchestrator.Main(cmd)` dispatcher, and its already-scaffolded **`SicaMcpHost`** — a credible, concrete integration story judges can see.
- **The hard part is real and demo-safe.** String sizing, DC/AC, yield, shading, and voltage-drop are genuine PV engineering, computed in pure Python. **Zero AutoCAD dependency** → the demo never breaks on a flaky plugin load.
- **Closes the loop the tool is missing.** Today the tool draws; it doesn't *verify against intent*. SpecAlive adds requirements traceability and validation — the MBSE piece.
- **Extensible.** The same structured model can later drive the live plugin through `SicaMcpHost` for a true "spec → drawing" round trip.

---

## 5. Architecture

### 5.1 Components

| # | Component | Tech | Responsibility |
|---|-----------|------|----------------|
| A | **Spec Ingestor** | Claude API + Pydantic | Parse requirements text → `RequirementSet` (structured, each with a verifiable threshold) |
| B | **Model Synthesizer** | Python | Build `PlantModel` (blocks + params) from requirements + engineering rules |
| C | **Diagram Renderer** | Mermaid / Graphviz | SysML-style block diagram (BDD/IBD flavor) + parameter table |
| D | **Simulation Engine** | NumPy / SciPy | Compute KPIs (string sizing, counts, DC/AC, yield, shading, cable drop, BOQ) |
| E | **Validator** | Python | Compare each requirement to its KPI → PASS/FAIL + traceability matrix |
| F | **Refiner** | Python | Adjust parameters to satisfy failing requirements, loop back to D |
| G | **Command-Plan Emitter** | Python | Produce ordered Orchestrator command list + JSON design intent for `SicaMcpHost` |
| H | **UI** | Streamlit | Spec editor ↔ live diagram + KPI plots + PASS/FAIL matrix + command plan |

### 5.2 Data flow

```
spec.txt ──A──▶ RequirementSet ──B──▶ PlantModel ──┬──C──▶ diagram.mmd
                                                    ├──D──▶ SimResult (KPIs)
                                    SimResult ──────E──▶ ValidationReport
                              ValidationReport ─────F──▶ (refine → B) or ✓
                                    PlantModel ──────G──▶ command_plan.json
                                        all ─────────H──▶ Streamlit app
```

### 5.3 Core schema (sketch — Pydantic)

```python
class Requirement(BaseModel):
    id: str                     # "REQ-DCAC-01"
    text: str                   # original sentence
    metric: str                 # "dc_ac_ratio" | "string_voc_tmin" | ...
    operator: Literal["<=", ">=", "==", "range"]
    target: float | tuple[float, float]
    unit: str

class ModuleSpec(BaseModel):
    wp: float; voc: float; vmp: float; isc: float; imp: float
    temp_coeff_voc: float       # %/°C
    length_m: float; width_m: float

class PlantModel(BaseModel):
    capacity_mwp_target: float
    mounting: Literal["fixed_tilt", "tracker"]
    tilt_deg: float; row_pitch_m: float
    module: ModuleSpec
    modules_per_string: int
    strings_per_inverter: int
    inverter_ac_kw: float; inverter_mppt_v: tuple[float, float]
    site_area_m2: float; latitude: float
    cable: CableSpec
    # derived blocks (mirror tool concepts):
    n_tables: int; n_piles: int; n_inverters: int
```

### 5.4 The live-model bridge (from Solar-Design-Configurator)

The CAD tool exposes a single dispatcher:

```csharp
// Orchestration/Orchestrator.cs
public static void Main(string cmd) {
    doc = Application.DocumentManager.MdiActiveDocument;
    doc.SendStringToExecute(cmd, true, false, false);
}
```

Every feature is a command string (from `CLAUDE.md`'s command map), e.g.
`PlaceTables`, `PilePlacement`, `INV_PILING`, `AutoGrouping`, `LTCable`, `sectionmark`, `BOQ_LT_UnderGround`, `CalculateHTSections`.

SpecAlive's **Command-Plan Emitter** produces an ordered, dependency-correct list of these commands plus the parameter payload — the machine-readable "design intent." Because the repo already contains a **`SicaMcpHost`** project, this plan is the natural payload for an MCP tool call that the host relays into `Orchestrator.Main(...)`. **For the hackathon we demo the generated plan + simulation/validation; wiring it into the live plugin is the documented next step** (and requires no change we make to their code — it's an adapter on the host side).

---

## 6. The engineering (what the simulation actually computes)

All standard PV design math — this is the substance that makes it MBSE, not "LLM writes code":

1. **String sizing.** Max modules/string = floor( 1500 V / Voc(Tmin) ), where
   `Voc(Tmin) = Voc_stc · (1 + temp_coeff_voc/100 · (Tmin − 25))`.
   Check Vmp window at Tmax/Tmin lands inside inverter MPPT range.
2. **Counts & ratios.** `DC_kWp = n_modules · Wp / 1000`; `n_inverters = ceil(DC / (AC · target_dcac))`; report actual `DC/AC`.
3. **GCR & shading.** `GCR = collector_width / row_pitch`; inter-row shading loss from a simple solar-geometry model over a representative clear-sky day at the site latitude.
4. **Energy yield.** Clear-sky irradiance profile → plane-of-array irradiance (tilt) → DC power (with temperature derate) → inverter clipping (from DC/AC) → AC energy; roll up to **specific yield (kWh/kWp)** and **PR**.
5. **Cable losses.** Estimate DC/LT/HT lengths from the block layout; `Vdrop% = I·R·L / V`; flag against the drop-limit requirement.
6. **BOQ roll-up.** Table count, pile count, cable lengths, inverter/SCB count — mirroring the tool's own BOQ features so the numbers speak the customer's language.

---

## 7. Demo script (3–4 minutes)

1. **Paste a tender spec** (plain English) into the left pane.
2. SpecAlive extracts **8–10 structured requirements** (show the table).
3. It synthesizes the **plant model** → SysML block diagram appears on the right.
4. **Simulate** → KPI cards + yield curve + shading plot.
5. **Validation matrix**: one requirement is **RED** (e.g. Voc@Tmin = 1512 V > 1500 V).
6. Click **Refine** → SpecAlive drops modules/string 22→21, re-simulates → all **GREEN**.
7. Show the **generated Orchestrator command plan** + JSON design intent, and point to `SicaMcpHost` as the live hook.
8. **Finale:** edit one spec line, watch the whole loop re-run live.

---

## 8. MVP plan (16–23 Sep 2026)

| Day | Deliverable |
|-----|-------------|
| 1–2 | Pydantic schema; Claude spec-extraction; 2 sample specs (fixed-tilt + tracker) |
| 2–4 | Simulation engine (string sizing, counts, DC/AC, yield+clipping, GCR shading, cable drop, BOQ) |
| 4–5 | Validator + traceability matrix + auto-refine loop |
| 5–6 | Streamlit UI: spec editor ↔ live diagram + KPI plots + PASS/FAIL + command plan |
| 6–7 | Polish, sample scenario, pitch deck, record backup demo video |

**Stretch goals:** true `SicaMcpHost` round-trip; optimizer (maximize yield s.t. all requirements); multi-block plant (park-level roll-up); PDF spec ingestion.

---

## 9. Tech stack

- **Language:** Python 3.11
- **AI extraction:** Claude API (`claude-opus-4-8` / `claude-sonnet-5`) with structured output
- **Modeling:** Pydantic v2
- **Simulation:** NumPy, SciPy (optionally `pvlib` for irradiance if allowed)
- **Diagram:** Mermaid (SysML-style), rendered in Streamlit
- **UI:** Streamlit
- **Packaging:** standalone repo at `D:\SpecAlive` — **reads** Solar-Design-Configurator's vocabulary, **writes nothing** into it

---

## 10. Boundaries & non-goals

- **No changes to the Solar-Design-Configurator codebase.** SpecAlive is a separate project; it references the tool's public command/feature vocabulary only.
- Not a replacement for detailed electrical design software; it's a **requirements-driven front-end and validator**.
- Live AutoCAD execution is a documented integration path (via `SicaMcpHost`), not a hackathon-day dependency.

---

*Document status: v1 (pitch + architecture). Next: end-to-end skeleton (schema + simulation + sample spec + CLI) per the MVP plan.*
