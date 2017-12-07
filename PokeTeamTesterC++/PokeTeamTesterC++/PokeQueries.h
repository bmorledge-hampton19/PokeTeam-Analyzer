
#include <string>
#include <iostream>
#include "SQLServer.h"//handles interaction with Database
#include "Poke.h" //handles pokemon objects
#include <vector>
#include "TeamSort.h"
using namespace std;



int getPokeID(string name) {//return pokemon ID for given name. If no pokemon have that name return 0
	int id = 0;
	SQL steve = SQL();
	id = steve.getID(name);
	//return 0 if no proper name
	return id;
}

void teamCalculations(int team[6]) {//returns 

	vector<Poke *>AttackingPokemon;
	for (int i = 0; i < 6; i++) {
		SQL steve = SQL();
		Poke* poke = steve.getBestAttackers(team[i]);
		AttackingPokemon.push_back(poke);
	}
	
	vector<Poke>DefendingTeam;
	SQL steve = SQL();
	for (int i = 0; i < 6; i++)
		DefendingTeam.push_back(steve.getPoke(team[i]));
	for (int i = 0; i < AttackingPokemon.size(); i++)
		delete[] AttackingPokemon[i];	//maybe don't need for loop
}


