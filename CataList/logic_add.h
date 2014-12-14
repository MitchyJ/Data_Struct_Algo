#ifndef _LOGIC_ADD_H_
#define _LOGIC_ADD_H_
//v0.2.1
#include <iostream>
#include "tasklist.h"
#include "logic_undo.h"
#include "logic_detail_parser.h"
#include <ctime>
#include <algorithm>

using namespace std;

class LogicAdd{
private:
	static const int ONE = 1;
	static const int NOTFOUND = -1;
	static const string MORNING;
	static const string AFTERNOON;
	static const string HRS;
	static const string NOUPDATE;
	static const string CANNOTFIND;
	static const string OPERATION;

	Task _newTask;
	TaskList _taskList;
	LogicDetailParser _detail;

public:
	bool newTaskParser(TaskList&, Task&, string, int&);
	void addToList(TaskList&, Task&, int&);
	void trimUserInput(string&);
	void initialiseTask(Task&);
	void addDeletedTask(TaskList&, Task, int);
	bool checkDateTimeValidity(int, int, int, int, int, int, int, int);
	//DID YOU ADD LOGICADD?!?!?!?!?!?!
};
#endif

////bool findDate(string, int&, int&, int&);
////bool findHoursTime(string, int&);
////bool findHoursMeridiemTime(string, string&, int&);
////bool findMeridiemTime(string, string&, int&, int&);
////bool checkDate(int, int, int);
////bool checkTime(int);
////void findUserInput(Task&, string);
////void retrieveDate(int&, int&, int&);
////string convertLowercase(string);
//
////void setDate();
////void retrieveDateTime(int&, int&, int&, int&, int&, string&);
////int _slashPosition;
////int _dotPosition;
////int _colonPosition;
////int _amPosition;
////int _pmPosition;
////int _hrsPosition;
//
////string _userInput;
////string _date;
////string _time;
//
////static const int TWO = 2;
////static const int THREE = 3;
////static const int FOUR = 4;
////static const int FIVE = 5;
////static const int SIX = 6;
////static const int SEVEN = 7;
////static const int EIGHT = 8;
////static const int NINE = 9;
////static const int TEN = 10;
//
////static const int MONTHCHECK = 12;
////static const int DAYCHECK = 31;
//
////static const int HUNDRED = 100;
////static const int TWELVEHOURS = 12;
////static const int MAXMINUTES = 60;
////static const int MAXHOURS = 24;
//
////static const int DATESLASH = 47;
////static const int DOT = 46;
////static const int COLON = 58;
////static const int SPACE = 32;
////static const int FIRSTPOSITION = 1;
//
////static const int YEARCHECK = 100;
////static const int STARTYEAR = 1900;
////static const int TWOTHOUSAND = 2000;
////static const int ZERO = 0;