/* Initialization */
#include "TwoTankController_model.h"
#include "TwoTankController_11mix.h"
#include "TwoTankController_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void TwoTankController_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
h1 = h0
*/
void TwoTankController_eqFunction_1(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2]] /* h0 PARAM */);
  threadData->lastEquationSolved = 1;
}

/*
equation index: 2
type: SIMPLE_ASSIGN
h2 = h0
*/
void TwoTankController_eqFunction_2(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2]] /* h0 PARAM */);
  threadData->lastEquationSolved = 2;
}

/*
equation index: 3
type: SIMPLE_ASSIGN
tRun = $START.tRun
*/
void TwoTankController_eqFunction_3(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,3};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) = ((modelica_real *)((data->modelData->realVarsData[2] /* tRun STATE(1) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 3;
}

/*
equation index: 4
type: SIMPLE_ASSIGN
$PRE.seq = Step.IDLE
*/
void TwoTankController_eqFunction_4(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,4};
  (data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) = 1;
  threadData->lastEquationSolved = 4;
}

/*
equation index: 5
type: SIMPLE_ASSIGN
seq = $PRE.seq
*/
void TwoTankController_eqFunction_5(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) = (data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */);
  threadData->lastEquationSolved = 5;
}

/*
equation index: 6
type: SIMPLE_ASSIGN
$PRE.paused = false
*/
void TwoTankController_eqFunction_6(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,6};
  (data->simulationInfo->booleanVarsPre[12] /* paused DISCRETE */) = 0 /* false */;
  threadData->lastEquationSolved = 6;
}

/*
equation index: 7
type: SIMPLE_ASSIGN
paused = $PRE.paused
*/
void TwoTankController_eqFunction_7(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,7};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */) = (data->simulationInfo->booleanVarsPre[12] /* paused DISCRETE */);
  threadData->lastEquationSolved = 7;
}
extern void TwoTankController_eqFunction_20(DATA *data, threadData_t *threadData);


/*
equation index: 9
type: SIMPLE_ASSIGN
$PRE.shutting = false
*/
void TwoTankController_eqFunction_9(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,9};
  (data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */) = 0 /* false */;
  threadData->lastEquationSolved = 9;
}

/*
equation index: 10
type: SIMPLE_ASSIGN
shutting = $PRE.shutting
*/
void TwoTankController_eqFunction_10(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,10};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* shutting DISCRETE */) = (data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */);
  threadData->lastEquationSolved = 10;
}
extern void TwoTankController_eqFunction_24(DATA *data, threadData_t *threadData);

extern void TwoTankController_eqFunction_22(DATA *data, threadData_t *threadData);

extern void TwoTankController_eqFunction_25(DATA *data, threadData_t *threadData);

extern void TwoTankController_eqFunction_21(DATA *data, threadData_t *threadData);

extern void TwoTankController_eqFunction_23(DATA *data, threadData_t *threadData);


/*
equation index: 16
type: SIMPLE_ASSIGN
$PRE.tMark = 0.0
*/
void TwoTankController_eqFunction_16(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,16};
  (data->simulationInfo->realVarsPre[6] /* tMark DISCRETE */) = 0.0;
  threadData->lastEquationSolved = 16;
}

/*
equation index: 17
type: SIMPLE_ASSIGN
tMark = $PRE.tMark
*/
void TwoTankController_eqFunction_17(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,17};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */) = (data->simulationInfo->realVarsPre[6] /* tMark DISCRETE */);
  threadData->lastEquationSolved = 17;
}

/*
equation index: 18
type: ALGORITHM

  $whenCondition12 := $START.$whenCondition12;
  $whenCondition11 := $START.$whenCondition11;
  $whenCondition10 := $START.$whenCondition10;
  $whenCondition9 := $START.$whenCondition9;
  $whenCondition8 := $START.$whenCondition8;
  $whenCondition7 := $START.$whenCondition7;
  $whenCondition6 := $START.$whenCondition6;
  $whenCondition5 := $START.$whenCondition5;
  $whenCondition4 := $START.$whenCondition4;
  $whenCondition3 := $START.$whenCondition3;
  $whenCondition2 := $START.$whenCondition2;
  $whenCondition1 := $START.$whenCondition1;
  $whenCondition1 := time >= 20.0;
  $whenCondition2 := time >= 220.0;
  $whenCondition3 := time >= 280.0;
  $whenCondition4 := time >= 650.0;
  $whenCondition5 := time >= 700.0;
  $whenCondition6 := h1 >= h1High and $PRE.seq == Step.FILL and not $PRE.shutting;
  $whenCondition7 := tRun - tMark >= wait1 and $PRE.seq == Step.HOLD1 and not $PRE.shutting;
  $whenCondition8 := h1 <= h1Low and $PRE.seq == Step.TRANSFER and not $PRE.shutting;
  $whenCondition9 := tRun - tMark >= wait2 and $PRE.seq == Step.HOLD2 and not $PRE.shutting;
  $whenCondition10 := h2 <= h2Low and $PRE.seq == Step.DRAIN and not $PRE.shutting;
  $whenCondition11 := tRun - tMark >= wait3 and $PRE.seq == Step.HOLD3 and not $PRE.shutting;
  $whenCondition12 := $PRE.shutting and h1 <= h1Low and h2 <= h2Low;
*/
void TwoTankController_eqFunction_18(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,18};
  modelica_boolean tmp0;
  modelica_boolean tmp1;
  modelica_boolean tmp2;
  modelica_boolean tmp3;
  modelica_boolean tmp4;
  modelica_boolean tmp5;
  modelica_boolean tmp6;
  modelica_boolean tmp7;
  modelica_boolean tmp8;
  modelica_boolean tmp9;
  modelica_boolean tmp10;
  modelica_boolean tmp11;
  modelica_boolean tmp12;
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition12 DISCRETE */) = (data->modelData->booleanVarsData[3] /* $whenCondition12 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition11 DISCRETE */) = (data->modelData->booleanVarsData[2] /* $whenCondition11 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */) = (data->modelData->booleanVarsData[1] /* $whenCondition10 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition9 DISCRETE */) = (data->modelData->booleanVarsData[11] /* $whenCondition9 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[10]] /* $whenCondition8 DISCRETE */) = (data->modelData->booleanVarsData[10] /* $whenCondition8 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* $whenCondition7 DISCRETE */) = (data->modelData->booleanVarsData[9] /* $whenCondition7 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* $whenCondition6 DISCRETE */) = (data->modelData->booleanVarsData[8] /* $whenCondition6 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[7]] /* $whenCondition5 DISCRETE */) = (data->modelData->booleanVarsData[7] /* $whenCondition5 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition4 DISCRETE */) = (data->modelData->booleanVarsData[6] /* $whenCondition4 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* $whenCondition3 DISCRETE */) = (data->modelData->booleanVarsData[5] /* $whenCondition3 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* $whenCondition2 DISCRETE */) = (data->modelData->booleanVarsData[4] /* $whenCondition2 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = (data->modelData->booleanVarsData[0] /* $whenCondition1 DISCRETE */).attribute .start;

  tmp0 = GreaterEq(data->localData[0]->timeValue,20.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = tmp0;

  tmp1 = GreaterEq(data->localData[0]->timeValue,220.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* $whenCondition2 DISCRETE */) = tmp1;

  tmp2 = GreaterEq(data->localData[0]->timeValue,280.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* $whenCondition3 DISCRETE */) = tmp2;

  tmp3 = GreaterEq(data->localData[0]->timeValue,650.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition4 DISCRETE */) = tmp3;

  tmp4 = GreaterEq(data->localData[0]->timeValue,700.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[7]] /* $whenCondition5 DISCRETE */) = tmp4;

  tmp5 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3]] /* h1High PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* $whenCondition6 DISCRETE */) = ((tmp5 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 2)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  tmp6 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[9]] /* wait1 PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* $whenCondition7 DISCRETE */) = ((tmp6 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 3)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  tmp7 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[10]] /* $whenCondition8 DISCRETE */) = ((tmp7 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 4)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  tmp8 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[10]] /* wait2 PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition9 DISCRETE */) = ((tmp8 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 5)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  tmp9 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */) = ((tmp9 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 6)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  tmp10 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[11]] /* wait3 PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition11 DISCRETE */) = ((tmp10 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 7)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  tmp11 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */));
  tmp12 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition12 DISCRETE */) = (((data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */) && tmp11) && tmp12);
  threadData->lastEquationSolved = 18;
}
OMC_DISABLE_OPT
void TwoTankController_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[18])(DATA*, threadData_t*) = {
    TwoTankController_eqFunction_1,
    TwoTankController_eqFunction_2,
    TwoTankController_eqFunction_3,
    TwoTankController_eqFunction_4,
    TwoTankController_eqFunction_5,
    TwoTankController_eqFunction_6,
    TwoTankController_eqFunction_7,
    TwoTankController_eqFunction_20,
    TwoTankController_eqFunction_9,
    TwoTankController_eqFunction_10,
    TwoTankController_eqFunction_24,
    TwoTankController_eqFunction_22,
    TwoTankController_eqFunction_25,
    TwoTankController_eqFunction_21,
    TwoTankController_eqFunction_23,
    TwoTankController_eqFunction_16,
    TwoTankController_eqFunction_17,
    TwoTankController_eqFunction_18
  };
  
  for (int id = 0; id < 18; id++) {
    eqFunctions[id](data, threadData);
  }
}

int TwoTankController_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  data->simulationInfo->discreteCall = 1;
  TwoTankController_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  return 0;
}

/* No TwoTankController_functionInitialEquations_lambda0 function */

int TwoTankController_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  return 0;
}


#if defined(__cplusplus)
}
#endif
