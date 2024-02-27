# Sims-city
Csce 2110 PROJECT 2 - SIM CITY
Group 216-3: Simone Brewington, Abel Montoya, Carlie Reynoso, Emily Warren

Compile Instructions:

	Use the command "g++ *.cpp" to compile the program.

Runtime Instructions:

	Use the command "./a.out" to run the program.
	When prompted, enter the file name "config1.txt."
	Follow the instructions on the menu, described in more detail below, to
	print the map, move timesteps, quit, or more. Enter the number of the desired
	menu option and press enter to take that action.

Program Description:

	The program asks the user for the configuration file name, then reads in region-specific 
	information (layout from a CSV 	file, time limit, refresh rate). The region map is created 
	as a 2D array of Cell object pointers containing information about the cell's type, population, 
	pollution state, neighbors, radiation, nuke location, and ages.

	Outputs initial output following all logic in the program with menu options for user input. 
	Menu options are in a 1-5 number format that waits for user choices to run the desired 
	functionality. Option 1 is to print the region map at the current timestep, 2 is to move 
	to the next timestep, 3 will zoom in on user input coordinates, 4 will clear the screen, and 	
	5 to quit the process.

	Growth is prioritized in upper-left cells. Growth in specific sectors modifies the availability 
	of total goods and workers depicted at each timestep and used for other sectors' growth. 
	There is a random possibility of a nuke landing on any part of the region, causing radiation 
	values to spread throughout the region each timestep. If the Powerplant (P) gets hit by radiation, 
	the power plant will alert to a meltdown and cause radiation to spike around it. This simulation 
	could go on indefinitely until the user presses 5 to terminate.

