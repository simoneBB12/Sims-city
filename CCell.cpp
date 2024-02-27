#include <iostream>
#include "CCell.h"
#include "Cell.h"
#include "Functions.h"

void UpdateCommercial(int& availGoods, int& availWorkers, const int numRows, const int numCols, Cell* regionMap[][100], bool &radiationInhibitUpdate){

	Cell* workingCellPtr = regionMap[0][0];

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {

                        workingCellPtr = regionMap[i][j];

			if(availGoods > 0 && availWorkers > 0 && workingCellPtr->GetType() == 'C'){
				//if population is zero
				if(workingCellPtr->GetPopulation() == 0){

					if(workingCellPtr->NextToPowerline()){
						IncrementCommercial(workingCellPtr, availWorkers, availGoods, radiationInhibitUpdate);
                       				//output regional state fxn call

					}

					else if(workingCellPtr->hasXNeighborsOfYPop(1,1)){
						IncrementCommercial(workingCellPtr, availWorkers, availGoods, radiationInhibitUpdate);
               		                	//output regional state fxn call
					}

				} //end if-pop-0 block


				//if population is one
				else if(workingCellPtr->GetPopulation() == 1){

						if(workingCellPtr->hasXNeighborsOfYPop(2,1)){
							IncrementCommercial(workingCellPtr, availWorkers, availGoods, radiationInhibitUpdate);
							//output regional state fxn call

						}

				} //end if-pop-1 block

//				else{
//				} //end else block (pop >= 2)

			} //end primary if loop
		}//end for-loop cols

	}//end for-loop rows
}



//decreases availGoods/Workers to increase commercial population if conditions are met
void IncrementCommercial(Cell* workingCellPtr, int& availWorkers, int& availGoods, bool &radiationInhibitUpdate){
	if(workingCellPtr->GetCannotGrow() == false) {
		workingCellPtr->SetPopulation( workingCellPtr->GetPopulation() + 1 );
		availWorkers--;
		availGoods--;
		workingCellPtr->SetHasBeenUpdated(true);
	}
	else {
		radiationInhibitUpdate = true;
	}
}

