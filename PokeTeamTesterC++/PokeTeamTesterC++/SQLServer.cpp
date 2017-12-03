#include "SQLServer.h"

Poke* SQL::getBestAttackers(int ID)
{

	Poke* poke[10];

	string stSQLTemp = "";
	stSQLTemp = "SELECT PS.*, GTM.Mul\n";
	stSQLTemp += "FROM PokemonStats PS, [dbo].[goodTypesInto](" + ID;
	stSQLTemp += ") AS GTM\n";
	stSQLTemp += "WHERE PS.Type1 = GTM.A1 AND PS.Type2 = GTM.A2\n";
	stSQLTemp += "ORDER BY Mul DESC, (PS.HP + PS.Attack + PS.Defense + PS.Speed + PS.Special) DESC";

	stSQL = stSQLTemp;
	
	SQLAllocStmt(hdbc, &hstmt);
	rc = SQLExecDirect(hstmt, (SQLCHAR*)stSQL.c_str(), SQL_NTS);
	if (!(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR state[255], error[255];
		SQLINTEGER code;
		SQLSMALLINT cb;
		SQLError(henv, hdbc, hstmt, state, &code, error, 255, &cb);
		cout << error << endl;
		exit(0);
	}

	int results = 0;

	while (rc == SQL_SUCCESS && results < 5) {
		rc = SQLFetch(hstmt);

		poke[results] = new readIntoPoke();

		results++;

		


}

void SQL::displayResults(int whichQuery)
{
	int results = 0;
	
	while (rc == SQL_SUCCESS && results < 5) {
		rc = SQLFetch(hstmt);

		results++;

		if (whichQuery == 6) {

			if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << "'" << szData << "'" << " ships orders with fees > 100." << endl;

		}
		else if (whichQuery == 7) {

			if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << "'" << szData << "'" << " has the title '";
			if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << szData << "'." << endl;

		}
		else if (whichQuery == 9) {

			if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << "Across all products:" << endl << "The maximum unit price is $" << szData << "." << endl;
			if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << "The minimum unit price is $" << szData << "." << endl;
			if (SQLGetData(hstmt, 3, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << "The average unit price is $" << szData << "." << endl;
			cout << endl;

		}
		else if (whichQuery == 10) {

			if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << "Among " << szData << ":" << endl;
			if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << "The maximum unit price is $" << szData << "." << endl;
			if (SQLGetData(hstmt, 3, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << "The minimum unit price is $" << szData << "." << endl;
			if (SQLGetData(hstmt, 4, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
				cout << "The average unit price is $" << szData << "." << endl;
			cout << endl;

		}

	}

	cout << endl;
}

Poke SQL::readIntoPoke()
{



	return;
}

SQL::SQL()
{

	SQLAllocEnv(&henv);
	SQLAllocConnect(henv, &hdbc);

	string stConnect = "Driver={SQL Server};Server=CS1;";
	stConnect += "Database=Northwind;Trusted_Connection=yes;";

	rc = SQLDriverConnect(hdbc, NULL, (SQLCHAR *)stConnect.c_str(), stConnect.length(), szConnectOut, 1024, &cchConnect, SQL_DRIVER_NOPROMPT);
	if (!(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR state[255], error[255];
		SQLINTEGER code;
		SQLSMALLINT cb;
		SQLError(henv, hdbc, NULL, state, &code, error, 255, &cb);
		cout << error << endl;
		exit(0);
	}
	
}

SQL::~SQL()
{

	SQLFreeStmt(hstmt, SQL_DROP);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);

}
