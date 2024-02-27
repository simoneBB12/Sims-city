#ifndef NUKEH
#define NUKEH

#include "Cell.h"

//nuke functionalities
void PlaceNuke(Cell* regionMap[][100], bool &nukeLanded, int numRows, int numCols);
void SpreadNukeRadiation(Cell* regionMap[][100], bool nukeLanded, int numRows, int numCols);

#endif
