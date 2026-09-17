"""SysML-flavored block diagram of the plant model, as Mermaid text.

Renders the plant as connected blocks (Site -> Array -> Strings -> Inverters ->
LT -> Grid) with key parameters, mirroring the CAD tool's own concepts.
"""
from __future__ import annotations

from .schema import PlantModel


def to_mermaid(m: PlantModel) -> str:
    mod = m.module
    return f"""flowchart LR
    SITE["🌍 Site<br/>lat {m.site.latitude}°, area {m.site.area_m2:.0f} m²<br/>GHI {m.site.ghi_kwh_m2_day} kWh/m²/day"]
    ARR["▦ MMS Tables ({m.mounting.value})<br/>{m.n_tables} × {m.table_name}<br/>tilt {m.tilt_deg}°, pitch {m.row_pitch_m} m"]
    MOD["🔆 Modules<br/>{m.n_modules} × {mod.wp:.0f} Wp<br/>{m.modules_per_table}/table"]
    STR["🔗 Strings<br/>{m.n_strings} × {m.modules_per_string} modules"]
    INV["⚡ Inverters<br/>{m.n_inverters} × {m.inverter.ac_kw:.0f} kVA<br/>DC/AC {m.target_dc_ac}"]
    LT["🔌 LT Cabling<br/>{m.cable.lt_area_mm2:.0f} mm² × {m.cable.n_parallel}"]
    PILE["⏚ Piling<br/>{m.n_piles} piles"]
    GRID["🏭 Grid / MV"]

    SITE --> ARR --> MOD --> STR --> INV --> LT --> GRID
    ARR -.-> PILE
"""
