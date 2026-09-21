model TwoTankController
  "L1 Two-Tank sequencing controller (SpecAlive-generated).
   Source-of-truth: cases/tank/ir.json. Behaviour per DR-02 decisions D-01..D-09
   and CR-004 parameters. See cases/tank/ASSUMPTIONS.md for traceability.
   Self-contained, simulatable 0..900 s (StopTime=900)."

  // ============================================================
  // Parameters  (traced to engineering data / CR-004; see ASSUMPTIONS.md)
  // ============================================================
  parameter Real A1(unit = "m2") = 1.20   "Tank 1 (TK-101) cross-section area";
  parameter Real A2(unit = "m2") = 1.40   "Tank 2 (TK-102) cross-section area";
  parameter Real h0(unit = "m") = 0.05    "Initial level, both tanks";
  parameter Real h1High(unit = "m") = 0.80 "T1 high setpoint (CR-004; legacy said 0.78)";
  parameter Real h1Low(unit = "m") = 0.05  "T1 low setpoint (LT-101)";
  parameter Real h2Low(unit = "m") = 0.05  "T2 low setpoint (LT-102)";
  parameter Real qFill(unit = "m3/s") = 0.0060     "Source->T1 via V1 (XV-101)";
  parameter Real qTransfer(unit = "m3/s") = 0.0045 "T1->T2 via V2 (XV-102)";
  parameter Real qDrain(unit = "m3/s") = 0.0050    "T2->drain via V3 (XV-103)";
  parameter Real wait1(unit = "s") = 10 "HOLD1, post-fill dwell";
  parameter Real wait2(unit = "s") = 12 "HOLD2, post-transfer dwell (CR-004)";
  parameter Real wait3(unit = "s") = 8  "HOLD3, inter-cycle dwell (CR-004)";

  // ============================================================
  // Sequence state
  // ============================================================
  type Step = enumeration(IDLE, FILL, HOLD1, TRANSFER, HOLD2, DRAIN, HOLD3);

  // Continuous states
  Real h1(start = h0, fixed = true, unit = "m") "Tank 1 level (LT-101)";
  Real h2(start = h0, fixed = true, unit = "m") "Tank 2 level (LT-102)";
  Real tRun(start = 0, fixed = true, unit = "s")
    "Hold-time accumulator; advances only inside a HOLD and only when not paused";

  // Discrete controller state
  discrete Step seq(start = Step.IDLE, fixed = true) "Active sequence step";
  discrete Boolean paused(start = false, fixed = true) "STOP active (process frozen)";
  discrete Boolean shutting(start = false, fixed = true) "SHUT active (controlled drain)";
  discrete Real tMark(start = 0, fixed = true, unit = "s") "tRun captured at HOLD entry";

  // Valve commands (outputs). XV-101/102/103.
  Boolean valve1 "XV-101 source->T1";
  Boolean valve2 "XV-102 T1->T2";
  Boolean valve3 "XV-103 T2->drain";

equation
  // ---- valve command logic ----
  // D-08: V1 and V2 never open together (FILL vs TRANSFER are exclusive steps).
  // D-09: V2 and V3 not together in auto; SHUT is the only exception (V2+V3 open).
  // STOP (paused) closes all valves (D-02). During SHUT, V1 stays closed (DR-02).
  valve1 = (seq == Step.FILL) and (not paused) and (not shutting);
  valve2 = ((seq == Step.TRANSFER) or shutting) and (not paused);
  valve3 = ((seq == Step.DRAIN) or shutting) and (not paused);

  // ---- hydraulics ----
  der(h1) = (if valve1 then qFill else 0.0) / A1
          - (if valve2 then qTransfer else 0.0) / A1;
  der(h2) = (if valve2 then qTransfer else 0.0) / A2
          - (if valve3 then qDrain else 0.0) / A2;

  // ---- hold-time accumulator (freezes on STOP -> implements D-03) ----
  der(tRun) = if (not paused) and
                 (seq == Step.HOLD1 or seq == Step.HOLD2 or seq == Step.HOLD3)
              then 1.0 else 0.0;

algorithm
  // ============================================================
  // Operator commands.  Test-harness edges (operator shift notes):
  //   START @20, STOP @220, START @280, STOP @650, SHUT @700.
  // Precedence SHUT > STOP > START (D-01) enforced by guards below.
  // NOTE: these fixed times are TEST STIMULUS, not controller logic
  //       (see ASSUMPTIONS.md - the controller keys off command edges).
  // ============================================================
  when time >= 20 then                       // START #1
    if (not shutting) and (not paused) and (pre(seq) == Step.IDLE) then
      seq := Step.FILL;                       // begin a new fill cycle (D-07)
      tMark := tRun;
    end if;
  end when;

  when time >= 220 then                       // STOP #1
    if not pre(shutting) then paused := true; end if;   // D-02, freeze (D-03)
  end when;

  when time >= 280 then                       // START #2 (resume)
    if not pre(shutting) then paused := false; end if;  // D-03 resume; D-04 no restart
  end when;

  when time >= 650 then                       // STOP #2
    if not pre(shutting) then paused := true; end if;
  end when;

  when time >= 700 then                       // SHUT (D-01 precedence, D-05)
    shutting := true;
    paused := false;
  end when;

  // ============================================================
  // Automatic sequence transitions (only while running: not shutting).
  // pre(seq) guards prevent same-event re-triggering.
  // ============================================================
  when (h1 >= h1High) and (pre(seq) == Step.FILL) and (not pre(shutting)) then
    seq := Step.HOLD1; tMark := tRun;
  end when;

  when (tRun - tMark >= wait1) and (pre(seq) == Step.HOLD1) and (not pre(shutting)) then
    seq := Step.TRANSFER;
  end when;

  when (h1 <= h1Low) and (pre(seq) == Step.TRANSFER) and (not pre(shutting)) then
    seq := Step.HOLD2; tMark := tRun;
  end when;

  when (tRun - tMark >= wait2) and (pre(seq) == Step.HOLD2) and (not pre(shutting)) then
    seq := Step.DRAIN;
  end when;

  when (h2 <= h2Low) and (pre(seq) == Step.DRAIN) and (not pre(shutting)) then
    seq := Step.HOLD3; tMark := tRun;
  end when;

  when (tRun - tMark >= wait3) and (pre(seq) == Step.HOLD3) and (not pre(shutting)) then
    seq := Step.FILL; tMark := tRun;          // next cycle
  end when;

  // ---- SHUT completion (D-06): both tanks at/below low -> reset to IDLE (D-07) ----
  when pre(shutting) and (h1 <= h1Low) and (h2 <= h2Low) then
    shutting := false;
    seq := Step.IDLE;
  end when;

annotation(
  experiment(StartTime = 0, StopTime = 900, Interval = 1, Tolerance = 1e-6),
  Documentation(info = "<html>
  <p>Two-tank sequencing controller. Flow: source -&gt; V1 -&gt; TK-101 -&gt; V2 -&gt;
  TK-102 -&gt; V3 -&gt; drain, sequenced by a PLC-101 state machine
  IDLE-&gt;FILL-&gt;HOLD1-&gt;TRANSFER-&gt;HOLD2-&gt;DRAIN-&gt;HOLD3.</p>
  <p>SHUT is a controlled drain (V2+V3 together, V1 closed), completing when both
  levels reach low. STOP freezes the process and the remaining hold delay; START
  resumes it. Generated by SpecAlive from the L1 dataset.</p>
  </html>"));
end TwoTankController;
