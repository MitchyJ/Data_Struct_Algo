#ifndef _STORAGE_H_
#define _STORAGE_H_
//v0.2.1
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "taskList.h"
#include "task.h"
using namespace std;

class Storage{
private:
	static const int ZERO = 0;
	static const int ONE = 1;
	static const string PENDINGTXTFILE;
	static const string ARCHIVETXTFILE;
	static const string COMPLETEDTXTFILE;

	string _startTime, _endTime;
	string _startDay, _endDay;
	string _startMonth, _endMonth;

	string _startYear, _endYear;
	string _taskDescription, _status, _day;
	string _deadline, _block;
	string _emptyline;

	Task _task;

public:
	bool readFile(TaskList&);
	bool addTaskToFile(Task, int);
	bool updateFile(TaskList);
	bool completeTask(Task);
	bool clearCompletedTask();
	bool archiveTask(Task);
	bool clearArchivedTask();
};
#endif
