#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
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

	string selectQuery(int whichQuery);

	void displayResults(int whichQuery);

public:
	SQL(int whichQuery);

};