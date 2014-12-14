#ifndef _LOGIC_SEARCH_H_
#define _LOGIC_SEARCH_H_
//v0.2.1
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "taskList.h"
#include "task.h"
using namespace std;

class LogicSearch{
private:
	static const int EMPTY = 0;
	static const int ONE = 1;
	static const int OFFSET = 1;
	static const string DOUBLESPACE;
	static const string SINGLESPACE;
	static const string SPACE;

	Task _task;
public:
	bool searchTaskList(TaskList, TaskList&, vector<int>&, string);
	void checkKeyword(string&);
	string convertLowercase(string);
};
#endif
