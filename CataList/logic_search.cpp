#include "logic_search.h"
//v0.2.1
const string LogicSearch::DOUBLESPACE = "  ";
const string LogicSearch::SINGLESPACE = " ";
const string LogicSearch::SPACE = "";

bool LogicSearch::searchTaskList(TaskList taskList, TaskList& searchResult, vector<int>& taskFoundPosition, string keyword){
	if(keyword == DOUBLESPACE || keyword == SINGLESPACE || keyword == SPACE)
		return false;

	checkKeyword(keyword);

	keyword = convertLowercase(keyword);

	for(int i = 0; !taskList.checkEmpty(); i++){
		taskList.getFrontTask(_task);
		if(_task.findKeyword(keyword)){
			searchResult.pushBack(_task);
			taskFoundPosition.push_back(i);
		}
		taskList.removeFrontTask();
	}
	if(searchResult.getSize() == EMPTY)
		return false;
	else
		return true;
}

void LogicSearch::checkKeyword(string& keyword){
	keyword = keyword.substr(ONE, keyword.size() - OFFSET);
}

string LogicSearch::convertLowercase(string text){
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}