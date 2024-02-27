#include "Cell.h"
#include <iostream>
#include <ctype.h>

// Parameterized constructor
Cell::Cell(char userType, int userPollution, int userPopulation)
: type(userType), pollutionState(userPollution), population(userPopulation),
  radiation(0), hasBeenUpdated(false), infantPop(0), toddlerPop(0), adolescentPop(0),
  radiationBeenUpdated(false)
{
    // Initialize neighbor pointers to nullptr
    fill(begin(neighbors), end(neighbors), nullptr);
}

// Default constructor
Cell::Cell()
: type(' '), pollutionState(0), population(0), radiation(0),
  hasBeenUpdated(false), infantPop(0), toddlerPop(0), adolescentPop(0),
  radiationBeenUpdated(false)
{
    // Initialize neighbor pointers to nullptr
    fill(begin(neighbors), end(neighbors), nullptr);
}

//sets
void Cell::SetType(char userType){ type = userType; }
void Cell::SetPollution(int userPollution) {pollutionState = userPollution;}
void Cell::SetPopulation(int userPopulation) {population = userPopulation;}
void Cell::SetCoordinates(int xVal, int yVal) {
	coordinates.first = xVal;
	coordinates.second = yVal;
}
void Cell::SetHasBeenUpdated(bool status) { hasBeenUpdated = status; }
void Cell::SetCannotGrow(bool state) {cannotGrow = state;}
void Cell::SetRadiation(int currRadiation) {radiation = currRadiation;}
void Cell::SetRadiationBeenUpdated(bool radiationStatus) {radiationBeenUpdated = radiationStatus;}

void Cell::SetInfantPop(int userInfantPop) { infantPop = userInfantPop; }
void Cell::SetToddlerPop(int userToddlerPop) { toddlerPop = userToddlerPop; }
void Cell::SetAdolescentPop(int userAdolescentPop) { adolescentPop = userAdolescentPop; }


//gets
char Cell::GetType() {return type;}
int Cell::GetPopulation() {return population;}
int Cell::GetPollution() {return pollutionState;}
int Cell::GetRow() {return coordinates.first;}
int Cell::GetColumn() {return coordinates.second;}
bool Cell::GetHasBeenUpdated() {return hasBeenUpdated;}
int Cell::GetInfantPop() {return infantPop;}
int Cell::GetToddlerPop() {return toddlerPop;}
int Cell::GetAdolescentPop(){return adolescentPop;}
bool Cell::GetRadiationBeenUpdated() {return radiationBeenUpdated;}
int Cell::GetRadiation() {
    return radiation;
}
bool Cell::GetCannotGrow() {
    return cannotGrow;
}

//adjacency list
void Cell::EstablishNeighbors(Cell* neighbor, int index) {
	if(!isspace(neighbor->GetType())){
		neighbors[index] = neighbor;
	}
}


void Cell::PrintNeighbors() {
	//iterate through neighbors of current cell
	for (int i = 0; i < 8; i++) {
		//if not white space, print neighbor
		if (neighbors[i] != NULL) {
			cout << neighbors[i]->type << " ";
		}
	}//end for loop
}


//check if cell is near powerline
bool Cell::NextToPowerline() {
        for (int i = 0; i < 8; i++) {
                if(neighbors[i] != nullptr) {
                        if (((neighbors[i])->type == 'T') || (((neighbors[i])->type == '#'))) {
                                return true;
                        }
                }
        }

        return false;
}


//functions involving neighbors
bool Cell::hasXNeighborsOfYPop(int numNeighbors, int minPop){

	int MAX_NEIGHBOR_COUNT = 8;
	int index = 0;
	int numSufficientlyPopulatedNeighbors = 0;
	bool hasEnoughNeighbors = false;
	int neighborPop = 0;

	while(index < MAX_NEIGHBOR_COUNT){

		if(neighbors[index] != nullptr){

			neighborPop = neighbors[index]->GetPopulation() + neighbors[index]->GetInfantPop()+
				neighbors[index]->GetToddlerPop() + neighbors[index]->GetAdolescentPop();

			if(neighborPop >= minPop && neighbors[index]->GetHasBeenUpdated() == false){
				numSufficientlyPopulatedNeighbors++;
			}

			else if(neighbors[index]->GetHasBeenUpdated() == true && neighborPop-1 >= minPop){
				//was updated but the unupdated value was still sufficient
				numSufficientlyPopulatedNeighbors++;
			}

		}//end if-block null checker
		index++;
	}


	if(numSufficientlyPopulatedNeighbors >= numNeighbors){
		hasEnoughNeighbors = true;
	}

	return hasEnoughNeighbors;
}


// Function to spread pollution to neighboring Industrial cells
void Cell::SpreadPollution() {
    for (int i = 0; i < 8; i++) {
        if (neighbors[i] != nullptr) {
            if (neighbors[i]->GetType() == 'I') {
                // Calculate the new pollution value
                int newPollution = neighbors[i]->GetPollution() + pollutionState - 1;
                if (newPollution >= 0) {
                    // Set pollution of the neighbor cell
                    neighbors[i]->SetPollution(newPollution);
                }
            }
        }
    }
}


//Function that outputs the final region pollution and will output total pollution in the region
void OutputFinalRegionalPollution(Cell* regionMap[][100], int numRows, int numCols) {
    int totalPollution = 0;

    // Iterate through all cells in the region map
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            // Check if the cell is Industrial ('I')
            if (regionMap[i][j]->GetType() == 'I') {
                // Get and print the pollution for this cell
                int cellPollution = regionMap[i][j]->GetPollution();
                cout << "Pollution in Cell (" << i << ", " << j << "): " << cellPollution << endl;

                // Accumulate the total pollution
                totalPollution += cellPollution;
            }
        }
    }

    // Output the total pollution in the region
    cout << "Total Pollution in the Region: " << totalPollution << endl;
}


//increments radiation surrounding a cell
//only if the cell has radiation == requested radiation
void Cell::UpdateSurroundings(int xRadiation) {
	for (int i = 0; i < 8; i++) {
                if (neighbors[i] != nullptr) {
                        if (neighbors[i]->radiation == xRadiation) {
                                neighbors[i]->IncrementRadiation();
                        }//end if neighbor has xRadiation and radiation has been updated
                }//end if neighbors[i] != null
        }//end for loop
}

//radiation function for nuke and powerplant explosion
//increments radiation and if population > 0, decrements
void Cell::IncrementRadiation() {
        if (radiationBeenUpdated == false) {
                radiation++;
        }//end if radiationBeenUpdated is false

	if (cannotGrow == false) {
		cannotGrow = true;
	}//end if cannotGrow is false

        if (population > 0) {
                //decrements entire population if next to nuke
                if (NextToNuke()) {
                        while (population > 0) {
                                population--;
                        }//end while
                }//end if

                else {

                        if (infantPop > 0) {
                                infantPop--;
                        }
                        else if (toddlerPop > 0) {
                                toddlerPop--;
                        }
                        else if (adolescentPop > 0) {
                                adolescentPop--;
                        }
                        //if only adult
                        else {
                                population--;
                        }
                }//end else
        }//end if
}

//checks if neighbor is next to nuke
//nuke denoted by type == 'X'
bool Cell::NextToNuke() {
        for (int i = 0; i < 8; i++) {
                if (neighbors[i] != nullptr) {
                        if (neighbors[i]->type == 'X') {
                                return true;

                        }//end if neighbors[i].type == X
                }//end if neighbors[i] != null
        }//end for loop

        return false;
}

