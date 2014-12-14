#include "task.h"
//v0.2.1
void Task::setTask(int startTime, int endTime, int startDay, int endDay, int startMonth, int endMonth, int startYear, int endYear, string taskDescription, string status, string day, bool deadline, bool block){
	_startTime = startTime;
	_endTime = endTime;
	_startDay = startDay;
	_endDay = endDay;
	_startMonth = startMonth;
	_endMonth = endMonth;
	_startYear = startYear;
	_endYear = endYear;
	_taskDescription = taskDescription;
	_status = status;
	_day = day;
	_deadline = deadline;
	_block = block;
}

void Task::setStartTime(int startTime){
	_startTime = startTime;
}

void Task::setEndTime(int endTime){
	_endTime = endTime;
}

void Task::setStartDay(int startDay){
	_startDay = startDay;
}

void Task::setEndDay(int endDay){
	_endDay = endDay;
}

void Task::setStartMonth(int startMonth){
	_startMonth = startMonth;
}

void Task::setEndMonth(int endMonth){
	_endMonth = endMonth;
}

void Task::setStartYear(int startYear){
	_startYear = startYear;
}

void Task::setEndYear(int endYear){
	_endYear = endYear;
}

void Task::setTaskDescription(string taskDescription){
	_taskDescription = taskDescription;
}

void Task::setStatus(string status){
	_status = status;
}

void Task::setDay(string day){
	_day = day;
}

void Task::setDeadline(bool deadline){
	_deadline = deadline;
}

void Task::setBlock(bool block){
	_block = block;
}

int Task::getStartTime(){
	return _startTime;
}

int Task::getEndTime(){
	return _endTime;
}

int Task::getStartDay(){
	return _startDay;
}

int Task::getEndDay(){
	return _endDay;
}

int Task::getStartMonth(){
	return _startMonth;
}

int Task::getEndMonth(){
	return _endMonth;
}

int Task::getStartYear(){
	return _startYear;
}

int Task::getEndYear(){
	return _endYear;
}

string Task::getTaskDescription(){
	return _taskDescription;
}

string Task::getStatus(){
	return _status;
}

string Task::getDay(){
	return _day;
}

bool Task::getDeadline(){
	return _deadline;
}

bool Task::getBlock(){
	return _block;
}

bool Task::findKeyword(string keyword){
	string taskDescription = _taskDescription;
	taskDescription = textChangeLowercase(taskDescription);

	if(taskDescription.find(keyword) == INVALID)
		return false;
	else
		return true;
}

string Task::textChangeLowercase(string text){
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

Task Task::getTask(){
	Task requestedTask;

	requestedTask.setTask(getStartTime(),getEndTime(),getStartDay(),getEndDay(),
		getStartMonth(),getEndMonth(),getStartYear(),getEndYear(),
		getTaskDescription(),getStatus(),getDay(),getDeadline(),getBlock());
	
	return requestedTask;
}