#include <iostream>
#include <fstream>
#include "Cell.h" 
#include "Zoomin.h"


void Zoom(Cell* regionMap[][100], const int numRows, const int numCols) {
    int rowIndex, colIndex;

    // Prompt user to input coordinates
    cout << "Enter coordinates (row & col): ";
    cout << "Row:"<<endl;
    cin >> rowIndex;
    cout << "Col:"<<endl;
    cin >> colIndex;
    // Validate input
    if (rowIndex < 0 || rowIndex >= numRows || colIndex < 0 || colIndex >= numCols) {
        cout << "Invalid coordinates. Out of bounds.\n";
        return;
    }

    // Get the current cell
    Cell* currCellPtr = regionMap[rowIndex][colIndex];

    // Print information for the current cell
    cout << "Coordinates: (" << rowIndex << ", " << colIndex << ")\n";
    cout << "Type: " << currCellPtr->GetType() << "\n";
    cout << "Population: " << currCellPtr->GetPopulation() << "\n";
    cout << "Pollution " << currCellPtr->GetPollution()<< "\n";
    //add pop specifics, nuke information, and Raderation at coordinates

    cout << "\n";
    
 
}
