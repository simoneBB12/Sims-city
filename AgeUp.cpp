#include <iostream>
using namespace std;

#include "Cell.h"


void AgeUp(const int numRows, const int numCols, Cell* regionMap[][100], int& availWorkers){

	//parse through every cell in map
	for(int i = 0; i < numRows; i++){
		for (int j = 0; j < numCols; j++){

			//only residential cells will have children
			if(regionMap[i][j]->GetType() == 'R' || regionMap[i][j]->GetInfantPop() +
				regionMap[i][j]->GetToddlerPop() + regionMap[i][j]->GetAdolescentPop() > 0){


	                        //adolescents age to adults
	                        if(regionMap[i][j]->GetAdolescentPop() > 0){
        	                        regionMap[i][j]->SetPopulation(regionMap[i][j]->GetPopulation() + 1);
                	                regionMap[i][j]->SetAdolescentPop(regionMap[i][j]->GetAdolescentPop() - 1);
                        	        availWorkers++;

	                                regionMap[i][j]->SetHasBeenUpdated(true);
        	                }

				//toddlers age to adolescents
	                        if(regionMap[i][j]->GetToddlerPop() > 0){
        	                        regionMap[i][j]->SetAdolescentPop(regionMap[i][j]->GetAdolescentPop() + 1);
                	                regionMap[i][j]->SetToddlerPop(regionMap[i][j]->GetToddlerPop() - 1);

	                                regionMap[i][j]->SetHasBeenUpdated(true);
        	                }

				//infants age to toddlers
	                        if(regionMap[i][j]->GetInfantPop() > 0){
        	                        regionMap[i][j]->SetToddlerPop(regionMap[i][j]->GetToddlerPop() + 1);
                	                regionMap[i][j]->SetInfantPop(regionMap[i][j]->GetInfantPop() - 1);

	                                regionMap[i][j]->SetHasBeenUpdated(true);
               		  	}

				if (regionMap[i][j]->GetHasBeenUpdated()){
				}
			} //end if-statement

		}//end for-loop cols
	} //end for-loop row

}
