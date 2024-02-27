#ifndef CELLH
#define CELLH

#include <utility>
using namespace std;

class Cell{

    	public:
		void Print();

            	//constructor
             	Cell(char userType, int userPollution, int userPopulation);
            	Cell();

            	//sets
            	void SetType(char userType);
            	void SetPollution(int userPollution);
            	void SetPopulation(int userPopulation);
		void SetCoordinates(int xVal, int yVal);
		void SetHasBeenUpdated(bool status);
		void SetCannotGrow(bool state);
                void SetRadiation(int currRadiation);
		void SetInfantPop(int userInfantPop);
		void SetToddlerPop(int userToddlerPop);
		void SetAdolescentPop(int userAdolescentPop);
		void SetRadiationBeenUpdated(bool radiationStatus);

            	//gets
            	char GetType();
            	int GetPopulation();
            	int GetPollution();
		int GetRow();
		int GetColumn();
		bool GetHasBeenUpdated();
		bool GetCannotGrow();
                int GetRadiation();
		int GetInfantPop();
		int GetToddlerPop();
		int GetAdolescentPop();
		bool GetRadiationBeenUpdated();

            	//create adjacency list
		void EstablishNeighbors(Cell* neighbor, int index);
		void PrintNeighbors();

		//functions involving neighbors
		bool hasXNeighborsOfYPop(int numNeighbors, int minPop);
		bool NextToPowerline();
		bool CheckNeighborBeenUpdated();


		void IndustrialUpdate(int& availWorkers);

		//functions regarding pollution spread
                void IndustrialUpdatePopulation(int& availableWorkers);
                void SpreadPollution();

                //function to output regional pollution
                void OutputFinalRegionalPollution(Cell* regionMap[][100], int numRows, int numCols);

		//radiation function for nuke and powerplant explosion
                void IncrementRadiation();
                bool HasXRadiation(int xRadiation);
		void UpdateSurroundings(int xRadiation);

                //functions concerning nukes
                bool NextToNuke();


    	private:
            	char type;
            	int pollutionState;
            	int population;	//this will refer only to the adult/working population! (not kids)
		int infantPop;
		int toddlerPop;
		int adolescentPop;
            	pair<int,int> coordinates;
            	Cell* neighbors[8]; //max possible neighbors; adjacency list
		bool hasBeenUpdated;
		bool cannotGrow;
                int radiation;
		bool radiationBeenUpdated;

};

#endif
