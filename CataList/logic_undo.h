#ifndef _LOGIC_UNDO_H_
#define _LOGIC_UNDO_H_
//v0.2.1
#include <iostream>
#include <string>
#include <stack>
#include "task.h"
using namespace std;

class LogicUndo{
private:
	
	stack<Task> _changes;
	stack<string> _operation;
	stack<int> _position;
	
public:
	void addToList(Task taskInfo, string operation, int position);
	bool getLatestInfo(Task&, string&, int&);
	void removeLastInfo();
	void clearList();
};
#endif
