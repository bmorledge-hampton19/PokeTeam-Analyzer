
#include <string>
#include <iostream>
#include "SQLServer.h"//handles interaction with Database
#include "Poke.h" //handles pokemon objects
#include <vector>
#include "TeamSort.h"
#include <algorithm>
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
	Poke poke = steve->getPoke(ID);
	delete steve;
	return poke;

}

void teamCalculations(int team[6]) {//returns 
	vector<Poke>FINALTEAM;
	vector<vector<Poke>>AttackingPokemon;
	for (int i = 0; i < 6; i++) {
		SQL * steve = new SQL();
		AttackingPokemon.push_back(steve->getBestAttackers(team[i]));
		delete steve;
	}
	
	/*vector<Poke>DefendingTeam;
	SQL steve = SQL();
	for (int i = 0; i < 6; i++)
		DefendingTeam.push_back(steve.getPoke(team[i]));*/


	for (int i = 0; i < AttackingPokemon.size(); i++) {
		double avgMatchup[10];
		for (int j = 0; j < AttackingPokemon[i].size(); j++) {
			avgMatchup[j] = 0;
			for (int k = 0; k < 6; k++) {
				SQL * steve = new SQL();
				avgMatchup[j] += steve->getMul(team[k], AttackingPokemon[i][j]);//result of query
				delete steve;
			}
		}
		int indexHigh = 0;
		double currentHigh = 0;
		for (int l = 0; l < 10; l++) {
			if (avgMatchup[l] > currentHigh) {
				currentHigh = avgMatchup[l];
				indexHigh = l;
			}
		}
		FINALTEAM.push_back(AttackingPokemon[i][indexHigh]);
	}

	cout << "The best team of 6 is...\n";
	for (int i = 0; i < FINALTEAM.size(); i++) {
		cout << FINALTEAM[i].getName() << endl;
	}
}


