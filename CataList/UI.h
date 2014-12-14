#ifndef _UI_H_
#define _UI_H_
//v0.2.1
#include <iostream>
#include <string>
#include <exception>
#include "task.h"
#include "tasklist.h"
using namespace std;

class UI{
private:
	string userChoice;
	string userInput;
	string command;
	string operation;


public:
	void main();
	string requestUserChoice();
	string requestInput();
	string getTaskDetails();
	string getInvalidInput();
	void welcomeMessage();
	void displayMessage(string);
	void successMessageForAdd();
	void errorMessageForAdd();
	void successMessageForDelete();
	void errorMessageForDelete();
	void successMessageForUpdate();
	void errorMessageForUpdate();
	void successMessageForUndo();
	void errorMessageForUndo();
	void successMessageForTaskSearch();
	void errorMessageForTaskSearch();
	void successMessageForExit();
	void successMessageForDisplay();
	bool displayTask(TaskList);
};

#endif
