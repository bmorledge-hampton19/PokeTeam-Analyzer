
#include <string>
#include <iostream>
#include "SQLServer.h"//handles interaction with Database
#include "Poke.h" //handles pokemon objects
#include <vector>
#include <algorithm>

//gets pokemon id from name
int getPokeID(string name);
//gets pokemon object from id
Poke getPokeObject(int ID);
//does all team calculations to find best attacking team
void teamCalculations(int team[6]);