#include <ctime>
#include <iostream>
#include "CppSQLite.h"
using namespace std;
const char* gszFile = "C:\\test.db";

int main(int argc, char** argv) {
	try {
		int i, fld;
		time_t tmStart, tmEnd;
		CppSQLiteDB db;

		cout << "SQLite Version: " << db.SQLiteVersion() << endl;

		db.open(gszFile);
		cout << db.execScalar("select count(*) from emp;")
		     << " rows in emp table in ";
		db.Close();
	} catch (CppSQLiteException& e) {
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}
}
