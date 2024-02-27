#include <iostream>
#include <string>
#include <utility>      //maybe unnecessary but used in Cell header file

#include "Cell.h"
#include "Functions.h"
using namespace std;


/*
Function:       PrintRegionMap
Input:          regionMap array, numRows, numCols
Output:         void; text is output to screen

Description:    Outputs the elements of regionMap.
*/
void PrintRegionMap(const int numRows, const int numCols, Cell* regionMap[][100]){
    for (int rowIndex = 0; rowIndex < numRows; rowIndex++){
        for (int colIndex = 0; colIndex < numCols; colIndex++){
            Cell* currentCell = regionMap[rowIndex][colIndex];

            // If the cell has a population, display the population
            if (currentCell->GetPopulation() != 0) {
                cout << currentCell->GetPopulation();

		//symbols for children
		if((currentCell->GetInfantPop() != 0) || (currentCell->GetToddlerPop() != 0) ||
		(currentCell->GetAdolescentPop() != 0)){
			for(int i = 0; i < (currentCell->GetAdolescentPop() != 0); i++){
				cout << "*";
			}
			for (int i = 0; i < ((currentCell->GetInfantPop()) + (currentCell->GetToddlerPop()) != 0); i++){
                                cout << "+";
                        }
		}

            }
            // If no population, display the cell type
            else {
                cout << currentCell->GetType();
		//cannot have children in a cell with no adults
            }

            // Display the pollution for any cell with a pollution level of 1 or more
            if (currentCell->GetPollution() > 0) {
                cout << "(" << currentCell->GetPollution() << ")";
            }
            //display radiation for each cell w/ radiation > 0
	    if (currentCell->GetRadiation() > 0) {
		cout << "<" << currentCell->GetRadiation() << ">";
	    }


            cout << "\t"; // Space between cells

        }
        cout << endl; // New line after each row
    }
}


//after each timestep, clear all Cells' "hasBeenUpdated" member bools
void ResetUpdateStatus(const int numRows, const int numCols, Cell* regionMap[][100]){

	for (int i = 0; i < numRows; i++){

                        for (int j = 0; j < numCols; j++){

					regionMap[i][j]->SetHasBeenUpdated(false);

                         } //end for-loop cols

        } //end for-loop rows


}

//resets the "radiationBeenUpdated" bool to false for each cell
void ResetRadiationUpdateStatus(const int numRows, const int numCols, Cell* regionMap[][100]) {
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			regionMap[i][j]->SetRadiationBeenUpdated(false);
		}
	}
}

//after each timestep, check to make sure at least one cell grew (to continue loop)
bool IsUnchanged(Cell* regionMap[][100], int numRows, int numCols){

	for (int i = 0; i < numRows; i++){

                        for (int j = 0; j < numCols; j++){

                                        if (regionMap[i][j]->GetHasBeenUpdated() == true){
						return false;
					}

                         } //end for-loop cols

        } //end for-loop rows

	return true;
}

