#include "logic_done.h"
//v0.2.1
bool LogicDone::findDoneTask(TaskList& taskList, Task& task, string userInput, int& position){
	_search.searchTaskList(taskList, _searchResult, _tasksPosition, userInput);
	if(!_searchResult.getSize())
		return false;
	else if(_searchResult.getSize() == 1){
		taskList.removeTask(_tasksPosition.back(), task);
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
		position = _tasksPosition.at(choice - 1);
		taskList.removeTask(position, task);
	}
}

bool LogicDone::checkUserChoice(string choice){
	for(int i = 0; i < choice.length(); i++)
	{
		if(!isdigit(choice[i]))
			return false;
	}
	return true;
}
