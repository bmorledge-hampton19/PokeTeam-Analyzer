#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <vector>
#include <string>
#include "Poke.h"
using namespace std;

class SQL {

private:

	// Variables needed for Query engine
	RETCODE rc;
	HENV henv;
	HDBC hdbc;
	HSTMT hstmt;
	char szData[100];
	string stSQL;
	SQLLEN cbData;
	int whichQuery;
	SQLCHAR szConnectOut[1024];
	SQLSMALLINT cchConnect;

	Poke readIntoPoke(); // Creates a pokemon object given data from a query

public:

	SQL(); // Initializes the query engine

	~SQL(); // Frees up resources for the query engine

	vector<Poke>getBestAttackers(int ID); // gets up to ten best attackers against a given pokemon

	Poke getPoke(int ID); //gets pokemon by id name

	double getMul(int ID, Poke thing); //gets multiplier between 1 attacking pokemon (as integer "ID") and 1 defending pokemon (as object "thing")

	int getID(string &pokeName); //gets pokemon id from name, or part of name

};