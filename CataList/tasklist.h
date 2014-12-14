#ifndef _TASKLIST_H_
#define _TASKLIST_H_
//v0.2.1
#include <iostream>
#include <list>
#include "task.h"
using namespace std;

class TaskList{
private:
	static const int ZERO = 0;
	list<Task> _taskList;
public:
	int getSize();
	bool checkEmpty();
	void clearList();
	void pushBack(Task);
	void getFrontTask(Task&);
	void removeFrontTask();
	void removeTask(int,Task&);
	void removeTask(int);
	void insertTaskToPosition(Task, int);
	void findInsertPosition(Task, int&);
	void compareDate(Task, int&);
	void compareMonth(Task, int&, int);
	void compareDay(Task, int&, int);
	void compareTime(Task, int&, int);
	Task getAtPosition(int);
};

#endif
