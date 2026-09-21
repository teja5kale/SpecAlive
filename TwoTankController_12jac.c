/* Jacobians 7 */
#include "TwoTankController_model.h"
#include "TwoTankController_12jac.h"
#include "simulation/jacobian_util.h"
#include "util/omc_file.h"
int TwoTankController_functionJacADJ_column(DATA* data, threadData_t *threadData, JACOBIAN *jacobian, JACOBIAN *parentJacobian)
{
  return 0;
}

void TwoTankController_JacADJ_DAG(DATA* data, threadData_t* threadData, JACOBIAN* jacobian) { /* empty */ }

int TwoTankController_functionJacH_column(DATA* data, threadData_t *threadData, JACOBIAN *jacobian, JACOBIAN *parentJacobian)
{
  return 0;
}

void TwoTankController_JacH_DAG(DATA* data, threadData_t* threadData, JACOBIAN* jacobian) { /* empty */ }

int TwoTankController_functionJacF_column(DATA* data, threadData_t *threadData, JACOBIAN *jacobian, JACOBIAN *parentJacobian)
{
  return 0;
}

void TwoTankController_JacF_DAG(DATA* data, threadData_t* threadData, JACOBIAN* jacobian) { /* empty */ }

int TwoTankController_functionJacD_column(DATA* data, threadData_t *threadData, JACOBIAN *jacobian, JACOBIAN *parentJacobian)
{
  return 0;
}

void TwoTankController_JacD_DAG(DATA* data, threadData_t* threadData, JACOBIAN* jacobian) { /* empty */ }

int TwoTankController_functionJacC_column(DATA* data, threadData_t *threadData, JACOBIAN *jacobian, JACOBIAN *parentJacobian)
{
  return 0;
}

void TwoTankController_JacC_DAG(DATA* data, threadData_t* threadData, JACOBIAN* jacobian) { /* empty */ }

int TwoTankController_functionJacB_column(DATA* data, threadData_t *threadData, JACOBIAN *jacobian, JACOBIAN *parentJacobian)
{
  return 0;
}

void TwoTankController_JacB_DAG(DATA* data, threadData_t* threadData, JACOBIAN* jacobian) { /* empty */ }

/* constant equations */
/* dynamic equations */

OMC_DISABLE_OPT
int TwoTankController_functionJacA_constantEqns(DATA* data, threadData_t *threadData, JACOBIAN *jacobian, JACOBIAN *parentJacobian)
{
  int index = TwoTankController_INDEX_JAC_A;
  
  
  return 0;
}

int TwoTankController_functionJacA_column(DATA* data, threadData_t *threadData, JACOBIAN *jacobian, JACOBIAN *parentJacobian)
{
  int index = TwoTankController_INDEX_JAC_A;
  
  
  return 0;
}

void TwoTankController_JacA_DAG(DATA* data, threadData_t* threadData, JACOBIAN* jacobian)
{
  const size_t eqMap[] = {};
  buildEvalDAG_Jac(jacobian, data->modelData, sizeof(eqMap)/sizeof(size_t), eqMap);
}

int TwoTankController_initialAnalyticJacobianADJ(DATA* data, threadData_t *threadData, JACOBIAN *jacobian)
{
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TwoTankController_initialAnalyticJacobianH(DATA* data, threadData_t *threadData, JACOBIAN *jacobian)
{
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TwoTankController_initialAnalyticJacobianF(DATA* data, threadData_t *threadData, JACOBIAN *jacobian)
{
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TwoTankController_initialAnalyticJacobianD(DATA* data, threadData_t *threadData, JACOBIAN *jacobian)
{
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TwoTankController_initialAnalyticJacobianC(DATA* data, threadData_t *threadData, JACOBIAN *jacobian)
{
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TwoTankController_initialAnalyticJacobianB(DATA* data, threadData_t *threadData, JACOBIAN *jacobian)
{
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
OMC_DISABLE_OPT
int TwoTankController_initialAnalyticJacobianA(DATA* data, threadData_t *threadData, JACOBIAN *jacobian)
{
  size_t count;

  FILE* pFile = openSparsePatternFile(data, threadData, "TwoTankController_JacA.bin");
  
  initJacobian(jacobian, 3, 3, 0, NULL, TwoTankController_functionJacA_column, NULL, NULL);
  jacobian->sparsePattern = allocSparsePattern(3, 9, 3);
  jacobian->availability = JACOBIAN_ONLY_SPARSITY;
  jacobian->isRowEval = 0 /* false */;
  
  /* read lead index of compressed sparse column */
  count = omc_fread(jacobian->sparsePattern->leadindex, sizeof(unsigned int), 3+1, pFile, FALSE);
  if (count != 3+1) {
    throwStreamPrint(threadData, "Error while reading lead index list of sparsity pattern. Expected %d, got %zu", 3+1, count);
  }
  
  /* read sparse index */
  count = omc_fread(jacobian->sparsePattern->index, sizeof(unsigned int), 9, pFile, FALSE);
  if (count != 9) {
    throwStreamPrint(threadData, "Error while reading row index list of sparsity pattern. Expected %d, got %zu", 9, count);
  }
  
  /* write color array */
  /* color 1 with 1 columns */
  readSparsePatternColor(threadData, pFile, jacobian->sparsePattern->colorCols, 1, 1, 3);
  /* color 2 with 1 columns */
  readSparsePatternColor(threadData, pFile, jacobian->sparsePattern->colorCols, 2, 1, 3);
  /* color 3 with 1 columns */
  readSparsePatternColor(threadData, pFile, jacobian->sparsePattern->colorCols, 3, 1, 3);
  
  omc_fclose(pFile);
  
  return 0;
}


