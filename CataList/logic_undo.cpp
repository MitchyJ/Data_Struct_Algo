#include "logic_undo.h"
//v0.2.1
void LogicUndo::addToList(Task taskInfo, string operation, int position){
	_changes.push(taskInfo);
	_operation.push(operation);
	_position.push(position);
}

bool LogicUndo::getLatestInfo(Task& task, string& operation, int& position){
	if(_operation.size()){
		task = _changes.top();
		operation = _operation.top();
		position = _position.top();

		removeLastInfo(); 
		return true;
	}
	else
		return false;
}

void LogicUndo::removeLastInfo(){
	_changes.pop();
	_operation.pop();
	_position.pop();
}

void LogicUndo::clearList(){
	while(!_changes.empty())
		removeLastInfo();
}