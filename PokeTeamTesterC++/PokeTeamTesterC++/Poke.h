#pragma once
#include <string>
using namespace std;

// A basic Pokemon class which stores only the information needed by the GUI for each pokemon
class Poke {

private:
	int ID;
	//Image?
	string name;
	int type1;
	int type2;

public:
	Poke(int ID, string name, int type1, int type2);

	int getID();
	//Get Image?
	string getName();
	int getType1();
	int getType2();

};