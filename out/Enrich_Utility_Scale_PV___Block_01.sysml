package EnrichUtilityScalePVBlock01 {
    // ============================================================
    // SpecAlive-generated SysML v2 system model
    // Source: validated PlantModel for "Enrich Utility-Scale PV — Block-01"
    // ============================================================

    // ---------- component part definitions ----------
    part def PVModule {
        attribute wp : Real = 550.0;            // Wp
        attribute voc : Real = 49.9;          // V @ STC
        attribute vmp : Real = 41.5;          // V @ STC
        attribute tempCoeffVoc : Real = -0.28; // %/degC
        attribute lengthM : Real = 2.279;
        attribute widthM : Real = 1.134;
    }

    part def MMSTable {
        doc /* MMS Table (32.2920 x 4.5760) (fixed_tilt) */
        attribute modulesPerTable : Integer = 56;
        attribute pilesPerTable : Integer = 12;
    }

    part def PVString {
        attribute modulesPerString : Integer = 28;
        attribute stringVocTmin : Real = 1475.4; // V
    }

    part def Inverter {
        attribute acKW : Real = 4000.0;
        attribute mpptLowV : Real = 875.0;
        attribute mpptHighV : Real = 1325.0;
        attribute maxSystemV : Real = 1500.0;
    }

    // ---------- plant assembly ----------
    part def PVPlant {
        part modules : PVModule[9100];
        part tables : MMSTable[163];
        part strings : PVString[325];
        part inverters : Inverter[1];

        attribute tiltDeg : Real = 24.0;
        attribute rowPitchM : Real = 10.169;
        attribute targetDcAc : Real = 1.25;
    }

    part plant : PVPlant;

    // ---------- analysis: simulated KPIs (from SpecAlive engine) ----------
    part def PlantKPI {
        attribute dc_capacity_mwp = 5.005;
        attribute dc_ac_ratio = 1.251;
        attribute string_voc_tmin = 1475.4;
        attribute gcr = 0.45;
        attribute row_pitch_m = 10.169;
        attribute lt_cable_drop_pct = 1.19;
        attribute specific_yield_kwh_kwp = 1783.0;
        attribute site_area_used_m2 = 53526.0;
        attribute pr : Real = 0.796;
        attribute specificYield : Real = 1783.0;
    }
    part plantKPI : PlantKPI;

    // ---------- requirements ----------
    requirement def REQ_CAP_01 {
        doc /* Target DC capacity 5.0 MWp */
        attribute targetMetric : String = "dc_capacity_mwp";
        require constraint { plantKPI::dc_capacity_mwp >= 4.9 }
    }
    requirement def REQ_VOC_04 {
        doc /* String Voc at min temp shall not exceed 1500.0 V */
        attribute targetMetric : String = "string_voc_tmin";
        require constraint { plantKPI::string_voc_tmin <= 1500.0 }
    }
    requirement def REQ_DCAC_06 {
        doc /* DC/AC ratio between 1.20 and 1.30 */
        attribute targetMetric : String = "dc_ac_ratio";
        require constraint { plantKPI::dc_ac_ratio >= 1.2 and plantKPI::dc_ac_ratio <= 1.3 }
    }
    requirement def REQ_GCR_07 {
        doc /* GCR shall not exceed 0.45 */
        attribute targetMetric : String = "gcr";
        require constraint { plantKPI::gcr <= 0.45 }
    }
    requirement def REQ_PITCH_08 {
        doc /* Row pitch >= 6.0 m */
        attribute targetMetric : String = "row_pitch_m";
        require constraint { plantKPI::row_pitch_m >= 6.0 }
    }
    requirement def REQ_DROP_09 {
        doc /* LT cable drop <= 2.0 % */
        attribute targetMetric : String = "lt_cable_drop_pct";
        require constraint { plantKPI::lt_cable_drop_pct <= 2.0 }
    }
    requirement def REQ_YIELD_10 {
        doc /* Specific yield >= 1550.0 kWh/kWp */
        attribute targetMetric : String = "specific_yield_kwh_kwp";
        require constraint { plantKPI::specific_yield_kwh_kwp >= 1550.0 }
    }
    requirement def REQ_AREA_11 {
        doc /* Site area used <= 60000.0 m2 */
        attribute targetMetric : String = "site_area_used_m2";
        require constraint { plantKPI::site_area_used_m2 <= 60000.0 }
    }

    // ---------- satisfy relationships ----------
    satisfy requirement REQ_CAP_01 by plant;
    satisfy requirement REQ_VOC_04 by plant;
    satisfy requirement REQ_DCAC_06 by plant;
    satisfy requirement REQ_GCR_07 by plant;
    satisfy requirement REQ_PITCH_08 by plant;
    satisfy requirement REQ_DROP_09 by plant;
    satisfy requirement REQ_YIELD_10 by plant;
    satisfy requirement REQ_AREA_11 by plant;
}
