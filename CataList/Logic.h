#ifndef _LOGIC_H_
#define _LOGIC_H_
//v0.2.1
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cctype>
#include <ctype.h>
#include <exception>

#include "logic_search.h"
#include "logic_delete.h"
#include "logic_done.h"
#include "logic_edit.h"
#include "logic_undo.h"
#include "logic_redo.h"
#include "logic_add.h"
#include "tasklist.h"
#include "storage.h"
#include "task.h"
#include "ui.h"

#include "assert.h"
#include "log.h"

using namespace std;

class Logic{
private:
	static const char ADDSIGN = '+';
	static const char DELSIGN = '-';
	static const int STARTPOSITION = 0;
	static const string STARTPROGRAM;
	static const string LOGTASK;
	static const string ADD;
	static const string DELETE;
	static const string EDIT;
	static const string DONE;
	static const string SEARCH;
	static const string DISPLAY;
	static const string UNDO;
	static const string REDO;
	static const string EXIT;
	static const string UPDATE;
	static const string SHOW;
	static const string FIND;
	static const string COMPLETE;

	TaskList _taskList;
	Task _task;
	Storage _fileStorage;
	LogicSearch _search;
	LogicDelete _delete;
	LogicDone _done;
	LogicEdit _edit;
	LogicUndo _undo;
	LogicRedo _redo;
	LogicAdd _add;

	UI _io;

	Assert _assertion;
	Log _log;

	string _operation;
	string _userInput;
	int _position;

public:
	bool undoParser();
	bool redoParser();
	bool addTask(string);
	bool updateTask(string);
	int deleteTask(string,vector<int>&,TaskList&);
	void deleteAtPos(int);
	bool editTask(string);
	bool searchTask(string,TaskList&);
	bool displayTask(TaskList&);
	bool userCommand(string&);
	bool statusUpdate(string);
	void init();
	string convertLowercase(string);
};
#endif
