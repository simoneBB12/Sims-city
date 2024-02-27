#include <iostream>
#include <fstream>      //file reading
#include <stdexcept>	//error handling (optional)
#include <string>
#include <stdlib.h>     //stoi
#include <algorithm>	//count function
#include <utility>      //maybe unnecessary but used in Cell header file
#include "Cell.h"
#include "Functions.h"
using namespace std;


/*
Function: 	ReadFiles
Input: 		Reference vars to fill (timeLimit, refreshRate, numCols, numRows,
		regionFileName)
Output:		void, but reference variables are returned with new values

Description:	Moves all of the initial steps in main.cpp to a function of its own.
		Prompts for & reads in user input for filename and then parses through
		files for critical information. This is NOT where the 2D array is
		created; that is a separate function (InitializeRegionMap).
*/
void ReadFiles(int& timeLimit, int& refreshRate, int& numCols, int& numRows, string& regionFileName, int& availWorkers, int& availGoods){

        //declaring vars
        string configFileName;
	//string regionFileName;
        ifstream configFile;
        ifstream regionFile;
        string workingString;

        //prompt for file name
        cout << "Enter file name: ";
        cin >> configFileName;
	cout << endl;

        //open configuration file
        configFile.open(configFileName);

        //read 1st line and get region file name
        getline(configFile, workingString);
        regionFileName = workingString.substr(14, 11);

        //read 2nd line and get time limit
        getline(configFile, workingString);
        workingString = workingString.erase(0,11);
        timeLimit = stoi(workingString);

        //read 3rd line and get refresh rate
        getline(configFile, workingString);
        workingString = workingString.erase(0,13);
        refreshRate = stoi(workingString);

        //open region file
        regionFile.open(regionFileName);

        //find numCols
        getline(regionFile, workingString);
        int numCommas = count(workingString.begin(), workingString.end(), ',');

        numCols = numCommas + 1;

        //find numRows
	numRows = 0;
        while(!regionFile.eof()){
                getline(regionFile, workingString);
                numRows++;
        }

        //close fully-parsed region file
        regionFile.close();

}



/*
Function:       FillArray
Input:          Empty array, numRows, numCols, name of file with array data
Output:         void, but array is returned with all values

Description:    Reads from csv file to populate 2D array of user-defined size.
		Note that the number of columns is capped at 100 in main; this
		allows array passing and should not functionally inhibit a user.
*/
void FillArray(Cell* regionMap[][100], const int numRows, const int numCols, const string regionFileName, int& availWorkers, int& availGoods){

        //create parsing variables
	string workingString;
	ifstream regionFile;
        char workingChar;
        int colIndex = 0;

        //open new region file to read
        regionFile.open(regionFileName);
        for (int rowIndex = 0; rowIndex < numRows; rowIndex++){
                getline(regionFile, workingString);
                colIndex = 0;

                        for (int stringIndex = 0; stringIndex <
                                workingString.length(); stringIndex++) {

                                workingChar = workingString[stringIndex];

                                if(workingChar != ','){

                                        Cell* tempCellPtr = new Cell;
                                        tempCellPtr->SetType(workingChar);

                                        regionMap[rowIndex][colIndex] = tempCellPtr;
                                        cout << (regionMap[rowIndex][colIndex])->GetType()
                                        << "\t";
                                        regionMap[rowIndex][colIndex]->SetCoordinates(rowIndex, colIndex);

                                        colIndex++;
                                } //get rid of commas (if-block)

                        } //stringIndex for-loop

                        cout << endl;

        } //rowIndex for loop
	cout << endl << "Available Workers: " << availWorkers << endl;
	cout << "Available Goods: " << availGoods << endl << endl;
        //close region file after reading in array
        regionFile.close();
}




/*
Function:       PopulateAdjacencyLists
Input:          regionMap array, numRows, numCols
Output:         void, but array is returned with adjacency lists for all elements

Description:    Parses through regionMap and, for each element, saves pointers to
		each neighbor in that element's data member adjacency list.
*/
void PopulateAdjacencyLists(Cell* regionMap[][100], int numRows, int numCols){

        //establishing pointers and variables for adjacenecy list
        Cell* currCellPtr = nullptr;
        Cell* tempCellPtr = nullptr;
        int colIndex;
        ifstream regionFile;
        int neighIndex;

        //iterate through intitial region map
        for (int rowIndex = 0; rowIndex < numRows; rowIndex++) {

                for (colIndex = 0; colIndex < numCols; colIndex++) {

                        neighIndex = 0;

                        currCellPtr = regionMap[rowIndex][colIndex];

                        //check top neighbor
                        if (rowIndex > 0) {
                                //get top left neighbor
                                if (colIndex > 0) {

                                        tempCellPtr = regionMap[rowIndex - 1][colIndex - 1];
                                        //put top left cell in adjacency list
                                        currCellPtr->EstablishNeighbors(tempCellPtr, neighIndex);
                                        neighIndex++;
                                }//end if statement top left neighbor

                                //get top right neighbor
                                if (colIndex < (numCols - 1)) {

                                        tempCellPtr = regionMap[rowIndex - 1][colIndex + 1];
                                        //put top right cell in adjacency list
                                        currCellPtr->EstablishNeighbors(tempCellPtr, neighIndex);

                                        neighIndex++;

                                }//end if statement top right neighbor


                                //get cell directly above current cell
                                tempCellPtr = regionMap[rowIndex - 1][colIndex];

                                //establish top cell as current cell's neighbor
                                currCellPtr->EstablishNeighbors(tempCellPtr, neighIndex);

                                neighIndex++;

                        }//end if statement top neighbor

                        //check bottom neighbor
                        if (rowIndex < numRows - 1) {

                                //check bottom left neighbor
                                if (colIndex > 0) {

                                        tempCellPtr = regionMap[rowIndex + 1][colIndex - 1];

                                        //put bottom left cell as current cell's neighbor
                                        currCellPtr->EstablishNeighbors(tempCellPtr, neighIndex);

                                        neighIndex++;

                                }//end if statement bottom left neighbor


                                //check bottom right
                                if (colIndex < (numCols - 1)) {

                                         tempCellPtr = regionMap[rowIndex + 1][colIndex + 1];

                                        //put bottom right cell as current cell's neighbor
                                        currCellPtr->EstablishNeighbors(tempCellPtr, neighIndex);

                                        neighIndex++;

                                }//end if statement bottom right neighbor

                                //get cell directly below current cell
                                tempCellPtr = regionMap[rowIndex + 1][colIndex];

                                //establish bottom cell as current cell's neighbor
                                currCellPtr->EstablishNeighbors(tempCellPtr, neighIndex);

                                neighIndex++;
                        }//end if statement bottom neighbor


                        //check left neighbor
                        if (colIndex > 0) {

                                //get cell left of current cell
                                tempCellPtr = regionMap[rowIndex][colIndex - 1];

                                //establish left cell as current cell's neighbor
                                currCellPtr->EstablishNeighbors(tempCellPtr, neighIndex);

                                neighIndex++;
                        }//end if statement left neighbor


                        //check right neighbor
                        if (colIndex < (numCols - 1)) {

                                //get cell right of current cell
                                tempCellPtr = regionMap[rowIndex][colIndex + 1];

                                //establish right cell as current cell's neighbor
                                currCellPtr->EstablishNeighbors(tempCellPtr, neighIndex);

                                neighIndex++;
                        }//end if statement right neighbor


                }//colIndex for loop


        }//rowIndex for loop

}



/*
Function:       DeleteArray
Input:          regionMap array, numRows, numCols
Output:         void; regionMap is returned without dynamic cell objects

Description:    Parses through and deletes each dynamically-allocated element
		of regionMap.
*/
void DeleteArray(Cell* regionMap[][100], const int numRows, const int numCols){

        for (int i = 0; i < numRows; i++){
                for (int j = 0; j < numCols; j++){
                        delete regionMap[i][j];
                } //column parse for-loop
        } //row parse for-loop
}
