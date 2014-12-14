#ifndef _LOG_H_
#define _LOG_H_
//v0.2.1
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class Log{
private:
	static const string LOGFILE;
	static const string SUCCESS;
	static const string FAIL;
	static const string SPACE;
	static const string COLON;
	static const int ZERO = 0;
	static const int ONE = 1;
	static const int YEAROFFSET = 1900;

	int _year;
	int _month;
	int _date;
	int _hour;
	int _minute;
	void getDateAndTime(int&, int&, int&, int&, int&);

public:
	void printTaskToLog(string, string, bool);
};
#endif
