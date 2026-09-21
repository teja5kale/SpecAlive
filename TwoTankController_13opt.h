#if defined(__cplusplus)
  extern "C" {
#endif
  int TwoTankController_mayer(DATA* data, modelica_real** res, short*);
  int TwoTankController_lagrange(DATA* data, modelica_real** res, short *, short *);
  int TwoTankController_getInputVarIndicesInOptimization(DATA* data, int* input_var_indices);
  int TwoTankController_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int TwoTankController_setInputData(DATA *data, const modelica_boolean file);
  int TwoTankController_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif
