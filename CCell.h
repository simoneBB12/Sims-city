#ifndef C_CELL_H
#define C_CELL_H

#include "Cell.h"

//commercial function definitions
void IncrementCommercial(Cell* workingCellPtr, int& availWorkers, int& availGoods, bool &radiationInhibitUpdate);
void UpdateCommercial(int& availGoods, int& availWorkers, const int numRows, const int numCols, Cell* regionMap[][100], bool &radiationInhibitUpdate);

#endif
