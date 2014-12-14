#include "logic_delete.h"
//v0.2.1
const string LogicDelete::CANCEL = "cancel" ;

int LogicDelete::delTask(TaskList& taskList,Task& deletedTask,string userInput,int& position,vector<int>& positionOfTask,TaskList& searchResult){
	if(_search.searchTaskList(taskList,searchResult,positionOfTask,userInput)){
		
		if(searchResult.getSize()==1){
			position =positionOfTask.at(ZERO);
			taskList.removeTask(positionOfTask.at(ZERO),deletedTask);
			return 0;
		}
		else{
			return 1;
		}
	}
	else
		return -1;
}	

void LogicDelete::deleteAddedTask(TaskList& taskList, Task deleteTask, int position){
	taskList.removeTask(position);
}

bool LogicDelete::checkUserChoice(string choice)
{
	for(int i=0;i<choice.length();i++)
	{
		if(!isdigit(choice[i]))
			return false;
	}
	return true;
}

void LogicDelete::deleteAtPos(TaskList& taskList,Task& deletedTask,int pos){
	taskList.removeTask(pos,deletedTask);
}