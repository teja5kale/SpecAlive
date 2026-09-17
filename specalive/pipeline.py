"""End-to-end SpecAlive loop: text -> model -> sim -> validate -> refine -> plan."""
from __future__ import annotations

from dataclasses import dataclass
from typing import List

from .commands import build_command_plan, design_intent
from .diagram import to_mermaid
from .extract import extract
from .refine import RefineStep, refine
from .schema import PlantModel, RequirementSet
from .simulate import SimResult, simulate
from .synthesize import synthesize
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

    @property
    def command_plan(self):
        return build_command_plan(self.model_final)


def run(spec_text: str) -> PipelineResult:
    reqs, hints = extract(spec_text)
    model0 = synthesize(reqs, hints)
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
    )
