#include "Cell.h" 
#include "Meltdown.h"
#include <iostream>

// addRadiationToCell helper function
void addRadiationToCell(Cell* regionMap[][100], int x, int y, int numRows, int numCols, int additionalRadiation) {
    if (x >= 0 && x < numRows && y >= 0 && y < numCols && regionMap[x][y] != nullptr) {
        // Set radiation
        int currentRadiation = regionMap[x][y]->GetRadiation();
        regionMap[x][y]->SetRadiation(currentRadiation + additionalRadiation);

        // Set population to zero and cannotGrow to true due to radiation
        regionMap[x][y]->SetPopulation(0);
        regionMap[x][y]->SetCannotGrow(true);
    }
}

// This function will check for meltdown and if true will trigger
void checkForMeltdown(Cell* regionMap[][100], int numRows, int numCols, bool& meltdownOccurred) {
    if (meltdownOccurred) {
        return; // If a meltdown has already occurred don't run again.
    }

    // Directions for the 8 adjacent cells around P cell
    int adjX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int adjY[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (regionMap[i][j] != nullptr && regionMap[i][j]->GetType() == 'P') {
                // Check if P cell has radiation
                int currentRadiation = regionMap[i][j]->GetRadiation();
                if (currentRadiation > 0) {
                    // The P cell itself has radiation so trigger meltdown
                    addRadiationToCell(regionMap, i, j, numRows, numCols, 3); // Add +3 radiation to the P cell

                    // Add +2 radiation to adjacent cells
                    for (int k = 0; k < 8; ++k) {
                        int newX = i + adjX[k];
                        int newY = j + adjY[k];
                        if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols) {
                            addRadiationToCell(regionMap, newX, newY, numRows, numCols, 2);
                        }
                    }

                    // Add +1 radiation to cells around the adjacent cells
                    for (int k = 0; k < 8; ++k) {
                        int adjI = i + adjX[k];
                        int adjJ = j + adjY[k];

                        for (int l = 0; l < 8; ++l) {
                            int newX = adjI + adjX[l];
                            int newY = adjJ + adjY[l];

                            // Skip the center P cell and the directly adjacent cells
                            if (!(newX == i && newY == j) && !(abs(newX - i) <= 1 && abs(newY - j) <= 1)) {
                                if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols &&
                                    regionMap[newX][newY] != nullptr) {
                                    // Check if the cell already has radiation, if not, add +1 radiation
                                    if (regionMap[newX][newY]->GetRadiation() == 0) {
                                        addRadiationToCell(regionMap, newX, newY, numRows, numCols, 1);
                                    }
                                }
                            }
                        }
                    }

                    meltdownOccurred = true;
	            cout << "\033[5m\033[31m**POWER PLANT CRITICAL MELTDOWN IN PROCESS**\033[0m" << endl;
                    return; // Terminate
                }
            }
        }
    }
}
