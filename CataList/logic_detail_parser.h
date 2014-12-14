#ifndef _LOGIC_DETAIL_PARSER_H_
#define _LOGIC_DETAIL_PARSER_H_

#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include "task.h"
using namespace std;

class LogicDetailParser{
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
	static const int POINTELEVEN = 11;
	static const int POINTTWELVE = 12;

	static const int SPACECODE = 32;
	static const int DOTCODE = 46;
	static const int SLASHCODE = 47;
	static const int COLONCODE = 58;

	static const int NOTSTATED = -1;

	static const int FOUND = 1;
	static const int NOTFOUND = 0;
	static const int ERROR = -1;

	static const int HUNDRED = 100;
	static const int FOURHUNDRED = 400;
	static const int TWOTHOUSAND = 2000;
	static const int YEARCHECK = 100;
	static const int MONTHCHECK = 12;
	static const int THREEONEDAYS = 31;
	static const int THREEZERODAYS = 30;
	static const int TWONINEDAYS = 29;
	static const int TWOEIGHTDAYS = 28;
	static const int FIXEDYEAR = 1900;

	static const int MAXMINUTES = 60;
	static const int MAXHOURS = 24;
	static const int TWELVEHOURS = 12;

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
	int _hoursFlag;

	string _date;
	string _time;
	string _taskDescription;
public:
	bool parser(Task&, string, string);
	string textChangeLowercase(string);
	void getIndicators(string);
	int findDate(Task&, string);
	bool parserDate(string, int&, int&, int&);
	bool checkDate(int, int, int);
	void retrieveDate(int&, int&, int&);
	void setTaskDate(Task&, int, int, int);
	string trimFoundText(string, string);
	int findTime(Task&, string);
	bool getTime(string&, string&, int&, int&);
	int getHoursTime(string, int&);
	bool parserHoursTime(string, int&);
	int getSymbolledTime(string, int&);
	bool parserSymbolledTime(string, string&, int&, int&);
	int getMeridiemTime(string, int&);
	bool parserMeridiemTime(string, string&, int&);
	bool checkTime(int);
	void setTaskTime(Task&, int, int);
	void removeUnwantedText();
	void setDate(Task&);
};
#endif