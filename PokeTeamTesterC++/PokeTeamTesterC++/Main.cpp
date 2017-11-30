#include <iostream>
#include "Poke.h"

using namespace std;

int main() {

	// The ID number of the opposing Pokemon.
	int opposingPoke;

	// Prompt the user to choose an opposing pokemon
	cout << "Welcome to the PokeTeam Analyzer." << endl;
	cout << "Input the ID of the pokemon to be fought: ";
	cin >> opposingPoke;

	Poke* poke = (pokeMatchup(opposingPoke));

	cout << endl << "The best pokemon to fight your choice would be " << poke->getName() << "." << endl;
}

Poke* pokeMatchup(int ID) {

	// Prompt SQLServer class to run query to find best matchup
	// against pokemon of given ID

}