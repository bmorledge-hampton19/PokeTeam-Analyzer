#include <iostream>
#include <string>
#include "PokeQueries.h"//handles queries
using namespace std;

//-----------------------------------------
//PokeTeam Analyzer
//
//CS 374 Final Project
//Ben Cameron Tom & Tyler
//------------------------------------------

int main() {
	cout << "Welcome to Poketeam Analyzer! \n \n";
	char selection;
	cout << "Would you like to: \n 1) Analyze team of pokemon \n 2) Look up single pokemon stats\n ";
	cin >> selection;
	cout << "\n \n";
	int pokeIDs[6];
	string pokeNames[6];
	while (true) {
		if (selection == '1') {//team analyzer. Finds best team to combat
			cout << "Enter 6 names of pokemon to add to your team.\n";
			for (int i = 0; i < 6; i++) {//loop until we have 6 different pokemon
				do {//loop until user gives valid pokemon name
					cin >> pokeNames[i];
					pokeIDs[i] = getPokeID(pokeNames[i]);
					if (pokeIDs[i] == 0) cout << "No generation 1 Pokemon have this name. Please try again.\n";
				} while (pokeIDs[i] == 0);
			}//finished team creation
			cout << "Team created! You selected: \n";
			for (int i = 0; i < 6; i++) {
				cout << pokeNames[i] << " ID # " << pokeIDs[i] << "\n";
			}
			//run teamAnalysis query and find best team
			teamCalculations(pokeIDs);
		}
		else if (selection == '2') {//pokedex, single pokemon lookup
			
			do {
				cout << "Enter the name of the pokemon whose stats you would like to see.";
				cin >> pokeNames[0];
				pokeIDs[0] = getPokeID(pokeNames[0]);
				if (pokeIDs[0] == 0) cout << "No generation 1 Pokemon have this name. Please try again.\n";
			} while (pokeIDs[0] == 0);



		}
		else cout << "Invalid selection.\n";

		cout << "\n \n Would you like to: \n 1) Analyze team of pokemon \n 2) Look up single pokemon stats\n ";
		cin >> selection;
	}
}