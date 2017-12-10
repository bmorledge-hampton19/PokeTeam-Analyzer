
#include "PokeQueries.h"
using namespace std;


int getPokeID(string &name) {//return pokemon ID for given name. If no pokemon have that name return 0
	int id = 0;
	SQL* pokemon = new SQL();
	id = pokemon->getID(name);
	//return 0 if no proper name
	delete pokemon;
	return id;
}

Poke getPokeObject(int ID) {//gets pokemon obeject from id

	SQL* pokemon = new SQL();
	Poke poke = pokemon->getPoke(ID);
	delete pokemon;
	return poke;

}

//teamCalculations takes team of 6 pokemon and runs through combinations of other pokemon
//returned by getBestAttacker query. Each ten pokemon returned must be cross refrenced to
//create the optimal attacking team. Print this team to user
void teamCalculations(int team[6]) {
	vector<Poke>FINALTEAM;
	vector<vector<Poke>>AttackingPokemon;
	for (int i = 0; i < 6; i++) {
		SQL * pokemon = new SQL();
		AttackingPokemon.push_back(pokemon->getBestAttackers(team[i]));
		delete pokemon;
	}

	//cross check query returned pokemon against other 5 pokemon on the team
	for (int i = 0; i < AttackingPokemon.size(); i++) {
		double avgMatchup[10];
		for (int j = 0; j < AttackingPokemon[i].size(); j++) {
			avgMatchup[j] = 0;
			//pokemon avgMatchup is sum of multipliers against all pokemon on other team
			for (int k = 0; k < 6; k++) {
				SQL * pokemon = new SQL();
				avgMatchup[j] += pokemon->getMul(team[k], AttackingPokemon[i][j]);//result of query
				delete pokemon;
			}
		}
		int indexHigh = 0;
		double currentHigh = 0;
		//find highest overal multiplier among these 10 pokemon
		for (int l = 0; l < 10; l++) {
			if (avgMatchup[l] > currentHigh) {
				currentHigh = avgMatchup[l];
				indexHigh = l;
			}
		}
		FINALTEAM.push_back(AttackingPokemon[i][indexHigh]);
	}
	//print to user
	cout << "The best team of 6 is...\n";
	for (int i = 0; i < FINALTEAM.size(); i++) {
		cout << FINALTEAM[i].getName() << endl;
	}
}


