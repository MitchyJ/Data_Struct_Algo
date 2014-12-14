#ifndef _LOGIC_DELETE_H_
#define _LOGIC_DELETE_H_
//v0.2.1
#include <iostream>
#include "tasklist.h"
#include "logic_search.h"
#include "UI.h"
#include <vector>
using namespace std;

class LogicDelete{
private:
	static const int ZERO = 0;
	static const int ONE = 1;
	static const int OFFSET = 1;
	static const string CANCEL;

	UI _ui;
	LogicSearch _search;

public:
	//bool delTask(TaskList&,Task&,string,int&);
	int delTask(TaskList&,Task&,string,int&,vector<int>&,TaskList&);
	void deleteAddedTask(TaskList&, Task, int);
	bool checkUserChoice(string);
	void deleteAtPos(TaskList&, Task&, int);
};
#endif
