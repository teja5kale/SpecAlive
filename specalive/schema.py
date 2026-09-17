"""Core data model for SpecAlive.

Three layers:
  * RequirementSet  — what the spec *asks for* (verifiable "shall" statements)
  * ModuleSpec / InverterSpec / CableSpec / SiteSpec — component parameters
  * PlantModel      — the synthesized system model (the MBSE single source of truth)

Every Requirement carries a machine-checkable (metric, operator, target) so the
Validator can compare it to a simulated KPI with zero ambiguity.
"""
from __future__ import annotations

from enum import Enum
from typing import List, Optional, Tuple, Union

from pydantic import BaseModel, Field


# --------------------------------------------------------------------------- #
# Requirements
# --------------------------------------------------------------------------- #
class Op(str, Enum):
    LE = "<="        # metric <= target
    GE = ">="        # metric >= target
    EQ = "=="        # metric == target (within tolerance)
    RANGE = "range"  # low <= metric <= high  (target is a (low, high) tuple)


# Canonical metric keys the simulator knows how to compute.
KNOWN_METRICS = {
    "dc_capacity_mwp",
    "dc_ac_ratio",
    "string_voc_tmin",
    "gcr",
    "row_pitch_m",
    "lt_cable_drop_pct",
    "specific_yield_kwh_kwp",
    "site_area_used_m2",
}


class Requirement(BaseModel):
    id: str                                        # e.g. "REQ-DCAC-06"
    text: str                                      # original sentence
    metric: str                                    # one of KNOWN_METRICS
    operator: Op
    target: Union[float, Tuple[float, float]]
    unit: str = ""

    def is_range(self) -> bool:
        return self.operator == Op.RANGE


class RequirementSet(BaseModel):
    project: str = "Untitled"
    requirements: List[Requirement] = Field(default_factory=list)

    def by_metric(self, metric: str) -> Optional[Requirement]:
        for r in self.requirements:
            if r.metric == metric:
                return r
        return None


# --------------------------------------------------------------------------- #
# Component specs
# --------------------------------------------------------------------------- #
class ModuleSpec(BaseModel):
    name: str = "Generic 545Wp"
    wp: float = 545.0
    voc: float = 49.5            # V at STC
    vmp: float = 41.8            # V at STC
    isc: float = 13.90           # A at STC
    imp: float = 13.04           # A at STC
    temp_coeff_voc: float = -0.27  # %/degC (negative)
    length_m: float = 2.279
    width_m: float = 1.134


class InverterSpec(BaseModel):
    name: str = "Central 4000kVA"
    ac_kw: float = 4000.0
    mppt_low_v: float = 875.0
    mppt_high_v: float = 1325.0
    max_system_v: float = 1500.0


class CableSpec(BaseModel):
    lt_area_mm2: float = 300.0       # LT feeder cross-section (per run)
    lt_length_m: float = 150.0       # representative one-way length
    lt_current_a: float = 800.0      # representative total feeder current
    lt_voltage_v: float = 415.0      # LT AC line voltage
    copper: bool = False             # False = aluminium
    n_parallel: int = 4              # runs in parallel per feeder


class SiteSpec(BaseModel):
    latitude: float = 23.85          # degrees N
    min_temp_c: float = 5.0
    max_temp_c: float = 65.0         # module (cell) temp for Vmp check
    ghi_kwh_m2_day: float = 5.6      # site global horizontal irradiation
    area_m2: float = 40000.0


# --------------------------------------------------------------------------- #
# System model
# --------------------------------------------------------------------------- #
class Mounting(str, Enum):
    FIXED_TILT = "fixed_tilt"
    TRACKER = "tracker"


class PlantModel(BaseModel):
    """The synthesized, parameterized plant — the single source of truth.

    Fields above the divider are *design decisions*; fields below (n_*) are
    *derived* by the synthesizer/simulator and mirror the CAD tool's own
    block concepts (MMS tables, strings, inverter groups, piles).
    """
    project: str = "Untitled"
    capacity_mwp_target: float = 5.0
    mounting: Mounting = Mounting.FIXED_TILT
    tilt_deg: float = 25.0
    row_pitch_m: float = 6.0

    module: ModuleSpec = Field(default_factory=ModuleSpec)
    inverter: InverterSpec = Field(default_factory=InverterSpec)
    cable: CableSpec = Field(default_factory=CableSpec)
    site: SiteSpec = Field(default_factory=SiteSpec)

    modules_per_string: int = 28
    target_dc_ac: float = 1.25          # design intent, refined against req window

    # ---- derived (filled in by synthesize/simulate) ----
    n_modules: int = 0
    n_strings: int = 0
    n_inverters: int = 0
    n_tables: int = 0
    n_piles: int = 0
    table_name: str = "MMS Table (32.2920 x 4.5760)"
    modules_per_table: int = 0
