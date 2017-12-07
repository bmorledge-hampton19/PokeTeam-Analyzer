
#include <string>
#include <iostream>
#include "SQLServer.h"//handles interaction with Database
#include "Poke.h" //handles pokemon objects
using namespace std;

int getPokeID(string name) {//return pokemon ID for given name. If no pokemon have that name return 0
	int id = 0;
	SQL* steve = new SQL();
	id = steve->getID(name);
	//return 0 if no proper name
	delete steve;
	return id;
}

Poke getPokeObject(int ID) {

	SQL* steve = new SQL();

	

}

void teamCalculations(int team[6]) {//returns 

	for (int i = 0; i < 6; i++) {
		SQL steve = SQL();
		Poke* poke = steve.getBestAttackers(team[i]);

		cout << "The best pokemon against selection " << i + 1 << " is " << poke->getName() << "." << endl;

		delete poke;
	}
}


