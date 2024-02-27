#include <iostream>
#include <algorithm>
#include "Cell.h"

//updates industrial cells in next time step
void IndustrialUpdate(int numRows, int numCols, int& availableWorkers, int& availableGoods, Cell* regionMap[][100], bool &radiationInhibitUpdate) {
    Cell* cellPtr;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            cellPtr = regionMap[i][j];

            if (cellPtr->GetType() == 'I') {
                if (cellPtr->GetPopulation() == 0) {
		// Check if adjacent to a powerline or a cell with at least 1 population
                    if (cellPtr->NextToPowerline() || cellPtr->hasXNeighborsOfYPop(1, 1)) {
                        if (availableWorkers >= 2) {
			   if(cellPtr->GetCannotGrow() == false) {
                	       // Increase population by 1 and assign workers to the job
                               cellPtr->SetPopulation(cellPtr->GetPopulation() + 1);
                               availableWorkers -= 2;
                               availableGoods++;
                               // assign them to a job
			    }//end if cannotGrow == false
			    else {
				radiationInhibitUpdate = true;
			    }
                        }
                    }
                } else if (cellPtr->GetPopulation() == 1) {
		// Check if adjacent to at least two cells with a population of at least 1
                    if (cellPtr->hasXNeighborsOfYPop(2, 1)) {
                        if (availableWorkers >= 2) {
      			   if(cellPtr->GetCannotGrow() == false) {
                               // Increase population by 1 and assign workers to the job
                               cellPtr->SetPopulation(cellPtr->GetPopulation() + 1);
                               availableWorkers -= 2;
                               availableGoods++;
                               // assign them to a job
                            }//end if cannotGrow == false
			    else {
                                radiationInhibitUpdate = true;
                            }
                        }
                    }
                } else if (cellPtr->GetPopulation() == 2) {
		// Check if adjacent to at least four cells with a population of at least 2
                    if (cellPtr->hasXNeighborsOfYPop(4, 2)) {
                        if (availableWorkers >= 2) {
			    if(cellPtr->GetCannotGrow() == false) {
                               // Increase population by 1 and assign workers to the job
                               cellPtr->SetPopulation(cellPtr->GetPopulation() + 1);
                               availableWorkers -= 2;
                               availableGoods++;
                               // assign them to a job
                            }//end if cannotGrow == false
			    else {
                                radiationInhibitUpdate = true;
                            }
                        }
                    }
                }

                // Set pollution for 'I' cells based on its population
                cellPtr->SetPollution(cellPtr->GetPopulation());

                // Spread pollution to adjacent cells
                for (int x = i - 1; x <= i + 1; x++) {
                    for (int y = j - 1; y <= j + 1; y++) {
                        if (x >= 0 && x < numRows && y >= 0 && y < numCols) { // Boundary check

                            int pollutionSpread = cellPtr->GetPollution() - 1;

                            // If the adjacent cell is an 'I' cell with zero pollution
                            if (regionMap[x][y]->GetType() == 'I' && regionMap[x][y]->GetPollution() == 0) {
                                regionMap[x][y]->SetPollution(pollutionSpread);
                            }
                            // If not an 'I' cell, or an 'I' cell with its own pollution
                            else if (regionMap[x][y]->GetType() != 'I' || (regionMap[x][y]->GetType() == 'I' && regionMap[x][y]->GetPollution() > 0)) {
                                int newPollution = max(regionMap[x][y]->GetPollution(), pollutionSpread);
                                regionMap[x][y]->SetPollution(newPollution);
                            }
                        }
                    }
                }
            }
        }
    }
}

