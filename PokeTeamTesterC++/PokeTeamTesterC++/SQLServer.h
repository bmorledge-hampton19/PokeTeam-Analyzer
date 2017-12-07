#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
#include "Poke.h"
using namespace std;

class SQL {

private:
	RETCODE rc;
	HENV henv;
	HDBC hdbc;
	HSTMT hstmt;
	// Each data entry can have a maximum of 100 characters.
	char szData[100];
	string stSQL;
	SQLLEN cbData;
	int whichQuery;

	SQLCHAR szConnectOut[1024];
	SQLSMALLINT cchConnect;

	Poke readIntoPoke();

public:
	SQL();

	~SQL();

	Poke* getBestAttackers(int ID);
	Poke getPoke(int ID);

	int getID(string pokeName);

};