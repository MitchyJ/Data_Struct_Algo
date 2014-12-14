#include "logic_edit.h"
//v0.2.1
const string LogicEdit::NOUPDATE = "NOTSTATED";

bool LogicEdit::changeTaskInfo(TaskList& taskList, Task& newTaskInfo, Task& oldTaskInfo, string userInput, string operation, int& oldPosition, int& newPosition){
	_searchResult.clearList();
	_taskPosition.clear();

	_position = userInput.find(" - ");
	if(_position < POINTTHREE)
		return false;
	else if(_position == (_userInput.size() - POINTTWO) || (_position + POINTFOUR) >= userInput.size())
		return false;

	newTaskInfo.setTask(NOTSTATED, NOTSTATED, NOTSTATED, NOTSTATED, NOTSTATED, NOTSTATED, NOTSTATED, NOTSTATED, NOUPDATE, NOUPDATE, NOUPDATE, false, false);

	_userInput = textChangeLowercase(userInput);
	_oldTaskText = _userInput.substr(POINTONE, _position - POINTONE);
	_newTaskText = userInput.substr((_position + POINTTHREE), (_userInput.size() - (_position + POINTTHREE)));

	_search.searchTaskList(taskList, _searchResult, _taskPosition, _oldTaskText);
	_searchResultSize = _searchResult.getSize();

	if(!_searchResultSize)
		return false;

	if(!_parserInput.parser(newTaskInfo, _newTaskText, operation))
			return false;

	if(_searchResultSize == POINTONE){
		oldPosition = _taskPosition.back();
		taskList.removeTask(oldPosition, oldTaskInfo);
		updateTask(oldTaskInfo, newTaskInfo);	// proper of position checking is needed
		taskList.findInsertPosition(newTaskInfo,newPosition);
		taskList.insertTaskToPosition(newTaskInfo, newPosition);
	}

	else{
		string userChoice;
		int choice;
		_ui.displayTask(_searchResult);

		do{
			userChoice = _ui.requestUserChoice();	
			if(userChoice == "cancel")	
				return false;
		}while(!checkUserChoice(userChoice));

		choice = stoi(userChoice) - CHOICE;
		oldPosition = _taskPosition.at(choice);
		taskList.removeTask(oldPosition, oldTaskInfo);
		updateTask(oldTaskInfo, newTaskInfo);	// proper of position checking is needed
		taskList.findInsertPosition(newTaskInfo,newPosition);
		taskList.insertTaskToPosition(newTaskInfo, newPosition);
	}

	return true;
}

string LogicEdit::textChangeLowercase(string text){
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

void LogicEdit::updateTask(Task& oldInfo, Task& newTask){

	if(newTask.getStartTime() == NOTSTATED)
		newTask.setStartTime(oldInfo.getStartTime());

	if(newTask.getEndTime() == NOTSTATED)
		newTask.setEndTime(oldInfo.getEndTime());

	if(newTask.getStartDay() == NOTSTATED)
		newTask.setStartDay(oldInfo.getStartDay());

	if(newTask.getEndDay() == NOTSTATED)
		newTask.setEndDay(oldInfo.getEndDay() );

	if(newTask.getStartMonth() == NOTSTATED)
		newTask.setStartMonth(oldInfo.getStartMonth());

	if(newTask.getEndMonth() == NOTSTATED)
		newTask.setEndMonth(oldInfo.getEndMonth());

	if(newTask.getStartYear() == NOTSTATED)
		newTask.setStartYear(oldInfo.getStartYear());

	if(newTask.getEndYear() == NOTSTATED)
		newTask.setEndYear(oldInfo.getEndYear());

	if(newTask.getDay() == NOUPDATE)
		newTask.setDay(oldInfo.getDay());

	if(newTask.getTaskDescription() == NOUPDATE)
		newTask.setTaskDescription(oldInfo.getTaskDescription());

	newTask.setStatus(oldInfo.getStatus());
	newTask.setBlock(oldInfo.getBlock());
	newTask.setDeadline(oldInfo.getDeadline());
}

bool LogicEdit::checkUserChoice(string choice){
	for(int i = 0; i < choice.length(); i++)
	{
		if(!isdigit(choice[i]))
			return false;
	}
	return true;
}
