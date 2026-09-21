/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "TwoTankController_model.h"
#if defined(__cplusplus)
extern "C" {
#endif


/*
equation index: 26
type: SIMPLE_ASSIGN
$START.h2 = h0
*/
static void TwoTankController_eqFunction_26(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,26};
  ((modelica_real *)((data->modelData->realVarsData[1] /* h2 STATE(1) */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2]] /* h0 PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */) = ((modelica_real *)((data->modelData->realVarsData[1] /* h2 STATE(1) */).attribute .start.data))[0];
  infoStreamPrint(OMC_LOG_INIT_V, 0,
                  "updated start value: %s(start=%g)",
                  data->modelData->realVarsData[1] /* h2 */ .info.name,
                  (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* h2 STATE(1) */));
  threadData->lastEquationSolved = 26;
}

/*
equation index: 27
type: SIMPLE_ASSIGN
$START.h1 = h0
*/
static void TwoTankController_eqFunction_27(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,27};
  ((modelica_real *)((data->modelData->realVarsData[0] /* h1 STATE(1) */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2]] /* h0 PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */) = ((modelica_real *)((data->modelData->realVarsData[0] /* h1 STATE(1) */).attribute .start.data))[0];
  infoStreamPrint(OMC_LOG_INIT_V, 0,
                  "updated start value: %s(start=%g)",
                  data->modelData->realVarsData[0] /* h1 */ .info.name,
                  (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* h1 STATE(1) */));
  threadData->lastEquationSolved = 27;
}
OMC_DISABLE_OPT
int TwoTankController_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  /* min ******************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating min-values");
  messageClose(OMC_LOG_INIT);
  
  /* max ******************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating max-values");
  messageClose(OMC_LOG_INIT);
  
  /* nominal **************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating nominal-values");
  messageClose(OMC_LOG_INIT);
  
  /* start ****************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating primary start-values");
  TwoTankController_eqFunction_26(data, threadData);
  TwoTankController_eqFunction_27(data, threadData);
  messageClose(OMC_LOG_INIT);
  
  return 0;
}

OMC_DISABLE_OPT
int TwoTankController_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  return 0;
}

#if defined(__cplusplus)
}
#endif
