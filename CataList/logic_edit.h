#ifndef _LOGIC_EDIT_H_
#define _LOGIC_EDIT_H_
//v0.2.1
#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include "ui.h"
#include "tasklist.h"
#include "logic_search.h"
#include "logic_detail_parser.h"
using namespace std;

class LogicEdit{
private:

	static const int POINTONE = 1;
	static const int POINTTWO = 2;
	static const int POINTTHREE = 3;
	static const int POINTFOUR = 4;

	static const int NOTSTATED = -1;
	static const int CHOICE = 1;

	static const string NOUPDATE;

	int _position;
	int _searchResultSize;

	string _oldTaskText;
	string _newTaskText;
	string _userInput;

	LogicDetailParser _parserInput;
	LogicSearch _search;
	UI _ui;

	TaskList _searchResult;
	vector<int> _taskPosition;

public:
	bool changeTaskInfo(TaskList&, Task&, Task&, string, string, int&, int&);
	string textChangeLowercase(string);
	void updateTask(Task&, Task&);
	bool checkUserChoice(string);
};
#endif
