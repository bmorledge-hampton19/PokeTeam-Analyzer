#include "SQLServer.h"

string SQL::selectQuery(int whichQuery)
{

	string stSQLTemp = "";

	if (whichQuery == 6) {
		stSQLTemp = "select distinct CompanyName ";
		stSQLTemp += "from Shippers join Orders on ShipVia = ShipperID ";
		stSQLTemp += "where Freight > 100";
	}
	else if (whichQuery == 7) {
		stSQLTemp = "select (FirstName + ' ' + LastName) as EmployeeName, Title ";
		stSQLTemp += "from Employees";
	}
	else if (whichQuery == 9) {
		stSQLTemp = "select MAX(UnitPrice) as MaximumPrice, MIN(UnitPrice) as MinPrice, AVG(UnitPrice) ";
		stSQLTemp += "as AveragePrice ";
		stSQLTemp += "from Products";
	}
	else if (whichQuery == 10) {
		stSQLTemp = "select C.CategoryName, MAX(UnitPrice) as MaximumPrice, MIN(UnitPrice) as MinPrice, ";
		stSQLTemp += "AVG(UnitPrice) as AveragePrice ";
		stSQLTemp += "from Products P join Categories C on P.CategoryID = C.CategoryID ";
		stSQLTemp += "group by C.CategoryID, C.CategoryName";
	}

	return stSQLTemp;
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

SQL::SQL(int whichQuery)
{
	this->whichQuery = whichQuery;

	SQLAllocEnv(&henv);
	SQLAllocConnect(henv, &hdbc);

	string stConnect = "Driver={SQL Server};Server=CS1;";
	stConnect += "Database=Northwind;Trusted_Connection=yes;";
	stSQL = selectQuery(whichQuery);

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
	SQLAllocStmt(hdbc, &hstmt);
	cout << stSQL << endl << endl;
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

	displayResults(whichQuery);




	SQLFreeStmt(hstmt, SQL_DROP);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);
}
