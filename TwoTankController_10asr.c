/* Asserts */
#include "TwoTankController_model.h"
#if defined(__cplusplus)
extern "C" {
#endif


/*
equation index: 28
type: ALGORITHM

  assert(seq >= Step.IDLE and seq <= Step.HOLD3, "Variable violating min/max constraint: Step.IDLE <= seq <= Step.HOLD3, has value: " + String(seq, "d"));
*/
void TwoTankController_eqFunction_28(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,28};
  modelica_boolean tmp0;
  modelica_boolean tmp1;
  static const MMC_DEFSTRINGLIT(tmp2,82,"Variable violating min/max constraint: Step.IDLE <= seq <= Step.HOLD3, has value: ");
  modelica_string tmp3;
  modelica_metatype tmpMeta4;
  static int tmp5 = 0;
  if(!tmp5)
  {
    tmp0 = GreaterEq((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */),1);
    tmp1 = LessEq((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */),7);
    if(!(tmp0 && tmp1))
    {
      tmp3 = modelica_integer_to_modelica_string_format((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* seq DISCRETE */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta4 = stringAppend(MMC_REFSTRINGLIT(tmp2),tmp3);
      {
        const char* assert_cond = "(seq >= Step.IDLE and seq <= Step.HOLD3)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"D:/SpecAlive/cases/tank/TwoTankController.mo",35,3,35,76,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta4));
        } else {
          FILE_INFO info = {"D:/SpecAlive/cases/tank/TwoTankController.mo",35,3,35,76,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta4));
        }
      }
      tmp5 = 1;
    }
  }
  threadData->lastEquationSolved = 28;
}
/* function to check assert after a step is done */
OMC_DISABLE_OPT
int TwoTankController_checkForAsserts(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[1])(DATA*, threadData_t*) = {
    TwoTankController_eqFunction_28
  };
  
  for (int id = 0; id < 1; id++) {
    eqFunctions[id](data, threadData);
  }
  
  return 0;
}

#if defined(__cplusplus)
}
#endif
