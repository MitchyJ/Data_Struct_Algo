#ifndef _LOGIC_DATETIME_H_
#define _LOGIC_DATETIME_H_
//v0.2.1
#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include "task.h"
using namespace std;

class LogicDateTime{
private:
	static const int POINTZERO = 0;
	static const int POINTONE = 1;
	static const int POINTTWO = 2;
	static const int POINTTHREE = 3;
	static const int POINTFOUR = 4;
	static const int POINTFIVE = 5;
	static const int POINTSIX = 6;
	static const int POINTSEVEN = 7;
	static const int POINTEIGHT = 8;
	static const int POINTNINE = 9;
	static const int POINTTEN = 10;

	static const int TWELVEHOURS = 12;
	static const int MAXMINUTES = 60;
	static const int MAXHOURS = 24;
	static const int HUNDRED = 100;
	static const int TWOTHOUSAND = 2000;
	static const int MONTHCHECK = 12;
	static const int YEARCHECK = 100; // this value is allow to change as year changes

	static const int NOTSTATED = -1;

	static const int SPACECODE = 32;
	static const int DOTCODE = 46;
	static const int SLASHCODE = 47;
	static const int COLONCODE = 58;

	static const string CANNOTFIND;
	static const string HOURS;
	static const string AM;
	static const string PM;

	int _slashPosition;
	int _hrsPosition;
	int _dotPosition;
	int _colonPosition;
	int _amPosition;
	int _pmPosition;
	bool _checkTime;
	bool _hoursFlag;
	string _date;
	string _time;
	string _taskDescription;

public:
	bool parser(Task&, string, string);
	string textChangeLowercase(string);
	void getPosition(string);

	bool parserDate(Task&, string, int, int, int, bool&);
	void setTaskDate(Task&, int, int, int);
	bool findDate(string, int&, int&, int&);
	bool checkDate(int, int, int);
	void retrieveDate(int&, int&, int&);

	bool parserTime(Task&, string);
	bool getTime(string, string&, string&, int&, int&, int);
	bool parserHours(string, int&);
	bool findHoursTime(string, int&);
	bool parserSymbolledTime(string, int&);
	bool findMeridiemTime(string, string&, int&, int&);
	bool parserMeridiemTime(string, int&);
	bool findHoursMeridiemTime(string, string&, int&);
	bool checkTime(int);
	void setTaskTime(Task&, int, int);
	string trimFoundTime(string, string);

	void removeUnwantedText();

	void setDate(Task&);
	void findUserInput(Task&, string);
	
};
#endif