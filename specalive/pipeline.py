"""End-to-end SpecAlive loop: text -> model -> sim -> validate -> refine -> plan."""
from __future__ import annotations

from dataclasses import dataclass
from typing import List

import json
import os

from .commands import build_command_plan, design_intent
from .diagram import to_mermaid
from .extract import extract
from .modelica import to_modelica
from .refine import RefineStep, refine
from .schema import PlantModel, RequirementSet
from .simulate import SimResult, simulate
from .synthesize import synthesize
from .sysml import to_sysml_v2
from .validate import ValidationReport, validate


@dataclass
class PipelineResult:
    requirements: RequirementSet
    model_initial: PlantModel
    report_initial: ValidationReport
    model_final: PlantModel
    report_final: ValidationReport
    sim_final: SimResult
    steps: List[RefineStep]
    mermaid: str
    design_intent: dict
    sysml_v2: str
    modelica: str

    @property
    def command_plan(self):
        return build_command_plan(self.model_final)

    def write_outputs(self, out_dir: str) -> dict:
        """Write all generated artifacts to out_dir; return {label: path}."""
        os.makedirs(out_dir, exist_ok=True)
        name = "".join(c if c.isalnum() else "_" for c in self.model_final.project).strip("_") or "plant"
        files = {
            "SysML v2": (f"{name}.sysml", self.sysml_v2),
            "Modelica": (f"{name}.mo", self.modelica),
            "Design intent (JSON)": (f"{name}.design_intent.json",
                                     json.dumps(self.design_intent, indent=2)),
            "Diagram (Mermaid)": (f"{name}.mmd", self.mermaid),
        }
        written = {}
        for label, (fn, content) in files.items():
            path = os.path.join(out_dir, fn)
            with open(path, "w", encoding="utf-8") as f:
                f.write(content)
            written[label] = path
        return written


def run(spec_text: str, naive_string_sizing: bool = True) -> PipelineResult:
    reqs, hints = extract(spec_text)
    model0 = synthesize(reqs, hints, naive_string_sizing)
    report0 = validate(reqs, simulate(model0))
    model1, report1, steps = refine(model0, reqs)
    sim1 = simulate(model1)
    return PipelineResult(
        requirements=reqs,
        model_initial=model0,
        report_initial=report0,
        model_final=model1,
        report_final=report1,
        sim_final=sim1,
        steps=steps,
        mermaid=to_mermaid(model1),
        design_intent=design_intent(model1),
        sysml_v2=to_sysml_v2(model1, reqs, sim1),
        modelica=to_modelica(model1, sim1),
    )
