#pragma once
#include <string>
using namespace std;

// A basic Pokemon class which stores all the information on each pokemon being used by the DB.
class Poke {

private:
	int ID;
	//Image?
	int hp;
	int attack;
	int defense;
	int speed;
	int special;
	string name;
	int type1;
	int type2;

public:
	Poke(int ID, string name, int hp, int attack, int defense, int speed, int special, int type1, int type2);
	Poke() {};
	int getID();
	//Get Image?
	string getName();
	int getType1();
	int getType2();

};