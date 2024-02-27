#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "Cell.h"

void ReadFiles(int& timeLimit, int& refreshRate, int& numCols, int& numRows, string& regionFileName, int& availWorkers, int& availGoods);

void FillArray(Cell* regionMap[][100], const int numRows, const int numCols, const string regionFileName, int& availWorkers, int& availGoods);

void PopulateAdjacencyLists(Cell* regionMap[][100], const int numRows, const int numCols);

void DeleteArray(Cell* regionMap[][100], const int numRows, const int numCols);

#endif

