"""Command-Plan Emitter — the live-model bridge.

Turns a validated PlantModel into the ordered list of Solar-Design-Configurator
Orchestrator commands (from that tool's command map) that would build the CAD
layout, plus a machine-readable "design intent" JSON payload suitable for an MCP
tool call relayed by SicaMcpHost -> Orchestrator.Main(cmd).

We DO NOT execute AutoCAD here; we emit the plan. Wiring it into the live
plugin is the documented next step and needs no change to that repo (it's an
adapter on the host side).
"""
from __future__ import annotations

from dataclasses import dataclass, field
from typing import Dict, List

from .schema import Mounting, PlantModel


@dataclass
class PlanStep:
    command: str          # AutoCAD command string (as sent by Orchestrator.Main)
    purpose: str
    depends_on: List[str] = field(default_factory=list)


# ordered, dependency-correct pipeline of real tool commands
def build_command_plan(m: PlantModel) -> List[PlanStep]:
    steps = [
        PlanStep("PlaceTables", "Place MMS tables across the site boundary"),
        PlanStep("SOLARSHADOW", "Optimise row pitch for inter-row shading", ["PlaceTables"]),
        PlanStep("IntExtMarkup", "Classify exterior/interior tables", ["PlaceTables"]),
        PlanStep("PilePlacement", "Place piles per table config", ["PlaceTables"]),
        PlanStep("INV_PILING", "Place inverter piles", ["PilePlacement"]),
        PlanStep("AutoGrouping", "Group tables into inverter/SCB sets", ["IntExtMarkup"]),
        PlanStep("InverterTagging", "Tag inverters", ["AutoGrouping"]),
        PlanStep("LTCable", "Route LT cabling", ["AutoGrouping"]),
        PlanStep("sectionmark", "Mark LT cable sections", ["LTCable"]),
        PlanStep("BOQ_LT_UnderGround", "Generate LT BOQ", ["sectionmark"]),
    ]
    if m.mounting == Mounting.TRACKER:
        steps.insert(1, PlanStep("TableDimension", "Dimension tracker tables", ["PlaceTables"]))
    return steps


def design_intent(m: PlantModel) -> Dict:
    """Machine-readable payload for SicaMcpHost / an MCP tool call."""
    return {
        "project": m.project,
        "mounting": m.mounting.value,
        "table_name": m.table_name,
        "parameters": {
            "capacity_mwp": m.capacity_mwp_target,
            "tilt_deg": m.tilt_deg,
            "row_pitch_m": m.row_pitch_m,
            "modules_per_string": m.modules_per_string,
            "target_dc_ac": m.target_dc_ac,
        },
        "counts": {
            "modules": m.n_modules,
            "strings": m.n_strings,
            "inverters": m.n_inverters,
            "tables": m.n_tables,
            "piles": m.n_piles,
        },
        "command_plan": [
            {"command": s.command, "purpose": s.purpose, "depends_on": s.depends_on}
            for s in build_command_plan(m)
        ],
    }
