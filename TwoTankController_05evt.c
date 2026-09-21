/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "TwoTankController_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void TwoTankController_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *TwoTankController_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"time >= 20.0",
  "time >= 220.0",
  "time >= 280.0",
  "time >= 650.0",
  "time >= 700.0",
  "h1 >= h1High and pre(seq) == Step.FILL and not pre(shutting)",
  "tRun - tMark >= wait1 and pre(seq) == Step.HOLD1 and not pre(shutting)",
  "h1 <= h1Low and pre(seq) == Step.TRANSFER and not pre(shutting)",
  "tRun - tMark >= wait2 and pre(seq) == Step.HOLD2 and not pre(shutting)",
  "h2 <= h2Low and pre(seq) == Step.DRAIN and not pre(shutting)",
  "tRun - tMark >= wait3 and pre(seq) == Step.HOLD3 and not pre(shutting)",
  "pre(shutting) and h1 <= h1Low and h2 <= h2Low"};
  static const int occurEqs0[] = {1,19};
  static const int occurEqs1[] = {1,19};
  static const int occurEqs2[] = {1,19};
  static const int occurEqs3[] = {1,19};
  static const int occurEqs4[] = {1,19};
  static const int occurEqs5[] = {1,19};
  static const int occurEqs6[] = {1,19};
  static const int occurEqs7[] = {1,19};
  static const int occurEqs8[] = {1,19};
  static const int occurEqs9[] = {1,19};
  static const int occurEqs10[] = {1,19};
  static const int occurEqs11[] = {1,19};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2,occurEqs3,occurEqs4,occurEqs5,occurEqs6,occurEqs7,occurEqs8,occurEqs9,occurEqs10,occurEqs11};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void TwoTankController_eqFunction_19(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_20(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_21(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_22(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_23(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_24(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_25(DATA* data, threadData_t *threadData);

int TwoTankController_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  static void (*const eqFunctions[7])(DATA*, threadData_t*) = {
    TwoTankController_eqFunction_19,
    TwoTankController_eqFunction_20,
    TwoTankController_eqFunction_21,
    TwoTankController_eqFunction_22,
    TwoTankController_eqFunction_23,
    TwoTankController_eqFunction_24,
    TwoTankController_eqFunction_25
  };
  
  for (int id = 0; id < 7; id++) {
    eqFunctions[id](data, threadData);
  }
  
  return 0;
}

int TwoTankController_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  const int *equationIndexes = NULL;

  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  modelica_boolean tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  modelica_boolean tmp15;
  modelica_real tmp16;
  modelica_real tmp17;
  modelica_boolean tmp18;
  modelica_real tmp19;
  modelica_real tmp20;
  modelica_boolean tmp21;
  modelica_real tmp22;
  modelica_real tmp23;
  modelica_boolean tmp24;
  modelica_real tmp25;
  modelica_real tmp26;
  modelica_boolean tmp27;
  modelica_real tmp28;
  modelica_real tmp29;
  modelica_boolean tmp30;
  modelica_real tmp31;
  modelica_real tmp32;
  modelica_boolean tmp33;
  modelica_real tmp34;
  modelica_real tmp35;
  modelica_boolean tmp36;
  modelica_real tmp37;
  modelica_real tmp38;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp1 = 1.0;
  tmp2 = 20.0;
  tmp0 = GreaterEqZC(data->localData[0]->timeValue, 20.0, tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[start_index] = (tmp0) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp4 = 1.0;
  tmp5 = 220.0;
  tmp3 = GreaterEqZC(data->localData[0]->timeValue, 220.0, tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  gout[start_index] = (tmp3) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp7 = 1.0;
  tmp8 = 280.0;
  tmp6 = GreaterEqZC(data->localData[0]->timeValue, 280.0, tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  gout[start_index] = (tmp6) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp10 = 1.0;
  tmp11 = 650.0;
  tmp9 = GreaterEqZC(data->localData[0]->timeValue, 650.0, tmp10, tmp11, data->simulationInfo->storedRelations[3]);
  gout[start_index] = (tmp9) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp13 = 1.0;
  tmp14 = 700.0;
  tmp12 = GreaterEqZC(data->localData[0]->timeValue, 700.0, tmp13, tmp14, data->simulationInfo->storedRelations[4]);
  gout[start_index] = (tmp12) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp16 = 1.0;
  tmp17 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3]] /* h1High PARAM */));
  tmp15 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3]] /* h1High PARAM */), tmp16, tmp17, data->simulationInfo->storedRelations[5]);
  gout[start_index] = (((tmp15 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 2)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp19 = 2.0;
  tmp20 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[9]] /* wait1 PARAM */));
  tmp18 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[9]] /* wait1 PARAM */), tmp19, tmp20, data->simulationInfo->storedRelations[6]);
  gout[start_index] = (((tmp18 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 3)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp22 = 1.0;
  tmp23 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */));
  tmp21 = LessEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */), tmp22, tmp23, data->simulationInfo->storedRelations[7]);
  gout[start_index] = (((tmp21 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 4)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp25 = 2.0;
  tmp26 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[10]] /* wait2 PARAM */));
  tmp24 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[10]] /* wait2 PARAM */), tmp25, tmp26, data->simulationInfo->storedRelations[8]);
  gout[start_index] = (((tmp24 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 5)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp28 = 1.0;
  tmp29 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */));
  tmp27 = LessEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */), tmp28, tmp29, data->simulationInfo->storedRelations[9]);
  gout[start_index] = (((tmp27 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 6)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp31 = 2.0;
  tmp32 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[11]] /* wait3 PARAM */));
  tmp30 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[11]] /* wait3 PARAM */), tmp31, tmp32, data->simulationInfo->storedRelations[10]);
  gout[start_index] = (((tmp30 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 7)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp34 = 1.0;
  tmp35 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */));
  tmp33 = LessEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */), tmp34, tmp35, data->simulationInfo->storedRelations[11]);
  tmp37 = 1.0;
  tmp38 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */));
  tmp36 = LessEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */), tmp37, tmp38, data->simulationInfo->storedRelations[12]);
  gout[start_index] = ((((data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */) && tmp33) && tmp36)) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  return 0;
}

const char *TwoTankController_relationDescription(int i)
{
  const char *res[] = {"time >= 20.0",
  "time >= 220.0",
  "time >= 280.0",
  "time >= 650.0",
  "time >= 700.0",
  "h1 >= h1High",
  "tRun - tMark >= wait1",
  "h1 <= h1Low",
  "tRun - tMark >= wait2",
  "h2 <= h2Low",
  "tRun - tMark >= wait3",
  "h1 <= h1Low",
  "h2 <= h2Low"};
  return res[i];
}

int TwoTankController_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  const int *equationIndexes = NULL;

  modelica_boolean tmp39;
  modelica_real tmp40;
  modelica_real tmp41;
  modelica_boolean tmp42;
  modelica_real tmp43;
  modelica_real tmp44;
  modelica_boolean tmp45;
  modelica_real tmp46;
  modelica_real tmp47;
  modelica_boolean tmp48;
  modelica_real tmp49;
  modelica_real tmp50;
  modelica_boolean tmp51;
  modelica_real tmp52;
  modelica_real tmp53;
  modelica_boolean tmp54;
  modelica_real tmp55;
  modelica_real tmp56;
  modelica_boolean tmp57;
  modelica_real tmp58;
  modelica_real tmp59;
  modelica_boolean tmp60;
  modelica_real tmp61;
  modelica_real tmp62;
  modelica_boolean tmp63;
  modelica_real tmp64;
  modelica_real tmp65;
  modelica_boolean tmp66;
  modelica_real tmp67;
  modelica_real tmp68;
  modelica_boolean tmp69;
  modelica_real tmp70;
  modelica_real tmp71;
  modelica_boolean tmp72;
  modelica_real tmp73;
  modelica_real tmp74;
  modelica_boolean tmp75;
  modelica_real tmp76;
  modelica_real tmp77;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
  if(evalforZeroCross) {
    start_index = current_index;
    tmp40 = 1.0;
    tmp41 = 20.0;
    tmp39 = GreaterEqZC(data->localData[0]->timeValue, 20.0, tmp40, tmp41, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp39;
    current_index++;

    start_index = current_index;
    tmp43 = 1.0;
    tmp44 = 220.0;
    tmp42 = GreaterEqZC(data->localData[0]->timeValue, 220.0, tmp43, tmp44, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp42;
    current_index++;

    start_index = current_index;
    tmp46 = 1.0;
    tmp47 = 280.0;
    tmp45 = GreaterEqZC(data->localData[0]->timeValue, 280.0, tmp46, tmp47, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[start_index] = tmp45;
    current_index++;

    start_index = current_index;
    tmp49 = 1.0;
    tmp50 = 650.0;
    tmp48 = GreaterEqZC(data->localData[0]->timeValue, 650.0, tmp49, tmp50, data->simulationInfo->storedRelations[3]);
    data->simulationInfo->relations[start_index] = tmp48;
    current_index++;

    start_index = current_index;
    tmp52 = 1.0;
    tmp53 = 700.0;
    tmp51 = GreaterEqZC(data->localData[0]->timeValue, 700.0, tmp52, tmp53, data->simulationInfo->storedRelations[4]);
    data->simulationInfo->relations[start_index] = tmp51;
    current_index++;

    start_index = current_index;
    tmp55 = 1.0;
    tmp56 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3]] /* h1High PARAM */));
    tmp54 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3]] /* h1High PARAM */), tmp55, tmp56, data->simulationInfo->storedRelations[5]);
    data->simulationInfo->relations[start_index] = tmp54;
    current_index++;

    start_index = current_index;
    tmp58 = 2.0;
    tmp59 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[9]] /* wait1 PARAM */));
    tmp57 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[9]] /* wait1 PARAM */), tmp58, tmp59, data->simulationInfo->storedRelations[6]);
    data->simulationInfo->relations[start_index] = tmp57;
    current_index++;

    start_index = current_index;
    tmp61 = 1.0;
    tmp62 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */));
    tmp60 = LessEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */), tmp61, tmp62, data->simulationInfo->storedRelations[7]);
    data->simulationInfo->relations[start_index] = tmp60;
    current_index++;

    start_index = current_index;
    tmp64 = 2.0;
    tmp65 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[10]] /* wait2 PARAM */));
    tmp63 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[10]] /* wait2 PARAM */), tmp64, tmp65, data->simulationInfo->storedRelations[8]);
    data->simulationInfo->relations[start_index] = tmp63;
    current_index++;

    start_index = current_index;
    tmp67 = 1.0;
    tmp68 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */));
    tmp66 = LessEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */), tmp67, tmp68, data->simulationInfo->storedRelations[9]);
    data->simulationInfo->relations[start_index] = tmp66;
    current_index++;

    start_index = current_index;
    tmp70 = 2.0;
    tmp71 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[11]] /* wait3 PARAM */));
    tmp69 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[11]] /* wait3 PARAM */), tmp70, tmp71, data->simulationInfo->storedRelations[10]);
    data->simulationInfo->relations[start_index] = tmp69;
    current_index++;

    start_index = current_index;
    tmp73 = 1.0;
    tmp74 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */));
    tmp72 = LessEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */), tmp73, tmp74, data->simulationInfo->storedRelations[11]);
    data->simulationInfo->relations[start_index] = tmp72;
    current_index++;

    start_index = current_index;
    tmp76 = 1.0;
    tmp77 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */));
    tmp75 = LessEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */), tmp76, tmp77, data->simulationInfo->storedRelations[12]);
    data->simulationInfo->relations[start_index] = tmp75;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= 20.0);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= 220.0);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= 280.0);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= 650.0);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= 700.0);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */) >= (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3]] /* h1High PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */) >= (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[9]] /* wait1 PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */) <= (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */) >= (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[10]] /* wait2 PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */) <= (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */) >= (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[11]] /* wait3 PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */) <= (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */) <= (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */));
    current_index++;
  }
  
  return 0;
}

#if defined(__cplusplus)
}
#endif
