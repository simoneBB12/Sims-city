#ifndef RCELLH
#define RCELLH

#include "Cell.h"

void IncrementResidentialAdult(Cell* cellPtr, int& availWorkers);
void IncrementResidentialChild(Cell* cellPtr);
void UpdateResidential(int numRows, int numCols, Cell* regionMap[][100], int& availWorkers);

#endif
