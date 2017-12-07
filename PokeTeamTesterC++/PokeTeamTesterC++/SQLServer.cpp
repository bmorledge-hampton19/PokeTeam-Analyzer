#include "SQLServer.h"
#include <string>
#include <iostream>


Poke SQL::readIntoPoke()
{
	int pokeInfo[9];
	string pokeName;

	for (int i = 0; i < 9; i++) {

		SQLGetData(hstmt, i+1, SQL_C_CHAR, szData, sizeof(szData), &cbData);
		if (i == 1) {
			pokeName = szData;
		}
		else pokeInfo[i] = stoi(szData);
	}

	Poke poke(pokeInfo[0], pokeName, pokeInfo[2], pokeInfo[3], pokeInfo[4], pokeInfo[5], pokeInfo[6], pokeInfo[7], pokeInfo[8]);

	return poke;
}

SQL::SQL()
{

	SQLAllocEnv(&henv);
	SQLAllocConnect(henv, &hdbc);

	string stConnect = "Driver={SQL Server};Server=CS1;";
	stConnect += "Database=PokeTeam;Trusted_Connection=yes;";

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

Poke * SQL::getBestAttackers(int ID)
{
	Poke* poke;
	poke = new Poke[10];

	string stSQLTemp = "";
	stSQLTemp += "SELECT Temp.ID, PC.Name, Temp.HP, Temp.Attack, Temp.Defense, Temp.Speed, Temp.Special, Temp.Type1, Temp.Type2, Temp.Mul, Temp.SumStats ";
	stSQLTemp += "FROM( ";
	stSQLTemp += "SELECT PS.*, GTM.Mul, (PS.HP + PS.Attack + PS.Defense + PS.Speed + PS.Special) AS SumStats, ROW_NUMBER() over(partition by PS.Type1, PS.Type2 ORDER BY(PS.HP + PS.Attack + PS.Defense + PS.Speed + PS.Special) DESC) as rn ";
	stSQLTemp += "FROM PokemonStats PS, [dbo].[goodTypesInto](" + to_string(ID);
	stSQLTemp += ") AS GTM ";
	stSQLTemp += "WHERE PS.Type1 = GTM.A1 AND PS.Type2 = GTM.A2 ";
	stSQLTemp += ") AS Temp INNER JOIN PokeCharacteristics AS PC ON PC.ID = Temp.ID ";
	stSQLTemp += "WHERE Temp.rn = 1 ";
	stSQLTemp += "ORDER BY Mul DESC, Temp.SumStats DESC";

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

	while (rc == SQL_SUCCESS && results < 10) {
		rc = SQLFetch(hstmt);

		poke[results] = readIntoPoke();

		results++;
	}

	return poke;
}

Poke SQL::getPoke(int ID)
{
	int pokeInfo[9];
	string pokeName = "";

	string stSQLTemp = "";
	stSQLTemp += "SELECT PS.*, PC.Name\n";
	stSQLTemp += "FROM PokemonStats AS PS INNER JOIN PokeCharacteristics AS PC ON PC.ID = PS.ID \n";
	stSQLTemp += "WHERE PS.ID = " + to_string(ID);

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

	rc = SQLFetch(hstmt);

	for (int i = 0; i < 9; i++) {

		SQLGetData(hstmt, i + 1, SQL_C_CHAR, szData, sizeof(szData), &cbData);
		if (i == 8) pokeName = szData;
		else pokeInfo[i] = stoi(szData);
	}

	Poke poke(pokeInfo[0], pokeName, pokeInfo[1], pokeInfo[2], pokeInfo[3], pokeInfo[4], pokeInfo[5], pokeInfo[6], pokeInfo[7]);

	return poke;
}

double SQL::getMul(int ID, Poke thing)
{

	string stSQLTemp = "SELECT DISTINCT Mul FROM[Matchups](" + to_string(ID) + ") WHERE D1 = "  + to_string(thing.getType1()) +  " AND D2 = " + to_string(thing.getType2());

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

	SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData);
	return atof(szData);
}

int SQL::getID(string pokeName)
{
	string stSQLTemp = "";
	stSQLTemp += "SELECT PC.*\n";
	stSQLTemp += "FROM PokeCharacteristics AS PC\n";
	stSQLTemp += "WHERE PC.Name LIKE '%" + pokeName + "%'\n";

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

	if (rc == SQL_SUCCESS) {
		rc = SQLFetch(hstmt);
		SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData);
		string pokeID = szData;
		if (pokeID.length() > 4) return 0;
		return stoi(pokeID);
	}

	cout << "No pokemon found with " << pokeName << " in their name." << endl;
	return 0;

}
