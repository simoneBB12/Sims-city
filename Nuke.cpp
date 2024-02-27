#include "Nuke.h"
#include "Cell.h"
#include "Functions.h"
#include <random>
#include <ctime>
#include <iostream>
using namespace std;

//grows nuclear radiation
//cell can have up to 5 radiation
void SpreadNukeRadiation(Cell* regionMap[][100], bool nukeLanded, int numRows, int numCols) {
	//reset radiation status for all cells
	ResetRadiationUpdateStatus(numRows, numCols, regionMap);

	Cell* cellPtr = nullptr;


	if (nukeLanded == true) {
		//iterate through region map
		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				cellPtr = regionMap[i][j];

				//if cell type is the the nuke,
				//update if it fills requirement(s)
				if(cellPtr->GetType() != 'X') {

					//if not right next to nuke or
					//not adjacent to cell that is right next to nuke
					if (cellPtr->GetRadiation() == 2) {
                                                cellPtr->IncrementRadiation();
                                                cellPtr->UpdateSurroundings(0);
						cellPtr->SetRadiationBeenUpdated(true);
                                        }//end if radiation == 2

                                        else if (cellPtr->GetRadiation() == 3) {
                                                cellPtr->IncrementRadiation();
                                                cellPtr->UpdateSurroundings(1);
						cellPtr->SetRadiationBeenUpdated(true);
                                        }//end else if radiation == 3

					else if (cellPtr->GetRadiation() == 4) {
						cellPtr->IncrementRadiation();
                                                cellPtr->UpdateSurroundings(2);
						cellPtr->SetRadiationBeenUpdated(true);
					}//end else if radiation == 4

					//if right next to nuke, update radiation
					//and cells adjacent to cells right next to nuke
					else if (cellPtr->NextToNuke()) {
						if (cellPtr->GetRadiation() == 0) {
							cellPtr->IncrementRadiation();
                                                        cellPtr->SetCannotGrow(true);
							cellPtr->SetRadiationBeenUpdated(true);
						}//end else if radiation == 0

						else if (cellPtr->GetRadiation() == 1) {
							cellPtr->IncrementRadiation();
                                                        cellPtr->SetRadiationBeenUpdated(true);
							cellPtr->UpdateSurroundings(0);
						}//end else if radiation == 1

						else if (cellPtr->GetRadiation() == 2) {
							cellPtr->IncrementRadiation();
                                                        cellPtr->SetRadiationBeenUpdated(true);
							cellPtr->UpdateSurroundings(1);
						}//end else if radiation == 2

						else if (cellPtr->GetRadiation() == 3) {
                                                        cellPtr->IncrementRadiation();
                                                        cellPtr->SetRadiationBeenUpdated(true);
							cellPtr->UpdateSurroundings(2);
                                                }//end else if radiation == 3

						else if (cellPtr->GetRadiation() == 4) {
                                                        cellPtr->IncrementRadiation();
                                                        cellPtr->SetRadiationBeenUpdated(true);
							cellPtr->UpdateSurroundings(3);
                                                }//end else if radiation == 4

					}//end else if nextTooNuke()
				}//end if type != 'X'
			}//end j for loop
		}//end i for loop
	}//end if
}


//inserts nuke onto region map
void PlaceNuke(Cell* regionMap[][100], bool &nukeLanded, int numRows, int numCols) {
	if (nukeLanded == false) {
		//generate random seed for x and y coords
		srand((int)time(0));

		//generate random x and y coordinates for 1 x 1 nuke//generate random x and y coordinates for 1 x 1 nuke
		int randXCoord = rand() % numRows;
		int randYCoord = rand() % numCols;
		Cell* cellPtr = regionMap[randXCoord][randYCoord];

		//if coords' type is P or is a space, regenerate coords
		//so powerplant can (hopefully) explode
		while (cellPtr->GetType() == 'P' || cellPtr->GetType() == ' ') {
			int randXCoord = rand() % numRows;
        	        int randYCoord = rand() % numCols;
                	cellPtr = regionMap[randXCoord][randYCoord];
		}


		//insert nuke
		cellPtr->SetType('X');
		cellPtr->SetCannotGrow(true);
		cellPtr->SetPopulation(0);
		cellPtr->SetRadiation(-100);

		nukeLanded = true;
	}
}
