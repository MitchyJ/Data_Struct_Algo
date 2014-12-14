#include "storage.h"
//v0.2.1
const string Storage::PENDINGTXTFILE = "PendingTask.txt";
const string Storage::ARCHIVETXTFILE = "ArchivedTask.txt";
const string Storage::COMPLETEDTXTFILE = "CompletedTask.txt";

bool Storage::readFile(TaskList& storage)
{
	Task retrieveData;
	ifstream taskFile(PENDINGTXTFILE);

	if(!storage.checkEmpty())
		storage.clearList();

	if(taskFile.is_open()){
		while(!taskFile.eof())
		{
			getline(taskFile, _startTime);
			getline(taskFile, _endTime);
			getline(taskFile, _startDay);
			getline(taskFile, _endDay);
			getline(taskFile, _startMonth);
			getline(taskFile, _endMonth);
			getline(taskFile, _startYear);
			getline(taskFile, _endYear);
			getline(taskFile, _taskDescription);
			getline(taskFile, _status);
			getline(taskFile, _day);
			getline(taskFile, _deadline);
			getline(taskFile, _block);
			getline(taskFile, _emptyline);

			retrieveData.setTask(stoi(_startTime),stoi(_endTime), stoi(_startDay), stoi(_endDay), stoi(_startMonth), stoi(_endMonth), stoi(_startYear), stoi(_endYear), _taskDescription, _status, _day, stoi(_deadline), stoi(_block));

			storage.pushBack(retrieveData);
		}
		taskFile.close();
		return true;
	}
	else{
		return false;
		taskFile.close();
	}
}

bool Storage::addTaskToFile(Task newTask, int position)
{
	ofstream taskFile(PENDINGTXTFILE, ios::app);
	if(taskFile.is_open()){	
		if(position != ZERO)
			taskFile << endl;

		taskFile << newTask.getStartTime() << endl << newTask.getEndTime() << endl << newTask.getStartDay() << endl << newTask.getEndDay() << endl
			<< newTask.getStartMonth() << endl << newTask.getEndMonth() << endl <<newTask.getStartYear() << endl << newTask.getEndYear() << endl
			<< newTask.getTaskDescription() << endl  << newTask.getStatus() << endl << newTask.getDay() << endl << newTask.getDeadline() << endl
			<< newTask.getBlock() << endl;

		taskFile.close();
		return true;
	}
	else{
		taskFile.close();
		return false;
	}
}

bool Storage::updateFile(TaskList storage)
{
	ofstream taskFile(PENDINGTXTFILE);
	Task addTask;
	if(taskFile.is_open()){

		while(!storage.checkEmpty()){

			storage.getFrontTask(addTask);

			taskFile << addTask.getStartTime() << endl << addTask.getEndTime() << endl << addTask.getStartDay() << endl << addTask.getEndDay() << endl
				<< addTask.getStartMonth() << endl << addTask.getEndMonth() << endl <<addTask.getStartYear() << endl << addTask.getEndYear() << endl
				<< addTask.getTaskDescription() << endl  << addTask.getStatus() << endl << addTask.getDay() << endl << addTask.getDeadline() << endl
				<< addTask.getBlock() << endl;

			if(storage.getSize() != ONE)
				taskFile << endl;
			storage.removeFrontTask();
		}
		taskFile.close();
		return true;
	}
	else{
		taskFile.close();
		return false;
	}
}

bool Storage::completeTask(Task completedTask){
	ofstream taskFile(COMPLETEDTXTFILE, ios::app);
	if(taskFile.is_open()){
		taskFile << completedTask.getStartTime() << endl << completedTask.getEndTime() << endl << completedTask.getStartDay() << endl << completedTask.getEndDay() << endl
			<< completedTask.getStartMonth() << endl << completedTask.getEndMonth() << endl << completedTask.getStartYear() << endl << completedTask.getEndYear() << endl
			<< completedTask.getTaskDescription() << endl  << completedTask.getStatus() << endl << completedTask.getDay() << endl << completedTask.getDeadline() << endl
			<< completedTask.getBlock() << endl;
		taskFile.close();
		return true;
	}
	else{
		taskFile.close();
		return false;
	}
}

bool Storage::clearCompletedTask(){
	ofstream taskFile(COMPLETEDTXTFILE);
	if(taskFile.is_open()){
		taskFile.clear();
		taskFile.close();
		return true;
	}
	else{
		taskFile.close();
		return false;
	}
}

bool Storage::archiveTask(Task archivedTask){
	ofstream taskFile(ARCHIVETXTFILE, ios::app);
	if(taskFile.is_open()){
		taskFile << archivedTask.getStartTime() << endl << archivedTask.getEndTime() << endl << archivedTask.getStartDay() << endl << archivedTask.getEndDay() << endl
			<< archivedTask.getStartMonth() << endl << archivedTask.getEndMonth() << endl << archivedTask.getStartYear() << endl << archivedTask.getEndYear() << endl
			<< archivedTask.getTaskDescription() << endl  << archivedTask.getStatus() << endl << archivedTask.getDay() << endl << archivedTask.getDeadline() << endl
			<< archivedTask.getBlock() << endl;
		taskFile.close();
		return true;
	}
	else{
		taskFile.close();
		return false;
	}
}

bool Storage::clearArchivedTask(){
	ofstream taskFile(ARCHIVETXTFILE);
	if(taskFile.is_open()){
		taskFile.clear();
		taskFile.close();
		return true;
	}
	else{
		taskFile.close();
		return false;
	}
}
