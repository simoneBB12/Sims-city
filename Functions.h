#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Cell.h"

void PrintRegionMap(const int numRows, const int numCols, Cell* regionMap[][100]);

void ResetUpdateStatus(const int numRows, const int numCols, Cell* regionMap[][100]);

void ResetRadiationUpdateStatus(const int numRows, const int numCols, Cell* regionMap[][100]);

bool IsUnchanged(Cell* regionMap[][100], int numRows, int numCols);

#endif
