/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "TwoTankController_model.h"
#include "simulation/solver/events.h"
#include "simulation/arrayIndex.h"

/* FIXME these defines are ugly and hard to read, why not use direct function pointers instead? */
#define prefixedName_performSimulation TwoTankController_performSimulation
#define prefixedName_updateContinuousSystem TwoTankController_updateContinuousSystem
#include <simulation/solver/perform_simulation.c.inc>

#define prefixedName_performQSSSimulation TwoTankController_performQSSSimulation
#include <simulation/solver/perform_qss_simulation.c.inc>


/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int TwoTankController_input_function(DATA *data, threadData_t *threadData)
{
  
  return 0;
}

int TwoTankController_input_function_init(DATA *data, threadData_t *threadData)
{
  
  return 0;
}

int TwoTankController_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  
  return 0;
}

int TwoTankController_inputNames(DATA *data, char ** names){
  
  return 0;
}

int TwoTankController_data_function(DATA *data, threadData_t *threadData)
{
  return 0;
}

int TwoTankController_dataReconciliationInputNames(DATA *data, char ** names){
  
  return 0;
}

int TwoTankController_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  
  return 0;
}

int TwoTankController_output_function(DATA *data, threadData_t *threadData)
{
  
  return 0;
}

int TwoTankController_setc_function(DATA *data, threadData_t *threadData)
{
  
  return 0;
}

int TwoTankController_setb_function(DATA *data, threadData_t *threadData)
{
  
  return 0;
}


/*
equation index: 19
type: ALGORITHM

  $whenCondition12 := pre($whenCondition12);
  $whenCondition11 := pre($whenCondition11);
  $whenCondition10 := pre($whenCondition10);
  $whenCondition9 := pre($whenCondition9);
  $whenCondition8 := pre($whenCondition8);
  $whenCondition7 := pre($whenCondition7);
  $whenCondition6 := pre($whenCondition6);
  shutting := pre(shutting);
  $whenCondition5 := pre($whenCondition5);
  $whenCondition4 := pre($whenCondition4);
  $whenCondition3 := pre($whenCondition3);
  paused := pre(paused);
  $whenCondition2 := pre($whenCondition2);
  tMark := pre(tMark);
  seq := pre(seq);
  $whenCondition1 := pre($whenCondition1);
  $whenCondition1 := time >= 20.0;
  when $whenCondition1 then
    if not shutting and not paused and pre(seq) == Step.IDLE then
      seq := Step.FILL;
      tMark := tRun;
    end if;
  end when;
  $whenCondition2 := time >= 220.0;
  when $whenCondition2 then
    if not pre(shutting) then
      paused := true;
    end if;
  end when;
  $whenCondition3 := time >= 280.0;
  when $whenCondition3 then
    if not pre(shutting) then
      paused := false;
    end if;
  end when;
  $whenCondition4 := time >= 650.0;
  when $whenCondition4 then
    if not pre(shutting) then
      paused := true;
    end if;
  end when;
  $whenCondition5 := time >= 700.0;
  when $whenCondition5 then
    shutting := true;
    paused := false;
  end when;
  $whenCondition6 := h1 >= h1High and pre(seq) == Step.FILL and not pre(shutting);
  when $whenCondition6 then
    seq := Step.HOLD1;
    tMark := tRun;
  end when;
  $whenCondition7 := tRun - tMark >= wait1 and pre(seq) == Step.HOLD1 and not pre(shutting);
  when $whenCondition7 then
    seq := Step.TRANSFER;
  end when;
  $whenCondition8 := h1 <= h1Low and pre(seq) == Step.TRANSFER and not pre(shutting);
  when $whenCondition8 then
    seq := Step.HOLD2;
    tMark := tRun;
  end when;
  $whenCondition9 := tRun - tMark >= wait2 and pre(seq) == Step.HOLD2 and not pre(shutting);
  when $whenCondition9 then
    seq := Step.DRAIN;
  end when;
  $whenCondition10 := h2 <= h2Low and pre(seq) == Step.DRAIN and not pre(shutting);
  when $whenCondition10 then
    seq := Step.HOLD3;
    tMark := tRun;
  end when;
  $whenCondition11 := tRun - tMark >= wait3 and pre(seq) == Step.HOLD3 and not pre(shutting);
  when $whenCondition11 then
    seq := Step.FILL;
    tMark := tRun;
  end when;
  $whenCondition12 := pre(shutting) and h1 <= h1Low and h2 <= h2Low;
  when $whenCondition12 then
    shutting := false;
    seq := Step.IDLE;
  end when;
*/
void TwoTankController_eqFunction_19(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,19};
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
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition12 DISCRETE */) = (data->simulationInfo->booleanVarsPre[3] /* $whenCondition12 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition11 DISCRETE */) = (data->simulationInfo->booleanVarsPre[2] /* $whenCondition11 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */) = (data->simulationInfo->booleanVarsPre[1] /* $whenCondition10 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition9 DISCRETE */) = (data->simulationInfo->booleanVarsPre[11] /* $whenCondition9 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[10]] /* $whenCondition8 DISCRETE */) = (data->simulationInfo->booleanVarsPre[10] /* $whenCondition8 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* $whenCondition7 DISCRETE */) = (data->simulationInfo->booleanVarsPre[9] /* $whenCondition7 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* $whenCondition6 DISCRETE */) = (data->simulationInfo->booleanVarsPre[8] /* $whenCondition6 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* shutting DISCRETE */) = (data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[7]] /* $whenCondition5 DISCRETE */) = (data->simulationInfo->booleanVarsPre[7] /* $whenCondition5 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition4 DISCRETE */) = (data->simulationInfo->booleanVarsPre[6] /* $whenCondition4 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* $whenCondition3 DISCRETE */) = (data->simulationInfo->booleanVarsPre[5] /* $whenCondition3 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */) = (data->simulationInfo->booleanVarsPre[12] /* paused DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* $whenCondition2 DISCRETE */) = (data->simulationInfo->booleanVarsPre[4] /* $whenCondition2 DISCRETE */);

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */) = (data->simulationInfo->realVarsPre[6] /* tMark DISCRETE */);

  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) = (data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = (data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */);

  tmp1 = 1.0;
  tmp2 = 20.0;
  relationhysteresis(data, &tmp0, data->localData[0]->timeValue, 20.0, tmp1, tmp2, 0, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = tmp0;

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */) /* edge */))
    {
      if((((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* shutting DISCRETE */)) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */))) && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 1)))
      {
        (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) = 2;

        (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */);
      }
    }
  }

  tmp4 = 1.0;
  tmp5 = 220.0;
  relationhysteresis(data, &tmp3, data->localData[0]->timeValue, 220.0, tmp4, tmp5, 1, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* $whenCondition2 DISCRETE */) = tmp3;

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* $whenCondition2 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[4] /* $whenCondition2 DISCRETE */) /* edge */))
    {
      if((!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)))
      {
        (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */) = 1 /* true */;
      }
    }
  }

  tmp7 = 1.0;
  tmp8 = 280.0;
  relationhysteresis(data, &tmp6, data->localData[0]->timeValue, 280.0, tmp7, tmp8, 2, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* $whenCondition3 DISCRETE */) = tmp6;

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* $whenCondition3 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[5] /* $whenCondition3 DISCRETE */) /* edge */))
    {
      if((!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)))
      {
        (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */) = 0 /* false */;
      }
    }
  }

  tmp10 = 1.0;
  tmp11 = 650.0;
  relationhysteresis(data, &tmp9, data->localData[0]->timeValue, 650.0, tmp10, tmp11, 3, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition4 DISCRETE */) = tmp9;

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition4 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[6] /* $whenCondition4 DISCRETE */) /* edge */))
    {
      if((!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)))
      {
        (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */) = 1 /* true */;
      }
    }
  }

  tmp13 = 1.0;
  tmp14 = 700.0;
  relationhysteresis(data, &tmp12, data->localData[0]->timeValue, 700.0, tmp13, tmp14, 4, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[7]] /* $whenCondition5 DISCRETE */) = tmp12;

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[7]] /* $whenCondition5 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[7] /* $whenCondition5 DISCRETE */) /* edge */))
    {
      (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* shutting DISCRETE */) = 1 /* true */;

      (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */) = 0 /* false */;
    }
  }

  tmp16 = 1.0;
  tmp17 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3]] /* h1High PARAM */));
  relationhysteresis(data, &tmp15, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3]] /* h1High PARAM */), tmp16, tmp17, 5, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* $whenCondition6 DISCRETE */) = ((tmp15 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 2)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* $whenCondition6 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[8] /* $whenCondition6 DISCRETE */) /* edge */))
    {
      (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) = 3;

      (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */);
    }
  }

  tmp19 = 2.0;
  tmp20 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[9]] /* wait1 PARAM */));
  relationhysteresis(data, &tmp18, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[9]] /* wait1 PARAM */), tmp19, tmp20, 6, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* $whenCondition7 DISCRETE */) = ((tmp18 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 3)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* $whenCondition7 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[9] /* $whenCondition7 DISCRETE */) /* edge */))
    {
      (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) = 4;
    }
  }

  tmp22 = 1.0;
  tmp23 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */));
  relationhysteresis(data, &tmp21, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */), tmp22, tmp23, 7, LessEq, LessEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[10]] /* $whenCondition8 DISCRETE */) = ((tmp21 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 4)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[10]] /* $whenCondition8 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[10] /* $whenCondition8 DISCRETE */) /* edge */))
    {
      (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) = 5;

      (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */);
    }
  }

  tmp25 = 2.0;
  tmp26 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[10]] /* wait2 PARAM */));
  relationhysteresis(data, &tmp24, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[10]] /* wait2 PARAM */), tmp25, tmp26, 8, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition9 DISCRETE */) = ((tmp24 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 5)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition9 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[11] /* $whenCondition9 DISCRETE */) /* edge */))
    {
      (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) = 6;
    }
  }

  tmp28 = 1.0;
  tmp29 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */));
  relationhysteresis(data, &tmp27, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */), tmp28, tmp29, 9, LessEq, LessEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */) = ((tmp27 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 6)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[1] /* $whenCondition10 DISCRETE */) /* edge */))
    {
      (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) = 7;

      (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */);
    }
  }

  tmp31 = 2.0;
  tmp32 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[11]] /* wait3 PARAM */));
  relationhysteresis(data, &tmp30, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[11]] /* wait3 PARAM */), tmp31, tmp32, 10, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition11 DISCRETE */) = ((tmp30 && ((data->simulationInfo->integerVarsPre[0] /* seq DISCRETE */) == 7)) && (!(data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */)));

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition11 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[2] /* $whenCondition11 DISCRETE */) /* edge */))
    {
      (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) = 2;

      (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* tMark DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tRun STATE(1) */);
    }
  }

  tmp34 = 1.0;
  tmp35 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */));
  relationhysteresis(data, &tmp33, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4]] /* h1Low PARAM */), tmp34, tmp35, 11, LessEq, LessEqZC);
  tmp37 = 1.0;
  tmp38 = fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */));
  relationhysteresis(data, &tmp36, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5]] /* h2Low PARAM */), tmp37, tmp38, 12, LessEq, LessEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition12 DISCRETE */) = (((data->simulationInfo->booleanVarsPre[13] /* shutting DISCRETE */) && tmp33) && tmp36);

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition12 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[3] /* $whenCondition12 DISCRETE */) /* edge */))
    {
      (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* shutting DISCRETE */) = 0 /* false */;

      (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) = 1;
    }
  }
  threadData->lastEquationSolved = 19;
}

/*
equation index: 20
type: SIMPLE_ASSIGN
$DER.tRun = if not paused and (seq == Step.HOLD1 or seq == Step.HOLD2 or seq == Step.HOLD3) then 1.0 else 0.0
*/
void TwoTankController_eqFunction_20(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,20};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* der(tRun) STATE_DER */) = (((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */)) && ((((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) == 3) || ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) == 5)) || ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) == 7)))?1.0:0.0);
  threadData->lastEquationSolved = 20;
}

/*
equation index: 21
type: SIMPLE_ASSIGN
valve1 = seq == Step.FILL and not paused and not shutting
*/
void TwoTankController_eqFunction_21(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,21};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[14]] /* valve1 DISCRETE */) = ((((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) == 2) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */))) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* shutting DISCRETE */)));
  threadData->lastEquationSolved = 21;
}

/*
equation index: 22
type: SIMPLE_ASSIGN
valve2 = (seq == Step.TRANSFER or shutting) and not paused
*/
void TwoTankController_eqFunction_22(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,22};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[15]] /* valve2 DISCRETE */) = ((((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) == 4) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* shutting DISCRETE */)) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */)));
  threadData->lastEquationSolved = 22;
}

/*
equation index: 23
type: SIMPLE_ASSIGN
$DER.h1 = ((if valve1 then qFill else 0.0) - (if valve2 then qTransfer else 0.0)) / A1
*/
void TwoTankController_eqFunction_23(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,23};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* der(h1) STATE_DER */) = DIVISION_SIM(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[14]] /* valve1 DISCRETE */)?(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[7]] /* qFill PARAM */):0.0) - (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[15]] /* valve2 DISCRETE */)?(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[8]] /* qTransfer PARAM */):0.0)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[0]] /* A1 PARAM */),"A1",equationIndexes);
  threadData->lastEquationSolved = 23;
}

/*
equation index: 24
type: SIMPLE_ASSIGN
valve3 = (seq == Step.DRAIN or shutting) and not paused
*/
void TwoTankController_eqFunction_24(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,24};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[16]] /* valve3 DISCRETE */) = ((((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */) == 6) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* shutting DISCRETE */)) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* paused DISCRETE */)));
  threadData->lastEquationSolved = 24;
}

/*
equation index: 25
type: SIMPLE_ASSIGN
$DER.h2 = ((if valve2 then qTransfer else 0.0) - (if valve3 then qDrain else 0.0)) / A2
*/
void TwoTankController_eqFunction_25(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,25};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* der(h2) STATE_DER */) = DIVISION_SIM(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[15]] /* valve2 DISCRETE */)?(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[8]] /* qTransfer PARAM */):0.0) - (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[16]] /* valve3 DISCRETE */)?(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6]] /* qDrain PARAM */):0.0)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1]] /* A2 PARAM */),"A2",equationIndexes);
  threadData->lastEquationSolved = 25;
}

OMC_DISABLE_OPT
int TwoTankController_functionDAE(DATA *data, threadData_t *threadData)
{
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  TwoTankController_functionLocalKnownVars(data, threadData);
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
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  return 0;
}


int TwoTankController_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  
  return 0;
}

/* forwarded equations */
extern void TwoTankController_eqFunction_19(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_20(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_21(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_22(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_23(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_24(DATA* data, threadData_t *threadData);
extern void TwoTankController_eqFunction_25(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[7])(DATA*, threadData_t*) = {
    TwoTankController_eqFunction_19,
    TwoTankController_eqFunction_20,
    TwoTankController_eqFunction_21,
    TwoTankController_eqFunction_22,
    TwoTankController_eqFunction_23,
    TwoTankController_eqFunction_24,
    TwoTankController_eqFunction_25
  };
  
  if (data->simulationInfo->evalSelection) {
    for (int i = 0; i < data->simulationInfo->evalSelection->n; i++) {
      int id = data->simulationInfo->evalSelection->idx[i];
      eqFunctions[id](data, threadData);
    }
  } else {
    for (int id = 0; id < 7; id++) {
      eqFunctions[id](data, threadData);
    }
  }
}

int TwoTankController_functionODE(DATA *data, threadData_t *threadData)
{
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  TwoTankController_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  return 0;
}

void TwoTankController_ODE_DAG(DATA* data, threadData_t* threadData)
{
  const size_t eqMap[] = {19, 20, 21, 22, 23, 24, 25};
  buildEvalDAG_ODE(data->modelData, sizeof(eqMap)/sizeof(size_t), eqMap);
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char **argv, DATA *data, threadData_t *threadData);
extern int _main_OptimizationRuntime(int argc, char **argv, DATA *data, threadData_t *threadData);

#include "TwoTankController_12jac.h"
#include "TwoTankController_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks TwoTankController_callback = {
  (int (*)(DATA *, threadData_t *, void *)) TwoTankController_performSimulation,    /* performSimulation */
  (int (*)(DATA *, threadData_t *, void *)) TwoTankController_performQSSSimulation,    /* performQSSSimulation */
  TwoTankController_updateContinuousSystem,    /* updateContinuousSystem */
  TwoTankController_callExternalObjectDestructors,    /* callExternalObjectDestructors */
  NULL,    /* initialNonLinearSystem */
  NULL,    /* initialLinearSystem */
  NULL,    /* initialMixedSystem */
  #if !defined(OMC_NO_STATESELECTION)
  TwoTankController_initializeStateSets,
  #else
  NULL,
  #endif    /* initializeStateSets */
  TwoTankController_initializeDAEmodeData,
  TwoTankController_ODE_DAG,
  TwoTankController_functionODE,
  TwoTankController_functionAlgebraics,
  TwoTankController_functionDAE,
  TwoTankController_functionLocalKnownVars,
  TwoTankController_input_function,
  TwoTankController_input_function_init,
  TwoTankController_input_function_updateStartValues,
  TwoTankController_data_function,
  TwoTankController_output_function,
  TwoTankController_setc_function,
  TwoTankController_setb_function,
  TwoTankController_function_storeDelayed,
  TwoTankController_function_storeSpatialDistribution,
  TwoTankController_function_initSpatialDistribution,
  TwoTankController_updateBoundVariableAttributes,
  TwoTankController_functionInitialEquations,
  GLOBAL_EQUIDISTANT_HOMOTOPY,
  NULL,
  TwoTankController_functionRemovedInitialEquations,
  TwoTankController_updateBoundParameters,
  TwoTankController_checkForAsserts,
  TwoTankController_function_ZeroCrossingsEquations,
  TwoTankController_function_ZeroCrossings,
  TwoTankController_function_updateRelations,
  TwoTankController_zeroCrossingDescription,
  TwoTankController_relationDescription,
  TwoTankController_function_initSample,
  TwoTankController_INDEX_JAC_A,
  TwoTankController_INDEX_JAC_ADJ,
  TwoTankController_INDEX_JAC_B,
  TwoTankController_INDEX_JAC_C,
  TwoTankController_INDEX_JAC_D,
  TwoTankController_INDEX_JAC_F,
  TwoTankController_INDEX_JAC_H,
  TwoTankController_initialAnalyticJacobianA,
  TwoTankController_initialAnalyticJacobianADJ,
  TwoTankController_initialAnalyticJacobianB,
  TwoTankController_initialAnalyticJacobianC,
  TwoTankController_initialAnalyticJacobianD,
  TwoTankController_initialAnalyticJacobianF,
  TwoTankController_initialAnalyticJacobianH,
  TwoTankController_functionJacA_column,
  TwoTankController_functionJacADJ_column,
  TwoTankController_functionJacB_column,
  TwoTankController_functionJacC_column,
  TwoTankController_functionJacD_column,
  TwoTankController_functionJacF_column,
  TwoTankController_functionJacH_column,
  TwoTankController_JacA_DAG,
  TwoTankController_linear_model_frame,
  TwoTankController_linear_model_datarecovery_frame,
  TwoTankController_mayer,
  TwoTankController_lagrange,
  TwoTankController_getInputVarIndicesInOptimization,
  TwoTankController_pickUpBoundsForInputsInOptimization,
  TwoTankController_setInputData,
  TwoTankController_getTimeGrid,
  TwoTankController_symbolicInlineSystem,
  TwoTankController_function_initSynchronous,
  TwoTankController_function_updateSynchronous,
  TwoTankController_function_equationsSynchronous,
  TwoTankController_inputNames,
  TwoTankController_dataReconciliationInputNames,
  TwoTankController_dataReconciliationUnmeasuredVariables,
  NULL,
  NULL,
  NULL,
  NULL,
  -1,
  NULL,
  NULL,
  -1

};

#define _OMC_LIT_RESOURCE_0_name_data "TwoTankController"
#define _OMC_LIT_RESOURCE_0_dir_data "D:/SpecAlive/cases/tank"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,17,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,23,_OMC_LIT_RESOURCE_0_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,2,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir)}};
void TwoTankController_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &TwoTankController_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "TwoTankController";
  data->modelData->modelFilePrefix = "TwoTankController";
  data->modelData->modelFileName = "TwoTankController.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "D:/SpecAlive/cases/tank";
  data->modelData->modelGUID = "{b17d9494-861a-4959-a463-16d1dafc0e9f}";
  #if defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME)
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  #else
  #if defined(_MSC_VER) /* handle joke compilers */
  {
  /* for MSVC we encode a string like char x[] = {'a', 'b', 'c', '\0'} */
  /* because the string constant limit is 65535 bytes */
  static const char contents_init[] =
    #include "TwoTankController_init.c"
    ;
  static const char contents_info[] =
    #include "TwoTankController_info.c"
    ;
    data->modelData->initXMLData = contents_init;
    data->modelData->modelDataXml.infoXMLData = contents_info;
  }
  #else /* handle real compilers */
  data->modelData->initXMLData =
  #include "TwoTankController_init.c"
    ;
  data->modelData->modelDataXml.infoXMLData =
  #include "TwoTankController_info.c"
    ;
  #endif /* defined(_MSC_VER) */
  #endif /* defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME) */
  data->modelData->modelDataXml.fileName = "TwoTankController_info.json";
  data->modelData->resourcesDir = NULL;
  data->modelData->runTestsuite = 0;
  data->modelData->nStatesArray = 3;
  data->modelData->nDiscreteReal = 1;
  data->modelData->nVariablesRealArray = 7;
  data->modelData->nVariablesIntegerArray = 1;
  data->modelData->nVariablesBooleanArray = 17;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersRealArray = 12;
  data->modelData->nParametersIntegerArray = 0;
  data->modelData->nParametersBooleanArray = 0;
  data->modelData->nParametersStringArray = 0;
  data->modelData->nParametersReal = 12;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nAliasRealArray = 0;
  data->modelData->nAliasIntegerArray = 0;
  data->modelData->nAliasBooleanArray = 0;
  data->modelData->nAliasStringArray = 0;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 0;
  data->modelData->nZeroCrossings = 12;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 13;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 29;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 0;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 7;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  data->modelData->nDelayExpressions = 0;
  data->modelData->nBaseClocks = 0;
  data->modelData->nSpatialDistributions = 0;
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
  data->modelData->nSetcVars = 0;
  data->modelData->ndataReconVars = 0;
  data->modelData->nSetbVars = 0;
  data->modelData->nRelatedBoundaryConditions = 0;
  data->modelData->linearizationDumpLanguage = OMC_LINEARIZE_DUMP_LANGUAGE_MODELICA;
}

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}


#if defined(__MINGW32__) || defined(_MSC_VER)

#if !defined(_UNICODE)
#define _UNICODE
#endif
#if !defined(UNICODE)
#define UNICODE
#endif

#include <windows.h>
char** omc_fixWindowsArgv(int argc, wchar_t **wargv)
{
  char** newargv;
  /* Support for non-ASCII characters
  * Read the unicode command line arguments and translate it to char*
  */
  newargv = (char**)malloc(argc*sizeof(char*));
  for (int i = 0; i < argc; i++) {
    newargv[i] = omc_wchar_to_multibyte_str(wargv[i]);
  }
  return newargv;
}

#define OMC_MAIN wmain
#define OMC_CHAR wchar_t
#define OMC_EXPORT __declspec(dllexport) extern

#else
#define omc_fixWindowsArgv(N, A) (A)
#define OMC_MAIN main
#define OMC_CHAR char
#define OMC_EXPORT extern
#endif

#if defined(threadData)
#undef threadData
#endif
/* call the simulation runtime main from our main! */
#if defined(OMC_DLL_MAIN_DEFINE)
OMC_EXPORT int omcDllMain(int argc, OMC_CHAR **argv)
#else
int OMC_MAIN(int argc, OMC_CHAR** argv)
#endif
{
  char** newargv = omc_fixWindowsArgv(argc, argv);
  /*
    Set the error functions to be used for simulation.
    The default value for them is 'functions' version. Change it here to 'simulation' versions
  */
  omc_assert = omc_assert_simulation;
  omc_assert_withEquationIndexes = omc_assert_simulation_withEquationIndexes;

  omc_assert_warning_withEquationIndexes = omc_assert_warning_simulation_withEquationIndexes;
  omc_assert_warning = omc_assert_warning_simulation;
  omc_terminate = omc_terminate_simulation;
  omc_throw = omc_throw_simulation;

  int res;
  DATA data;
  MODEL_DATA modelData;
  SIMULATION_INFO simInfo;
  data.modelData = &modelData;
  data.simulationInfo = &simInfo;
  measure_time_flag = 0;
  compiledInDAEMode = 0;
  compiledWithSymSolver = 0;
  MMC_INIT(0);
  omc_alloc_interface.init();
  {
    MMC_TRY_TOP()
  
    MMC_TRY_STACK()
  
    TwoTankController_setupDataStruc(&data, threadData);
    res = _main_initRuntimeAndSimulation(argc, newargv, &data, threadData);
    if(res == 0) {
      if (omc_flag[FLAG_MOO_OPTIMIZATION]) {
        res = _main_OptimizationRuntime(argc, newargv, &data, threadData);
      } else {
        res = _main_SimulationRuntime(argc, newargv, &data, threadData);
      }
    }
    
    MMC_ELSE()
    rml_execution_failed();
    fprintf(stderr, "Stack overflow detected and was not caught.\nSend us a bug report at https://trac.openmodelica.org/OpenModelica/newticket\n    Include the following trace:\n");
    printStacktraceMessages();
    fflush(NULL);
    return 1;
    MMC_CATCH_STACK()
    
    MMC_CATCH_TOP(return rml_execution_failed());
  }

  fflush(NULL);
  return res;
}

#ifdef __cplusplus
}
#endif


