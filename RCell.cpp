
#include <iostream>
#include "Cell.h"
#include "Functions.h"


//adult increment
void IncrementResidentialAdult(Cell* cellPtr, int& availWorkers) {
	if (cellPtr->GetCannotGrow() == false) {
        	cellPtr->SetPopulation(cellPtr->GetPopulation()+1);

        	availWorkers++;
        	cellPtr->SetHasBeenUpdated(true);
	}
}


//child increment
void IncrementResidentialChild(Cell* cellPtr) {
	if (cellPtr->GetCannotGrow() == false) {
        	cellPtr->SetInfantPop(cellPtr->GetInfantPop()+1);

        	cellPtr->SetHasBeenUpdated(true);
		//no availWorker increase because children cannot work
		//see AgeUp function for how this changes
	}
}


void UpdateResidential(int numRows, int numCols, Cell* regionMap[][100], int& availWorkers) {
	//reset updated status
//	ResetUpdateStatus(numRows, numCols, regionMap);
	//get intial population
	int pop;

	Cell* cellPtr;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j <numCols; j++) {

			cellPtr = regionMap[i][j];

			//if residential cell
			if (cellPtr->GetType() == 'R') {

				//base case
				if (cellPtr == nullptr) {
					return;

				}

				//sum all subpops to find total population within a cell
				pop = cellPtr->GetPopulation() + cellPtr->GetAdolescentPop() +
					cellPtr->GetToddlerPop() + cellPtr->GetInfantPop();

				if (pop == 0) {	//note that this if-statement checks total pop
					if (cellPtr->NextToPowerline()) {
						IncrementResidentialAdult(cellPtr, availWorkers);

					}//end if nexttopowerline
					else if (cellPtr->hasXNeighborsOfYPop(1, 1)) {
						IncrementResidentialAdult(cellPtr, availWorkers);

					}//end else if
				}//end if statment population = 0

				else if (pop == 1) {
					if(cellPtr->hasXNeighborsOfYPop(2, 1)) {

						IncrementResidentialAdult(cellPtr, availWorkers);

					}//end if statement
				}//end else if statement

				else if (pop == 2) {

					if(cellPtr->hasXNeighborsOfYPop(4, 2)) {

						//third house member is a child (not adult)
        		            		IncrementResidentialChild(cellPtr);

        				}//end if statement
				}//end else if statement

				else if (pop == 3) {
					if(cellPtr->hasXNeighborsOfYPop(6, 3)) {

						//fourth house member is a child (not adult)
        	        		        IncrementResidentialChild(cellPtr);

		        	        }//end if statement
				}//end else if statement

				else if (pop == 4) {

					if(cellPtr->hasXNeighborsOfYPop(8, 4)) {

						//fifth house member is a child (not adult)
						IncrementResidentialChild(cellPtr);

               				}//end if statement
				}//end else if statement

			}

				//cannot have more than 5 house members
		}

	}
}

