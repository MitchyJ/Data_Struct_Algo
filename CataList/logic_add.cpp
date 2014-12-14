#include "logic_add.h"
//v0.2.1
const string LogicAdd::HRS = "hrs";
const string LogicAdd::MORNING = "am";
const string LogicAdd::AFTERNOON = "pm";
const string LogicAdd::NOUPDATE = "No Update";
const string LogicAdd::CANNOTFIND = "CaNNoTFinD";
const string LogicAdd::OPERATION = "add";

bool LogicAdd::newTaskParser(TaskList& taskList, Task& newTask, string userInput, int& position){
	trimUserInput(userInput);
	initialiseTask(newTask);

	bool found = _detail.parser(newTask,userInput,"add");

	if(newTask.getTaskDescription() == NOUPDATE)
		return false;
	if(!checkDateTimeValidity(newTask.getStartYear(),newTask.getStartMonth(),newTask.getStartDay(),newTask.getEndYear(),newTask.getEndMonth(),newTask.getEndDay(),newTask.getStartTime(),newTask.getEndTime())){
		//cout<<newTask.getStartYear()<<endl;
		//cout<<newTask.getStartMonth()<<endl;
		//cout<<newTask.getStartDay()<<endl;
		//cout<<newTask.getEndYear()<<endl;
		//cout<<newTask.getEndMonth()<<endl;
		//cout<<newTask.getEndDay()<<endl;
		//cout<<newTask.getStartTime()<<endl;
		//cout<<newTask.getEndTime()<<endl;
		return false;
	}

	newTask.setBlock(false);
	newTask.setDay("ANYDAY!");
	newTask.setDeadline(true);
	newTask.setStatus("NOTDONE");

	addToList(taskList, newTask, position);
	return true;
}

void LogicAdd::initialiseTask(Task& newTask){
	newTask.setTask(NOTFOUND, NOTFOUND, NOTFOUND, NOTFOUND, NOTFOUND, NOTFOUND, NOTFOUND, NOTFOUND, NOUPDATE, NOUPDATE, NOUPDATE, false, false);
}
void LogicAdd::addToList(TaskList& taskList, Task& newTask, int& position){
	taskList.findInsertPosition(newTask, position);
	taskList.insertTaskToPosition(newTask, position);
}

void LogicAdd::addDeletedTask(TaskList& taskList, Task deletedTask, int position){
	taskList.insertTaskToPosition(deletedTask, position);
}

void LogicAdd::trimUserInput(string& userInput){
	int length = userInput.length() - ONE;
	userInput = userInput.substr(ONE,length);
}

bool LogicAdd::checkDateTimeValidity(int startYear, int startMonth, int startDay,  int endYear, int endMonth, int endDay, int startTime, int endTime){
	if (startYear > endYear)
		return false;
	else if(startYear == endYear)
		if(startMonth > endMonth)
			return false;
		else if (startMonth == endMonth)
			if(startDay > endDay)
				return false;
			else if (startDay == endDay)
				return (startTime < endTime);

	return true;
}

//void LogicAdd::setDate(){
//	int year,month,day,hr,min;
//	string dayOfTheWeek;
//
//	retrieveDateTime(year,month,day,hr,min,dayOfTheWeek);
//
//	_newTask.setStartDay(day);
//	_newTask.setStartMonth(month);
//	_newTask.setStartYear(year);
//	_newTask.setEndDay(day);
//	_newTask.setEndMonth(month);
//	_newTask.setEndYear(year);
//	_newTask.setDay(dayOfTheWeek);
//}

//void LogicAdd::retrieveDateTime(int& year, int& month, int& day, int& hour, int& minute, string& dayOfTheWeek){
//
//	static string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
//	time_t now = time(ZERO);
//	tm *localTime = localtime(&now);
//
//	year = STARTYEAR + localTime->tm_year;
//	month = FIRSTPOSITION + localTime->tm_mon;
//	day = localTime->tm_mday;
//	hour = localTime->tm_hour;
//	minute = localTime->tm_min;
//	dayOfTheWeek = days[localTime->tm_wday];
//}

//string LogicAdd::convertLowercase(string text){
//	transform(text.begin(), text.end(), text.begin(), ::tolower);
//	return text;
//}

//bool LogicAdd::findDate(string findText, int& year, int& month, int& day){
//	int findYear, findMonth, findDay;
//	findYear = findMonth = findDay = NOTFOUND;
//
//	bool firstSlash = false;
//	bool secondSlash = false;
//	int dayCheck = ZERO;
//	int monthCheck = ZERO;
//	int yearCheck = ZERO;
//	int move = ZERO;
//
//	while(_slashPosition != NOTFOUND || findText.size() >= SIX){
//
//		if(_slashPosition == ONE)
//			move = ONE;
//		else
//			move = TWO;
//
//		if(_slashPosition == ZERO){}
//		else{
//			for(int i = _slashPosition - move; i < findText.size(); i++){
//
//				if(firstSlash && dayCheck == ZERO)
//					break;
//				if(secondSlash && monthCheck == ZERO)
//					break;
//
//				if(!firstSlash && findText[i] == DATESLASH)
//					firstSlash = true;
//				else if(!secondSlash && firstSlash && findText[i] == DATESLASH)
//					secondSlash = true;
//
//				if(findText[i] == DATESLASH){}
//				else if(!firstSlash){
//					if(isdigit(findText[i]))
//						dayCheck++;
//					else if(dayCheck == ONE)
//						break;
//				}
//				else if(firstSlash && !secondSlash){
//					if(isdigit(findText[i]))
//						monthCheck++;
//					else
//						break;
//					if(monthCheck > TWO)
//						break;
//				}
//				else if(firstSlash && secondSlash){
//					if(isdigit(findText[i]) && yearCheck < 4)
//						yearCheck++;
//					else
//						break;
//				}
//			}
//		}
//
//		if(yearCheck >= TWO){
//			if(dayCheck == ONE)
//				findDay = stoi(findText.substr((_slashPosition - ONE), ONE));
//			else if(dayCheck == TWO)
//				findDay = stoi(findText.substr((_slashPosition - TWO), TWO));
//
//			if(monthCheck == ONE){
//				findMonth = stoi(findText.substr((_slashPosition + ONE), ONE));
//
//				if(yearCheck == TWO || yearCheck == THREE)
//					findYear = stoi(findText.substr((_slashPosition + THREE), TWO));
//				else if(yearCheck == FOUR)
//					findYear = stoi(findText.substr((_slashPosition + THREE), FOUR));
//			}
//			else if(monthCheck == TWO){
//				findMonth = stoi(findText.substr((_slashPosition + ONE), TWO));
//
//				if(yearCheck == TWO || yearCheck == THREE)
//					findYear = stoi(findText.substr((_slashPosition + FOUR), TWO));
//				else if(yearCheck == FOUR)
//					findYear = stoi(findText.substr((_slashPosition + FOUR), FOUR));
//			}
//			if(dayCheck == ONE && monthCheck == ONE && yearCheck == TWO)
//				_date = findText.substr(_slashPosition - ONE, SIX);
//			else if(dayCheck==TWO && monthCheck == ONE && yearCheck == TWO)
//				_date = findText.substr(_slashPosition - TWO, SEVEN);
//			else if(dayCheck==ONE && monthCheck == TWO && yearCheck == TWO)
//				_date = findText.substr(_slashPosition - ONE, SEVEN);
//			else if(dayCheck==TWO && monthCheck ==TWO && yearCheck == TWO)
//				_date = findText.substr(_slashPosition - TWO, EIGHT);
//			else if(dayCheck == ONE && monthCheck == ONE && yearCheck == FOUR)
//				_date = findText.substr(_slashPosition - ONE, EIGHT);
//			else if(dayCheck==TWO && monthCheck == ONE && yearCheck == FOUR)
//				_date = findText.substr(_slashPosition - TWO, NINE);
//			else if(dayCheck==ONE && monthCheck == TWO && yearCheck == FOUR)
//				_date = findText.substr(_slashPosition - ONE, NINE);
//			else if (dayCheck==TWO && monthCheck ==TWO && yearCheck == FOUR)
//				_date = findText.substr(_slashPosition - TWO, TEN);
//		}
//
//		if(checkDate(findDay, findMonth, findYear)){
//			day = findDay;
//			month = findMonth;
//			year = findYear;
//			return true;
//		}
//
//		firstSlash = false;
//		secondSlash = false;
//		dayCheck = ZERO;
//		monthCheck = ZERO;
//		yearCheck = ZERO;
//		move = ZERO;
//
//		findText = findText.substr((_slashPosition + ONE), (findText.size() - (_slashPosition + ONE)));
//		_slashPosition = findText.find(DATESLASH);
//	}
//	return false;
//}

//bool LogicAdd::checkDate(int day, int month, int year){
//	int currentYear, currentMonth, currentDay, days;
//	retrieveDate(currentYear, currentMonth, currentDay);
//
//	if(year < YEARCHECK)
//		year += TWOTHOUSAND;
//
//	switch (month){
//	case 1: case 3: case 5: case 7:case 8: case 10: case 12 :
//		days=31;
//		break;
//	case 4: case 6: case 9: case 11 :
//		days=30;
//		break;
//	case 2 : 
//		if(((year % 4 == 0) && (year % 100 != 0))||(year % 400 == 0))
//			days=29;
//		else
//			days=28;
//		break;
//	}
//
//	if (day > ZERO && day <= days && month > ZERO && month <= MONTHCHECK && year >= currentYear){
//		if(year > currentYear)
//			return true;
//		else if(month > currentMonth)
//			return true;
//		else if(day >= currentDay)
//			return true;
//		else
//			return false;
//	}
//	else
//		return false;
//}

//bool LogicAdd::findHoursTime(string findText, int& hours){
//	int hrsCheck = ZERO;
//
//	while(_hrsPosition != NOTFOUND){
//		if(findText[_hrsPosition - ONE] == SPACE && (_hrsPosition - FIVE) >= ZERO){
//			for(int i = _hrsPosition - FIVE; i < _hrsPosition; i++){
//				if(isdigit(findText[i]))
//					hrsCheck++;
//				else
//					break;
//				if(hrsCheck == FOUR){
//					hours = stoi(findText.substr((_hrsPosition - FIVE), FOUR));
//					_time = findText.substr((_hrsPosition - FIVE), EIGHT);
//					return true;
//				}
//			}
//		}
//		else{
//			for(int i = _hrsPosition - FOUR; i < _hrsPosition; i++){
//				if(isdigit(findText[i]))
//					hrsCheck++;
//				else
//					break;
//				if(hrsCheck == FOUR){
//					hours = stoi(findText.substr((_hrsPosition - FOUR), FOUR));
//					_time = findText.substr((_hrsPosition - FOUR), SEVEN);
//					return true;
//				}
//			}
//		}
//		hrsCheck = ZERO;
//
//		findText = findText.substr((_hrsPosition + ONE), (findText.size() - (_hrsPosition + ONE)));
//		_hrsPosition = findText.find(HRS);
//	}
//	return false;
//}

//bool LogicAdd::findHoursMeridiemTime(string findText, string& meridiem, int& hours){
//	int hrsCheck = ZERO;
//	int position = ZERO;
//	int shiftPosition = ZERO;
//
//	while(_amPosition != NOTFOUND || _pmPosition != NOTFOUND){
//		if(_amPosition != NOTFOUND && _pmPosition == NOTFOUND){
//			position = _amPosition;
//			meridiem = MORNING;
//		}
//		else if(_amPosition == NOTFOUND && _pmPosition != NOTFOUND){
//			position = _pmPosition;
//			meridiem = AFTERNOON;
//		}
//		else if(_amPosition != NOTFOUND && _pmPosition != NOTFOUND && _amPosition < _pmPosition){
//			position = _amPosition;
//			meridiem = MORNING;
//		}
//		else if(_amPosition != NOTFOUND && _pmPosition != NOTFOUND && _amPosition > _pmPosition){
//			position = _pmPosition;
//			meridiem = AFTERNOON;
//		}
//
//		if(position == ZERO){}
//		else if(position == ONE || (position == TWO && findText[ONE] == SPACE)){
//			if(isdigit(findText[ZERO])){
//				hours = stoi(findText.substr(ZERO, ONE));
//
//				if (position == ONE)
//					_time = findText.substr(ZERO, THREE);
//				else //if (position == two)
//					_time = findText.substr(ZERO, FOUR);
//				return true;
//			}
//		}
//		else if(position == TWO){
//			if(isdigit(findText[ZERO]) && isdigit(findText[ONE])){
//				hours = stoi(findText.substr(ZERO, TWO));
//				_time = findText.substr(ZERO, FOUR);
//				return true;
//			}
//			else if(isdigit(findText[ONE])){
//				hours = stoi(findText.substr(ONE, ONE));
//				_time = findText.substr(ONE, THREE);
//				return true;
//			}
//		}
//		else if(findText[position - ONE] == SPACE){
//			if(isdigit(findText[position - THREE]) && isdigit(findText[position - TWO])){
//				hours = stoi(findText.substr((position - THREE), TWO));
//				_time = findText.substr((position - THREE), FIVE);
//				return true;
//			}
//			else if(isdigit(findText[position - TWO])){
//				hours = stoi(findText.substr((position - TWO), ONE));
//				_time = findText.substr((position - TWO), FOUR);
//				return true;
//			}
//		}
//		else{
//			if(isdigit(findText[position - TWO]) && isdigit(findText[position - ONE])){
//				hours = stoi(findText.substr((position - TWO), TWO));
//				_time = findText.substr((position - TWO), FOUR);
//				return true;
//			}
//			else if(isdigit(findText[position - ONE])){
//				hours = stoi(findText.substr((position - ONE), ONE));
//				_time = findText.substr((position - ONE), THREE);
//				return true;
//			}
//		}
//
//		findText = findText.substr((position + ONE), (findText.size() - (position + ONE)));
//		_amPosition = findText.find(MORNING);
//		_pmPosition = findText.find(AFTERNOON);
//	}
//	return false;
//}

//bool LogicAdd::findMeridiemTime(string findText, string& meridiem, int& hours, int& minutes){
//
//	int pointPosition;
//	int meridiemPosition;
//	int textRemovePoint;
//	while(findText.size() >= FIVE){
//		if(_dotPosition != NOTFOUND && _colonPosition != NOTFOUND){
//			if(_dotPosition < _colonPosition)
//				pointPosition = _dotPosition;
//			else
//				pointPosition = _colonPosition;
//		}
//		else if(_dotPosition == NOTFOUND && _colonPosition != NOTFOUND)
//			pointPosition = _colonPosition;
//		else if(_dotPosition != NOTFOUND && _colonPosition == NOTFOUND)
//			pointPosition = _dotPosition;
//		else
//			return false;
//
//		if(_amPosition != NOTFOUND && _pmPosition != NOTFOUND){
//			if(_amPosition < _pmPosition){
//				meridiemPosition = _amPosition;
//				meridiem = MORNING;
//			}
//			else{
//				meridiemPosition = _pmPosition;
//				meridiem = AFTERNOON;
//			}
//		}
//		else if(_amPosition == NOTFOUND && _pmPosition != NOTFOUND){
//			meridiemPosition = _pmPosition;
//			meridiem = AFTERNOON;
//		}
//		else if(_amPosition != NOTFOUND && _pmPosition == NOTFOUND){
//			meridiemPosition = _amPosition;
//			meridiem = MORNING;
//		}
//		else
//			return false;
//
//		if(meridiemPosition < pointPosition)
//			textRemovePoint = meridiemPosition + ONE;
//
//		else if(pointPosition == ZERO)
//			textRemovePoint = pointPosition + ONE;
//
//		else if((((meridiemPosition - pointPosition) == FOUR) && (findText[meridiemPosition - ONE] == SPACE)) || ((meridiemPosition - pointPosition) == THREE)){
//			//"1:30pm" and "1:30 pm - single digit hour"
//			if(pointPosition == ONE){
//				if(isdigit(findText[pointPosition - ONE]) && isdigit(findText[pointPosition + ONE]) && isdigit(findText[pointPosition + TWO])){
//					hours = stoi(findText.substr((pointPosition - ONE), ONE));
//					minutes = stoi(findText.substr((pointPosition + ONE), TWO));
//					_time = findText.substr((pointPosition - ONE), SIX);
//					return true;
//				}
//				else
//					textRemovePoint = pointPosition + ONE;
//			}
//			//"11.30pm and 11.30 pm - double digit hour"
//			else{
//				if(isdigit(findText[pointPosition - TWO]) && isdigit(findText[pointPosition - ONE]) &&
//					isdigit(findText[pointPosition + ONE]) && isdigit(findText[pointPosition + TWO])){
//						hours = stoi(findText.substr((pointPosition - TWO), TWO));
//						minutes = stoi(findText.substr((pointPosition + ONE), TWO));
//						_time = findText.substr((pointPosition - TWO), SEVEN);
//						return true;
//				}
//				else if(isdigit(findText[pointPosition - ONE]) && isdigit(findText[pointPosition + ONE]) && isdigit(findText[pointPosition + TWO])){
//					hours = stoi(findText.substr((pointPosition - TWO), TWO));
//					minutes = stoi(findText.substr((pointPosition + ONE), TWO));
//					_time = findText.substr((pointPosition - ONE), SIX);
//					return true;
//				}
//				else
//					textRemovePoint = pointPosition + ONE;
//			}
//		}
//		else
//			textRemovePoint = pointPosition + ONE;
//
//		findText = findText.substr(textRemovePoint,(findText.size() - textRemovePoint));
//		_amPosition = findText.find(MORNING);
//		_pmPosition = findText.find(AFTERNOON);
//		_dotPosition = findText.find(DOT);
//		_colonPosition = findText.find(COLON);
//
//		if((_amPosition == NOTFOUND && _pmPosition == NOTFOUND) || (_colonPosition == NOTFOUND && _dotPosition == NOTFOUND))
//			break;
//	}
//	return false;
//}

//void LogicAdd::findUserInput(Task& newTask, string parserString){
//	int timePosition;
//	int datePosition;
//	string taskDescription;
//
//	timePosition = parserString.find(_time);
//	datePosition = parserString.find(_date);
//
//
//	if(datePosition == NOTFOUND)
//		taskDescription = parserString.substr(ZERO, timePosition-ONE);
//	else if(timePosition == NOTFOUND)
//		taskDescription = parserString.substr(ZERO, datePosition-ONE);
//	else if (datePosition < timePosition)
//		taskDescription = parserString.substr(ZERO, datePosition-ONE);
//	else if (datePosition > timePosition)
//		taskDescription = parserString.substr(ZERO, timePosition-ONE);
//
//	newTask.setTaskDescription(taskDescription);
//}

//void LogicAdd::retrieveDate(int& year, int& month, int& day){
//	time_t now = time(0);
//	tm *ltm = localtime(&now);
//
//	year = 1900 + ltm->tm_year;
//	month = 1 + ltm->tm_mon;
//	day = ltm->tm_mday;
//}

//bool LogicAdd::checkTime(int time){
//	if(time % HUNDRED < MAXMINUTES && time / HUNDRED < MAXHOURS)
//		return true;
//	else
//		return false;
//}