#include "tasklist.h"
//v0.2.1

bool TaskList::checkEmpty(){
	return _taskList.empty();
}

void TaskList::clearList(){
	_taskList.clear();
}

void TaskList::pushBack(Task task){
	_taskList.push_back(task);
}

void TaskList::getFrontTask(Task& task){
	task = _taskList.front();
}

void TaskList::removeFrontTask(){
	_taskList.pop_front();
}

int TaskList::getSize(){
	return _taskList.size();
}

void TaskList::removeTask(int taskPosition,Task& deletedTask){
	list<Task>::iterator it; 
	it = _taskList.begin();
	advance (it, taskPosition);
	deletedTask = it->getTask();
	it = _taskList.erase(it);
}

void TaskList::removeTask(int taskPosition){
	list<Task>::iterator it; 
	it = _taskList.begin();
	advance (it, taskPosition);
	it = _taskList.erase(it);
}

void TaskList::insertTaskToPosition(Task task, int position){
	if (position == ZERO)
		_taskList.push_back(task);
	else{
		list<Task>::iterator it;
		it = _taskList.begin();
		advance(it, position);
		_taskList.insert(it, task);
	}
}

void TaskList::findInsertPosition(Task task, int& position){ 
	position = ZERO;

	if(_taskList.size() == ZERO)
		return;
	else
		compareDate(task,position);
}

void TaskList::compareDate(Task task, int& position){
	int taskStartYear = task.getStartYear();
	int listIndexStartYear;
	list<Task>::iterator it;

	for(it = _taskList.begin();it!=_taskList.end();it++){
		listIndexStartYear = it->getStartYear();

		if(taskStartYear > listIndexStartYear){
			position++;
		}
		else if (taskStartYear == listIndexStartYear){
			compareMonth(task, position, taskStartYear);
			break;
		}
		else
			break;

	}
}

void TaskList::compareMonth(Task task, int& position, int taskStartYear){
	int taskStartMonth = task.getStartMonth();
	int listIndexStartMonth;
	int listIndexStartYear;
	list<Task>::iterator it = _taskList.begin();

	for(advance(it,position);it!=_taskList.end();it++){
		listIndexStartMonth = it->getStartMonth();
		listIndexStartYear = it->getStartYear();

		if((taskStartMonth > listIndexStartMonth) && (taskStartYear == listIndexStartYear))
			position++;
		else if (taskStartMonth == listIndexStartMonth){
			compareDay(task, position, taskStartMonth);
			break;
		}
		else 
			break;
	}
}

void TaskList::compareDay(Task task, int& position, int taskStartMonth){
	int taskStartDay = task.getStartDay();
	int listIndexStartDay;
	int listIndexStartMonth;
	list<Task>::iterator it = _taskList.begin();

	for(advance(it,position);it!=_taskList.end();it++){
		listIndexStartDay = it->getStartDay();
		listIndexStartMonth = it->getStartMonth();

		if((taskStartDay > listIndexStartDay) && (taskStartMonth == listIndexStartMonth))
			position++;
		else if (taskStartDay == listIndexStartDay){
			compareTime(task, position, taskStartDay);
			break;
		}
		else
			break;
	}
}

void TaskList::compareTime(Task task, int& position, int taskStartDay){
	int taskStartTime = task.getStartTime();

	list<Task>::iterator it = _taskList.begin();

	for(advance(it,position);it!=_taskList.end();it++){
		if( (taskStartTime > it->getStartTime()) && (it->getStartDay() == taskStartDay) ){
			position++;
		}
		else
			break;
	}
}

Task TaskList::getAtPosition(int taskPosition){
	list<Task>::iterator it; 
	it = _taskList.begin();
	advance (it, taskPosition);
	return it->getTask();
}

