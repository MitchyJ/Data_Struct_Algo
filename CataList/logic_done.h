#ifndef _LOGIC_DONE_H_
#define _LOGIC_DONE_H_
//v0.2.1
#include <iostream>
#include <vector>
#include "ui.h"
#include "tasklist.h"
#include "logic_search.h"
using namespace std;

class LogicDone{
private:
	TaskList _searchResult;
	vector<int> _tasksPosition;

	LogicSearch _search;
	UI _ui;

public:
	bool findDoneTask(TaskList&, Task&, string, int&);
	bool checkUserChoice(string);
};
#endif
