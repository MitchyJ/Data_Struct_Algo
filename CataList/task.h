#ifndef _TASK_H_
#define _TASK_H_
//v0.2.1
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int INVALID = -1;

class Task{
private:
	int _startTime, _endTime;
	int _startDay, _startMonth, _startYear;
	int _endDay, _endMonth, _endYear;
	string _taskDescription, _status, _day;
	bool _deadline, _block;

public:
	void setTask(int, int, int, int, int, int, int, int, string, string, string, bool, bool);

	void setStartTime(int);
	void setEndTime(int);
	
	void setStartDay(int);
	void setEndDay(int);
	
	void setStartMonth(int);
	void setEndMonth(int);
	
	void setStartYear(int);
	void setEndYear(int);
	
	void setTaskDescription(string);
	void setStatus(string);
	void setDay(string);
	
	void setDeadline(bool);
	void setBlock(bool);

	int getStartTime();
	int getEndTime();

	int getStartDay();
	int getEndDay();

	int getStartMonth();
	int getEndMonth();

	int getStartYear();
	int getEndYear();

	string getTaskDescription();
	string getStatus();
	string getDay();

	bool getDeadline();
	bool getBlock();

	bool findKeyword(string);
	string textChangeLowercase(string);

	Task getTask();
};

#endif
