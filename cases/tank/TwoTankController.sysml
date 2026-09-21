package TwoTankController {
    // ============================================================
    // SpecAlive-generated SysML v2 model  (L1 Two-Tank Controller)
    // Single source of truth: cases/tank/ir.json
    // Behaviour per DR-02 (D-01..D-09) + CR-004 parameters.
    // ============================================================

    import ScalarValues::*;

    // ---------- interfaces ----------
    port def LiquidPort;
    port def SignalPort;

    // ---------- component part definitions ----------
    part def Source     { port out : LiquidPort; }         // SRC-101
    part def Sink       { port in  : LiquidPort; }          // DRN-101

    part def Tank {                                          // TK-101 / TK-102
        attribute area : Real;          // m2
        attribute level : Real;         // m (state)
        attribute hLow : Real;          // m
        port inlet  : LiquidPort;
        port outlet : LiquidPort;
    }

    part def OnOffValve {                                    // XV-101/102/103
        attribute flow : Real;          // m3/s when open
        attribute open : Boolean;
        port inlet  : LiquidPort;
        port outlet : LiquidPort;
        port cmd    : SignalPort;
    }

    part def LevelTransmitter {                              // LT-101 / LT-102
        port sense : LiquidPort;
        port out   : SignalPort;
    }

    part def Controller {                                    // PLC-101
        port cmdV1 : SignalPort;
        port cmdV2 : SignalPort;
        port cmdV3 : SignalPort;
        port level1 : SignalPort;
        port level2 : SignalPort;
        // operator command events
        event START;
        event STOP;
        event SHUT;   // controlled drain, NOT e-stop
    }

    // ---------- plant assembly ----------
    part def TwoTankPlant {
        part source : Source;
        part tank1 : Tank    { attribute :>> area = 1.20; attribute :>> hLow = 0.05; }
        part tank2 : Tank    { attribute :>> area = 1.40; attribute :>> hLow = 0.05; }
        part valve1 : OnOffValve { attribute :>> flow = 0.0060; }
        part valve2 : OnOffValve { attribute :>> flow = 0.0045; }
        part valve3 : OnOffValve { attribute :>> flow = 0.0050; }
        part lt1 : LevelTransmitter;
        part lt2 : LevelTransmitter;
        part drain : Sink;
        part plc : Controller;

        attribute h1High : Real = 0.80;   // CR-004 (legacy said 0.78)
        attribute wait1 : Real = 10;
        attribute wait2 : Real = 12;      // CR-004
        attribute wait3 : Real = 8;       // CR-004

        // hydraulic path: SRC -> V1 -> T1 -> V2 -> T2 -> V3 -> drain
        connect source.out  to valve1.inlet;
        connect valve1.outlet to tank1.inlet;
        connect tank1.outlet to valve2.inlet;
        connect valve2.outlet to tank2.inlet;
        connect tank2.outlet to valve3.inlet;
        connect valve3.outlet to drain.in;

        // control signals
        connect plc.cmdV1 to valve1.cmd;
        connect plc.cmdV2 to valve2.cmd;
        connect plc.cmdV3 to valve3.cmd;
        connect lt1.out to plc.level1;
        connect lt2.out to plc.level2;
    }

    part plant : TwoTankPlant;

    // ---------- behaviour: sequence state machine ----------
    state def SequenceSM {
        entry; then IDLE;

        state IDLE;
        state FILL;
        state HOLD1;
        state TRANSFER;
        state HOLD2;
        state DRAIN;
        state HOLD3;
        state SHUTTING;

        transition IDLE_to_FILL      first IDLE      accept START            then FILL;
        transition FILL_to_HOLD1     first FILL      if level1 >= 0.80       then HOLD1;
        transition HOLD1_to_TRANSFER first HOLD1     after 10 [s]            then TRANSFER;
        transition TRANSFER_to_HOLD2 first TRANSFER  if level1 <= 0.05       then HOLD2;
        transition HOLD2_to_DRAIN    first HOLD2     after 12 [s]            then DRAIN;
        transition DRAIN_to_HOLD3    first DRAIN     if level2 <= 0.05       then HOLD3;
        transition HOLD3_to_FILL     first HOLD3     after 8 [s]             then FILL;

        // SHUT has precedence (D-01); completes when both low (D-06); resets to IDLE (D-07)
        transition any_to_SHUT       accept SHUT                             then SHUTTING;
        transition SHUT_to_IDLE      first SHUTTING  if (level1 <= 0.05) & (level2 <= 0.05) then IDLE;
    }

    // ---------- requirements ----------
    requirement def <'D-01'> Precedence   { doc /* Command precedence SHUT > STOP > START */ }
    requirement def <'D-02'> StopCloses    { doc /* STOP closes all valves and stores interrupted state */ }
    requirement def <'D-03'> FreezeDelay   { doc /* STOP freezes remaining delay; START resumes it */ }
    requirement def <'D-04'> StartIgnored  { doc /* START while running is ignored */ }
    requirement def <'D-05'> ShutLockout   { doc /* START/STOP during active SHUT are ignored */ }
    requirement def <'D-06'> ShutComplete  { doc /* SHUT complete only when LT-101 and LT-102 both low */ }
    requirement def <'D-07'> ResetIdle     { doc /* After shutdown all valves closed, reset to IDLE */ }
    requirement def <'D-08'> V1V2Interlock { doc /* V1 and V2 never open together */ }
    requirement def <'D-09'> V2V3Interlock { doc /* V2 and V3 not together in auto; SHUT is the only exception */ }

    satisfy requirement <'D-01'> by plant.plc;
    satisfy requirement <'D-02'> by plant.plc;
    satisfy requirement <'D-03'> by plant.plc;
    satisfy requirement <'D-04'> by plant.plc;
    satisfy requirement <'D-05'> by plant.plc;
    satisfy requirement <'D-06'> by plant.plc;
    satisfy requirement <'D-07'> by plant.plc;
    satisfy requirement <'D-08'> by plant.plc;
    satisfy requirement <'D-09'> by plant.plc;
}
