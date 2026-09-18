"""SysML v2 textual emitter.

Renders the PlantModel + RequirementSet as a SysML v2 model: part defs with
attributes, a plant assembly with typed parts and multiplicities, requirement
defs with constraints, and satisfy relationships. Grounded in the *validated*
model + simulated KPIs so the constraints reference concrete values.

Target: SysML v2 (KerML-based textual notation), OMG 2023+.
"""
from __future__ import annotations

from .schema import PlantModel, Op, RequirementSet
from .simulate import SimResult

_OP_TXT = {Op.LE: "<=", Op.GE: ">=", Op.EQ: "==", Op.RANGE: "in"}


def _req_constraint(metric: str, op: Op, target) -> str:
    lhs = f"plantKPI::{metric}"
    if op == Op.RANGE:
        lo, hi = target
        return f"{lhs} >= {lo} and {lhs} <= {hi}"
    return f"{lhs} {_OP_TXT[op]} {target}"


def to_sysml_v2(m: PlantModel, reqs: RequirementSet, sim: SimResult) -> str:
    e = sim.extras
    pkg = "".join(c for c in m.project if c.isalnum()) or "SolarPlant"

    req_defs = []
    satisfies = []
    for r in reqs.requirements:
        rid = r.id.replace("-", "_")
        con = _req_constraint(r.metric, r.operator, r.target)
        req_defs.append(f"""    requirement def {rid} {{
        doc /* {r.text} */
        attribute targetMetric : String = "{r.metric}";
        require constraint {{ {con} }}
    }}""")
        satisfies.append(f"    satisfy requirement {rid} by plant;")

    kpi_lines = "\n".join(
        f"        attribute {k} = {v};" for k, v in sim.metrics.items()
    )

    return f"""package {pkg} {{
    // ============================================================
    // SpecAlive-generated SysML v2 system model
    // Source: validated PlantModel for "{m.project}"
    // ============================================================

    // ---------- component part definitions ----------
    part def PVModule {{
        attribute wp : Real = {m.module.wp};            // Wp
        attribute voc : Real = {m.module.voc};          // V @ STC
        attribute vmp : Real = {m.module.vmp};          // V @ STC
        attribute tempCoeffVoc : Real = {m.module.temp_coeff_voc}; // %/degC
        attribute lengthM : Real = {m.module.length_m};
        attribute widthM : Real = {m.module.width_m};
    }}

    part def MMSTable {{
        doc /* {m.table_name} ({m.mounting.value}) */
        attribute modulesPerTable : Integer = {m.modules_per_table};
        attribute pilesPerTable : Integer = {m.n_piles // max(1, m.n_tables)};
    }}

    part def PVString {{
        attribute modulesPerString : Integer = {m.modules_per_string};
        attribute stringVocTmin : Real = {sim.m('string_voc_tmin')}; // V
    }}

    part def Inverter {{
        attribute acKW : Real = {m.inverter.ac_kw};
        attribute mpptLowV : Real = {m.inverter.mppt_low_v};
        attribute mpptHighV : Real = {m.inverter.mppt_high_v};
        attribute maxSystemV : Real = {m.inverter.max_system_v};
    }}

    // ---------- plant assembly ----------
    part def PVPlant {{
        part modules : PVModule[{m.n_modules}];
        part tables : MMSTable[{m.n_tables}];
        part strings : PVString[{m.n_strings}];
        part inverters : Inverter[{m.n_inverters}];

        attribute tiltDeg : Real = {m.tilt_deg};
        attribute rowPitchM : Real = {m.row_pitch_m};
        attribute targetDcAc : Real = {m.target_dc_ac};
    }}

    part plant : PVPlant;

    // ---------- analysis: simulated KPIs (from SpecAlive engine) ----------
    part def PlantKPI {{
{kpi_lines}
        attribute pr : Real = {e['pr']};
        attribute specificYield : Real = {sim.m('specific_yield_kwh_kwp')};
    }}
    part plantKPI : PlantKPI;

    // ---------- requirements ----------
{chr(10).join(req_defs)}

    // ---------- satisfy relationships ----------
{chr(10).join(satisfies)}
}}
"""
