#include <iostream>
#include <stdexcept>	//error handling (optional)
#include <string>
#include "CCell.h"
#include "ICell.h"
#include "Cell.h"
#include "Functions.h"
#include "RCell.h"
#include "Zoomin.h"
#include <random>	//for nuke
#include <ctime>	//for nuke
#include "Nuke.h"
#include "Meltdown.h"
#include "Initialize.h"
#include "AgeUp.h"

using namespace std;

void Menu();

int main() {

    	//declaring vars
    	int availGoods = 0;
    	int availWorkers = 0;
    	int timeLimit, refreshRate; 	//will be initialized in ReadFiles
	int numCols, numRows; 		//will be initialized in ReadFiles
	string regionFileName;
	const int MAX_COLS = 100;
	int currentStep = 0;
	int option;
	int nukeStep;
	bool radiationInhibitCommercialUpdate = false;
	bool radiationInhibitIndustrialUpdate = false;
	bool nukeLanded = false;


	//read in initial information (not 2D array info yet)
	ReadFiles(timeLimit, refreshRate, numCols, numRows, regionFileName, availWorkers, availGoods);

    	//create array and parsing variables
    	Cell* regionMap[numRows][MAX_COLS];

	//populate array with info from file + set up adjacency lists
	cout << "Intitial State" << endl << endl;
	FillArray(regionMap, numRows, numCols, regionFileName, availWorkers, availGoods);
	PopulateAdjacencyLists(regionMap, numRows, numCols);

	//creates time step range for nuke to spawn in using seed w/ random time
	//random time step cannot be the first nor the last
	srand((int)time(0));
	nukeStep = rand() % (timeLimit - 1) + 1;

	bool meltdownOccurred = false;

	Cell* cellPtr = nullptr;

	do {
		Menu();
		cin >> option;
		switch(option) {
			case 1:

				// Check for meltdown if it hasn't occurred yet
        			if (!meltdownOccurred) {
          		 		checkForMeltdown(regionMap, numRows, numCols, meltdownOccurred);
       				}

				//print sim city map
		                PrintRegionMap(numRows, numCols, regionMap);

		                cout << endl << "Available Workers: " << availWorkers << endl;
        		        cout << "Available Goods: " << availGoods << endl;

        		        //outputs nuclear state
                		if (nukeStep - 1 == currentStep) {
                        		cout << endl << "NUKE INCOMING!" << endl;
                		}
               			 if (nukeStep == currentStep) {
                		        cout << endl << "\033[5m\033[31mNUKE HAS LANDED!!!\033[0m" << endl;
                		}
				cout << "____________________________________________________________" << endl;
			break;
			case 2:
				currentStep++;
				cout << "State " << currentStep << endl << endl;

				 do {
                       			 //updates commmercial cells
                        		if (availWorkers != 0 && availGoods != 0 && radiationInhibitCommercialUpdate == false) {
                                		UpdateCommercial(availGoods, availWorkers, numRows, numCols, regionMap, radiationInhibitCommercialUpdate);
                        		}
                        		//updates industrial cells
                        		if (availWorkers >= 2 && radiationInhibitIndustrialUpdate == false) {
                                		IndustrialUpdate(numRows, numCols, availWorkers, availGoods, regionMap, radiationInhibitIndustrialUpdate);
                        		}

                        		//if at least one region cannot update, break loop
                        		if (radiationInhibitCommercialUpdate || radiationInhibitIndustrialUpdate == true) {
                                		break;
                        		}
                		}while (availGoods > 0 && availWorkers > 0);

                		//reset radiationInhibitsUpdate status
               	 		radiationInhibitCommercialUpdate = false;
                		radiationInhibitIndustrialUpdate = false;

                		//updates residential cells
                		UpdateResidential(numRows, numCols, regionMap, availWorkers);

				AgeUp(numRows, numCols, regionMap, availWorkers);

				//calls nuke + updates nuclear radiation
				 if (nukeStep <= currentStep) {
                        		PlaceNuke(regionMap, nukeLanded, numRows, numCols);
                	        	SpreadNukeRadiation(regionMap, nukeLanded, numRows, numCols);
		                }


				if(IsUnchanged(regionMap, numRows, numCols)) {
					break;
				}
				else {
					ResetUpdateStatus(numRows, numCols, regionMap);
				}

				cout << "____________________________________________________________" << endl;
				break;
		case 3:
			Zoom(regionMap, numRows, numCols);
			break;

		case 4:
			system("clear");
			cout << "screen clear"<<endl;
			cout << "____________________________________________________________" << endl;

			break;

		case 5:
			cout << "Program successfully exited!" << endl;
			break;

		default:
			cout << "Invalid input" << endl;
			break;

		}

	}while(option != 5);


	//delete dynamically-allocated objects
	DeleteArray(regionMap, numRows, numCols);


    	return 0;

}

void Menu(){
	cout << "choose an option"<<endl;
	cout << "1-Print map at current time step"<<endl;
	cout << "2-Next time step"<<endl;
	cout << "3-Zoom on coordinates"<<endl;
	cout << "4-clear screen"<<endl;
	cout << "5-Quit"<<endl;
	cout << "____________________________________________________________" << endl;
}

