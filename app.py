"""SpecAlive — Streamlit UI.

Run:  streamlit run app.py

Left: paste/edit the spec.  Right: live requirements, SysML diagram, KPIs,
PASS/FAIL matrix, refine log, and the generated Orchestrator command plan.
"""
from __future__ import annotations

import json
import os

import streamlit as st
import streamlit.components.v1 as components

from specalive.pipeline import run

st.set_page_config(page_title="SpecAlive", page_icon="🔆", layout="wide")

DEFAULT_SPEC = os.path.join(os.path.dirname(__file__), "data", "sample_spec_enrich.txt")


def mermaid(code: str, height: int = 300):
    components.html(
        f"""
        <script src="https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.min.js"></script>
        <div class="mermaid">{code}</div>
        <script>mermaid.initialize({{startOnLoad:true, theme:'default'}});</script>
        """,
        height=height,
    )


st.title("🔆 SpecAlive — Specs to a Live Solar Plant Model")
st.caption("Requirements text → validated system model → simulation → command plan "
           "for Solar-Design-Configurator (SicaMcpHost). No changes to the CAD repo.")

with st.sidebar:
    st.header("① Requirements spec")
    default_text = ""
    if os.path.exists(DEFAULT_SPEC):
        with open(DEFAULT_SPEC, "r", encoding="utf-8") as f:
            default_text = f.read()
    spec_text = st.text_area("Paste / edit the spec", value=default_text, height=420)
    mode = st.radio(
        "String-sizing mode",
        ["Naive → catch & fix (demo)", "Cold-Voc-aware (correct from start)"],
        help="Naive sizes strings on nameplate Voc, so the initial model fails the "
             "1500 V limit and the refiner corrects it. Cold-Voc-aware sizes on the "
             "cold-temperature Voc from the start (no refine needed).",
    )
    naive = mode.startswith("Naive")
    go = st.button("▶ Run SpecAlive loop", type="primary", width='stretch')

if not go:
    st.info("Edit the spec on the left and hit **Run SpecAlive loop**. "
            "Try changing a threshold (e.g. Voc limit, DC/AC window) and re-run.")
    st.stop()

res = run(spec_text, naive_string_sizing=naive)

# ---- top KPI strip ----
sim, e = res.sim_final, res.sim_final.extras
c = st.columns(6)
c[0].metric("DC capacity", f"{sim.m('dc_capacity_mwp')} MWp")
c[1].metric("DC/AC", sim.m("dc_ac_ratio"))
c[2].metric("String Voc@Tmin", f"{sim.m('string_voc_tmin')} V")
c[3].metric("GCR", sim.m("gcr"))
c[4].metric("Specific yield", f"{sim.m('specific_yield_kwh_kwp'):.0f}")
c[5].metric("LT drop", f"{sim.m('lt_cable_drop_pct')} %")

left, right = st.columns([1, 1])

with left:
    st.subheader("② Plant system model (SysML)")
    mermaid(res.mermaid, height=340)

    st.subheader("① Extracted requirements")
    st.dataframe(
        [{"id": r.id, "metric": r.metric, "op": r.operator.value,
          "target": str(r.target), "unit": r.unit} for r in res.requirements.requirements],
        width='stretch', hide_index=True,
    )

with right:
    st.subheader("④ / ⑤ Validation")
    n0 = sum(x.passed for x in res.report_initial.checks)
    n1 = sum(x.passed for x in res.report_final.checks)
    st.write(f"**Initial:** {n0}/{len(res.report_initial.checks)} · "
             f"**After refine:** {n1}/{len(res.report_final.checks)} "
             + ("✅ ALL PASS" if res.report_final.all_pass else "❌ failures remain"))
    st.dataframe(
        [{"id": x.req_id, "status": x.status, "detail": x.detail}
         for x in res.report_final.checks],
        width='stretch', hide_index=True,
    )

    st.subheader("③ Refine log")
    if res.steps:
        for s in res.steps:
            st.write(f"- **iter {s.iteration}** ({s.fixed_metric}) → {s.action}")
    else:
        st.write("No changes needed — initial model already satisfied all requirements.")

st.divider()
b1, b2 = st.columns([1, 1])
with b1:
    st.subheader("⑦ BOQ roll-up")
    st.dataframe([{"item": k, "qty": v} for k, v in sim.boq.items()],
                 width='stretch', hide_index=True)
    st.subheader("Representative-day AC output")
    st.line_chart({"AC kW": sim.day_ac_kw})

with b2:
    st.subheader("⑧ Live-model bridge → Orchestrator command plan")
    for i, s in enumerate(res.command_plan, 1):
        dep = f"  _(after {', '.join(s.depends_on)})_" if s.depends_on else ""
        st.write(f"**{i}. `{s.command}`**{dep} — {s.purpose}")
    with st.expander("Design intent (JSON for SicaMcpHost)"):
        st.code(json.dumps(res.design_intent, indent=2), language="json")

st.divider()
st.subheader("⑨ Generated system-model artifacts (SysML v2 + Modelica)")
fn = "".join(c if c.isalnum() else "_" for c in res.model_final.project).strip("_") or "plant"
sm, mo = st.columns([1, 1])
with sm:
    st.markdown("**SysML v2** — part defs, requirements & satisfy relationships")
    st.download_button("⬇ Download .sysml", res.sysml_v2, file_name=f"{fn}.sysml",
                       mime="text/plain", width="stretch")
    st.code(res.sysml_v2, language="text")
with mo:
    st.markdown("**Modelica** — runnable one-day energy model (OpenModelica)")
    st.download_button("⬇ Download .mo", res.modelica, file_name=f"{fn}.mo",
                       mime="text/plain", width="stretch")
    st.code(res.modelica, language="modelica")
