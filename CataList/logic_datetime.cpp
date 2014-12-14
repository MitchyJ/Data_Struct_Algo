#include "logic_datetime.h"
//v0.2.1
const string LogicDateTime::CANNOTFIND = "CaNNoTfINd";
const string LogicDateTime::HOURS = "hrs";
const string LogicDateTime::AM = "am";
const string LogicDateTime::PM = "pm";

bool LogicDateTime::parser(Task& task, string text, string operation){
	int year, month, day;
	int hours, minutes;
	int tempPosition;
	int tempHours1, tempHours2;

	string lowercaseText = textChangeLowercase(text);
	string tempText;

	string stringTime = CANNOTFIND;
	string tempTime1 = CANNOTFIND;
	string tempTime2 = CANNOTFIND;
	string tempDate = CANNOTFIND;
	string meridiem;

	bool checkText = true;

	_checkTime = true;
	_hoursFlag = false;
	_taskDescription = text;
	_date = CANNOTFIND;
	_time = CANNOTFIND;

	year = month = day = NOTSTATED;

	getPosition(lowercaseText);

	if(_slashPosition == NOTSTATED && _hrsPosition == NOTSTATED &&
		_amPosition == NOTSTATED && _pmPosition == NOTSTATED &&
		_colonPosition == NOTSTATED && _dotPosition == NOTSTATED){
			task.setTaskDescription(text);
			return true;
	}
	/*
	if no position found, the whole text will be the task Description
	for add, it will be a floating task
	for edit, it will be change of task description
	*/

	if(_slashPosition != NOTSTATED){
		if(parserDate(task, lowercaseText, year, month, day, checkText)){
			if(!checkText)
				return false;
			tempDate = _date;
			_taskDescription = trimFoundTime(textChangeLowercase(_taskDescription), _date);
			tempPosition = lowercaseText.find(_date);
			tempText = lowercaseText.substr((tempPosition + POINTSIX), (lowercaseText.size() - (tempPosition + POINTONE)));
			_slashPosition = tempText.find(SLASHCODE);
			if(parserDate(task, tempText, year, month, day, checkText)){
				if(!checkText)
					return false;
				_taskDescription = trimFoundTime(textChangeLowercase(_taskDescription), _date);
			}
		}
	}

	if(task.getStartDay() != NOTSTATED && task.getEndDay() == NOTSTATED)
		setTaskDate(task, task.getStartYear(), task.getStartMonth(), task.getStartDay());
	/*
	tempDate is the first Date found
	_date is the second Date found
	if no date is found both are "CaNNoTfINd" string
	if only 1 date is found, then both tempDate and _date are the same date
	*/

	if(parserTime(task, lowercaseText)){
		if(!_checkTime)
			return false;
	}
	else
		return false;

	removeUnwantedText();
	if(_taskDescription.size() != POINTZERO)
		task.setTaskDescription(_taskDescription);
	/*
	if _taskDescription size is 0,
	then mean user did not type in task description
	*/

	if(operation == "change"){
		return true;
	}

	if(operation == "add")
		findUserInput(task ,text);

	if (_time != CANNOTFIND && _date != CANNOTFIND){}
	else if (_time == CANNOTFIND){
		task.setStartTime(900);
		task.setEndTime(1800);
	}
	else if (_date == CANNOTFIND)
		setDate(task);
	else
		//floating
		return false;
}
//when text size is 1 return false!
void LogicDateTime::removeUnwantedText(){
	bool spaceCheck = false;
	while(!spaceCheck){
		if(_taskDescription[POINTZERO] == SPACECODE)
			_taskDescription = _taskDescription.substr(POINTONE, (_taskDescription.size() - POINTONE));
		if(_taskDescription.size() >= POINTONE){
			if(_taskDescription[_taskDescription.size() - POINTONE] == SPACECODE)
				_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTONE));
		}
		if(_taskDescription[POINTZERO] == SPACECODE)
			_taskDescription = _taskDescription.substr(POINTONE, (_taskDescription.size() - POINTONE));
		if(_taskDescription.size() >= POINTONE){
			if(_taskDescription[_taskDescription.size() - POINTONE] == SPACECODE)
				_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTONE));
		}

		spaceCheck = true;

		if(_taskDescription.find("to ") == POINTZERO){
			_taskDescription = _taskDescription.substr(POINTTHREE, (_taskDescription.size() - POINTTHREE));
			spaceCheck = false;
		}
		if(_taskDescription.size() >= POINTTHREE){
			if(_taskDescription.substr((_taskDescription.size() - POINTTHREE), POINTTHREE) == " to"){
				_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTTHREE));
				spaceCheck = false;
			}
		}

		if(_taskDescription.find("on ") == POINTZERO){
			_taskDescription = _taskDescription.substr(POINTTHREE, (_taskDescription.size() - POINTTHREE));
			spaceCheck = false;
		}
		if(_taskDescription.size() >= POINTTHREE){
			if(_taskDescription.substr((_taskDescription.size() - POINTTHREE), POINTTHREE) == " on"){
				_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTTHREE));
				spaceCheck = false;
			}
		}

		if(_taskDescription.find("at ") == POINTZERO){
			_taskDescription = _taskDescription.substr(POINTTHREE, (_taskDescription.size() - POINTTHREE));
			spaceCheck = false;
		}
		if(_taskDescription.size() >= POINTTHREE){
			if(_taskDescription.substr((_taskDescription.size() - POINTTHREE), POINTTHREE) == " at"){
				_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTTHREE));
				spaceCheck = false;
			}
		}

		if(_taskDescription.find("from ") == POINTZERO){
			_taskDescription = _taskDescription.substr(POINTFIVE, (_taskDescription.size() - POINTFIVE));
			spaceCheck = false;
		}
		if(_taskDescription.size() >= POINTFIVE){
			if(_taskDescription.substr((_taskDescription.size() - POINTFIVE), POINTFIVE) == " from"){
				_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTFIVE));
				spaceCheck = false;
			}
		}
	}
}

string LogicDateTime::textChangeLowercase(string text){
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

void LogicDateTime::getPosition(string text){
	_slashPosition = text.find(SLASHCODE);
	_hrsPosition = text.find(HOURS);
	_dotPosition = text.find(DOTCODE);
	_colonPosition = text.find(COLONCODE);
	_amPosition = text.find(AM);
	_pmPosition = text.find(PM);
}

bool LogicDateTime::parserDate(Task& task, string text, int year, int month, int day, bool& checkText){
	if(findDate(text, year, month, day)){
		if(checkDate(day, month, year)){
			if(year < HUNDRED)
				year += TWOTHOUSAND;
			setTaskDate(task, year, month, day);
			return true;
		}
		else{
			checkText = false;
			return true;
		}
	}
	return false;
}

void LogicDateTime::setTaskDate(Task& task, int year, int month, int day){
	if(task.getStartYear() == NOTSTATED){
		task.setStartDay(day);
		task.setStartMonth(month);
		task.setStartYear(year);
	}
	else{
		task.setEndDay(day);
		task.setEndMonth(month);
		task.setEndYear(year);
	}
}

bool LogicDateTime::findDate(string text, int& year, int& month, int& day){

	bool firstSlash = false;
	bool secondSlash = false;
	int dayCheck = POINTZERO;
	int monthCheck = POINTZERO;
	int yearCheck = POINTZERO;
	int shift = POINTZERO;

	while(_slashPosition != NOTSTATED || text.size() >= POINTSIX){

		if(_slashPosition == POINTONE)
			shift = POINTONE;
		else
			shift = POINTTWO;

		if(_slashPosition == POINTZERO){}
		else{
			for(int i = _slashPosition - shift; i < text.size(); i++){

				if(firstSlash && dayCheck == POINTZERO)
					break;
				if(secondSlash && monthCheck == POINTZERO)
					break;

				if(!firstSlash && text[i] == SLASHCODE)
					firstSlash = true;
				else if(!secondSlash && firstSlash && text[i] == SLASHCODE)
					secondSlash = true;

				if(text[i] == SLASHCODE){}
				else if(!firstSlash){
					if(isdigit(text[i]))
						dayCheck++;
					else if(dayCheck == POINTONE)
						break;
				}
				else if(firstSlash && !secondSlash){
					if(isdigit(text[i]))
						monthCheck++;
					else
						break;
					if(monthCheck > POINTTWO)
						break;
				}
				else if(firstSlash && secondSlash){
					if(isdigit(text[i]) && yearCheck < POINTFOUR)
						yearCheck++;
					else
						break;
				}
			}
		}

		if(yearCheck >= POINTTWO){
			if(dayCheck == POINTONE)
				day = stoi(text.substr((_slashPosition - POINTONE), POINTONE));
			else if(dayCheck == POINTTWO)
				day = stoi(text.substr((_slashPosition - POINTTWO), POINTTWO));

			if(monthCheck == POINTONE){
				month = stoi(text.substr((_slashPosition + POINTONE), POINTONE));

				if(yearCheck == POINTTWO || yearCheck == POINTTHREE)
					year = stoi(text.substr((_slashPosition + POINTTHREE), POINTTWO));
				else if(yearCheck == POINTFOUR)
					year = stoi(text.substr((_slashPosition + POINTTHREE), POINTFOUR));
			}
			else if(monthCheck == POINTTWO){
				month = stoi(text.substr((_slashPosition + POINTONE), POINTTWO));

				if(yearCheck == POINTTWO || yearCheck == POINTTHREE)
					year = stoi(text.substr((_slashPosition + POINTFOUR), POINTTWO));
				else if(yearCheck == POINTFOUR)
					year = stoi(text.substr((_slashPosition + POINTFOUR), POINTFOUR));
			}
			if(dayCheck == POINTONE && monthCheck == POINTONE && (yearCheck == POINTTWO || yearCheck == POINTTHREE))
				_date = text.substr(_slashPosition - POINTONE, POINTSIX);
			else if(dayCheck == POINTTWO && monthCheck == POINTONE && (yearCheck == POINTTWO || yearCheck == POINTTHREE))
				_date = text.substr(_slashPosition - POINTTWO, POINTSEVEN);
			else if(dayCheck == POINTONE && monthCheck == POINTTWO && (yearCheck == POINTTWO || yearCheck == POINTTHREE))
				_date = text.substr(_slashPosition - POINTONE, POINTSEVEN);
			else if(dayCheck == POINTTWO && monthCheck == POINTTWO && (yearCheck == POINTTWO || yearCheck == POINTTHREE))
				_date = text.substr(_slashPosition - POINTTWO, POINTEIGHT);
			else if(dayCheck == POINTONE && monthCheck == POINTONE && yearCheck == POINTFOUR)
				_date = text.substr(_slashPosition - POINTONE, POINTEIGHT);
			else if(dayCheck == POINTTWO && monthCheck == POINTONE && yearCheck == POINTFOUR)
				_date = text.substr(_slashPosition - POINTTWO, POINTNINE);
			else if(dayCheck == POINTONE && monthCheck == POINTTWO && yearCheck == POINTFOUR)
				_date = text.substr(_slashPosition - POINTONE, POINTNINE);
			else if(dayCheck == POINTTWO && monthCheck == POINTTWO && yearCheck == POINTFOUR)
				_date = text.substr(_slashPosition - POINTTWO, POINTTEN);
			return true;
		}

		firstSlash = false;
		secondSlash = false;
		dayCheck = POINTZERO;
		monthCheck = POINTZERO;
		yearCheck = POINTZERO;
		shift = POINTZERO;

		text = text.substr((_slashPosition + POINTONE), (text.size() - (_slashPosition + POINTONE)));
		_slashPosition = text.find(SLASHCODE);
	}
	return false;
}

//MAGIC NUMBER HERE
bool LogicDateTime::checkDate(int day, int month, int year){
	int currentYear, currentMonth, currentDay, days;
	retrieveDate(currentYear, currentMonth, currentDay);

	if(year < YEARCHECK)
		year += TWOTHOUSAND;

	switch (month){
	case 1: case 3: case 5: case 7:case 8: case 10: case 12 :
		days = 31;
		break;
	case 4: case 6: case 9: case 11 :
		days = 30;
		break;
	case 2 : 
		if(((year % 4 == 0) && (year % 100 != 0))||(year % 400 == 0))
			days = 29;
		else
			days = 28;
		break;
	}

	if (day > POINTZERO && day <= days && month > POINTZERO && month <= MONTHCHECK && year >= currentYear){
		if(year > currentYear)
			return true;
		else if(month > currentMonth)
			return true;
		else if(day >= currentDay)
			return true;
		else
			return false;
	}
	else
		return false;
}

//MAGICNUMBER HERE!!
void LogicDateTime::retrieveDate(int& year, int& month, int& day){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	year = 1900 + ltm->tm_year;
	month = 1 + ltm->tm_mon;
	day = ltm->tm_mday;
}

bool LogicDateTime::parserTime(Task& task, string text){
	int tempHours1 = NOTSTATED;
	int tempHours2 = NOTSTATED;
	int hours;
	int time;

	string stringTime = CANNOTFIND;
	string tempTime1 = CANNOTFIND;
	string tempTime2 = CANNOTFIND;

	string tempText = text;

	if(!getTime(text, tempTime1, tempTime2, tempHours1, tempHours2, hours))
		return true;

	if(tempTime1 == CANNOTFIND && tempTime2 == CANNOTFIND)
		return true;
	else if(tempTime1 != CANNOTFIND && tempTime2 != CANNOTFIND){
		if(text.find(tempTime1) < text.find(tempTime2)){
			_time = tempTime1;
			setTaskTime(task, tempHours1, tempHours2);
		}
		else{

			_time = tempTime2;
			setTaskTime(task, tempHours2, tempHours1);
		}
		return true;
	}

	else if(tempTime1 != CANNOTFIND){
		stringTime = tempTime1;
		time = tempHours1;
	}
	else if(tempTime2 != CANNOTFIND){
		stringTime = tempTime2;
		time = tempHours2;
	}

	tempHours1 = NOTSTATED;
	tempHours2 = NOTSTATED;
	tempTime1 = CANNOTFIND;
	tempTime2 = CANNOTFIND;
	tempText = trimFoundTime(tempText, stringTime);
	getPosition(tempText);

	if(!getTime(tempText, tempTime1, tempTime2, tempHours1, tempHours2, hours))
		return true;

	if(tempTime1 == CANNOTFIND && tempTime2 == CANNOTFIND){
		setTaskTime(task, time, time);
		return true;
	}
	else if(tempTime1 != CANNOTFIND && tempTime2 != CANNOTFIND){
		return false;
	}

	else if(tempTime1 != CANNOTFIND){
		if(text.find(tempTime1) < text.find(stringTime)){
			_time = tempTime1;
			setTaskTime(task, tempHours1, time);
		}
		else
			setTaskTime(task, time, tempHours1);
	}
	else if(tempTime2 != CANNOTFIND){
		if(text.find(tempTime2) < text.find(stringTime)){
			_time = tempTime2;
			setTaskTime(task, tempHours2, time);
		}
		else
			setTaskTime(task, time, tempHours2);
	}
	return true;
}

bool LogicDateTime::getTime(string text, string& tempTime1, string& tempTime2, int& tempHours1, int& tempHours2, int hours){
	if(parserHours(text, hours)){
		tempHours1 = hours;
		tempTime1 = _time;
		if(!_checkTime)
			return false;
		_taskDescription = trimFoundTime(textChangeLowercase(_taskDescription), _time);
	}
	if(parserSymbolledTime(text, hours)){
		tempHours2 = hours;
		tempTime2 = _time;
		if(!_checkTime)
			return false;
		_taskDescription = trimFoundTime(textChangeLowercase(_taskDescription), _time);
	}
	else if(parserMeridiemTime(text, hours)){
		tempHours2 = hours;
		tempTime2 = _time;
		if(!_checkTime)
			return false;
		_taskDescription = trimFoundTime(textChangeLowercase(_taskDescription), _time);
	}
	return true;
}

bool LogicDateTime::parserHours(string text, int& hours){
	if(findHoursTime(text, hours)){
		if(!checkTime(hours))
			_checkTime = false;
		return true;
	}
	else
		return false;
}

bool LogicDateTime::findHoursTime(string text, int& hours){
	int hrsCheck = POINTZERO;

	while(_hrsPosition != NOTSTATED){
		if(text[_hrsPosition - POINTONE] == SPACECODE && (_hrsPosition - POINTFIVE) >= POINTZERO){
			for(int i = _hrsPosition - POINTFIVE; i < _hrsPosition; i++){
				if(isdigit(text[i]))
					hrsCheck++;
				else
					break;
				if(hrsCheck == POINTFOUR){
					hours = stoi(text.substr((_hrsPosition - POINTFIVE), POINTFOUR));
					_time = text.substr((_hrsPosition - POINTFIVE), POINTEIGHT);
					return true;
				}
			}
		}
		else{
			for(int i = _hrsPosition - POINTFOUR; i < _hrsPosition; i++){
				if(isdigit(text[i]))
					hrsCheck++;
				else
					break;
				if(hrsCheck == POINTFOUR){
					hours = stoi(text.substr((_hrsPosition - POINTFOUR), POINTFOUR));
					_time = text.substr((_hrsPosition - POINTFOUR), POINTSEVEN);
					return true;
				}
			}
		}
		hrsCheck = POINTZERO;

		text = text.substr((_hrsPosition + POINTONE), (text.size() - (_hrsPosition + POINTONE)));
		_hrsPosition = text.find(HOURS);
	}
	return false;
}

bool LogicDateTime::parserSymbolledTime(string text, int& hours){
	string meridiem;
	int minutes;
	if(findMeridiemTime(text, meridiem, hours, minutes)){
		if(meridiem == AM){
			if(hours == TWELVEHOURS)
				hours = POINTZERO;
			if(hours > TWELVEHOURS){
				_checkTime = false;
				return true;
			}
		}
		if(meridiem == PM)
			if(hours != TWELVEHOURS)
				hours += TWELVEHOURS;
		hours = hours * HUNDRED + minutes;
		if(!checkTime(hours))
			_checkTime = false;
		return true;
	}
	return false;
}

bool LogicDateTime::findMeridiemTime(string text, string& meridiem, int& hours, int& minutes){

	int pointPosition;
	int meridiemPosition;
	int textRemovePoint;
	while(text.size() >= POINTFIVE){
		if(_dotPosition != NOTSTATED && _colonPosition != NOTSTATED){
			if(_dotPosition < _colonPosition)
				pointPosition = _dotPosition;
			else
				pointPosition = _colonPosition;
		}
		else if(_dotPosition == NOTSTATED && _colonPosition != NOTSTATED)
			pointPosition = _colonPosition;
		else if(_dotPosition != NOTSTATED && _colonPosition == NOTSTATED)
			pointPosition = _dotPosition;
		else
			return false;

		if(_amPosition != NOTSTATED && _pmPosition != NOTSTATED){
			if(_amPosition < _pmPosition){
				meridiemPosition = _amPosition;
				meridiem = AM;
			}
			else{
				meridiemPosition = _pmPosition;
				meridiem = PM;
			}
		}
		else if(_amPosition == NOTSTATED && _pmPosition != NOTSTATED){
			meridiemPosition = _pmPosition;
			meridiem = PM;
		}
		else if(_amPosition != NOTSTATED && _pmPosition == NOTSTATED){
			meridiemPosition = _amPosition;
			meridiem = AM;
		}
		else
			return false;

		if(meridiemPosition < pointPosition)
			textRemovePoint = meridiemPosition + POINTONE;

		else if(pointPosition == POINTZERO)
			textRemovePoint = pointPosition + POINTONE;

		else if((((meridiemPosition - pointPosition) == POINTFOUR) && (text[meridiemPosition - POINTONE] == SPACECODE)) || ((meridiemPosition - pointPosition) == POINTTHREE)){
			//"1:30pm" and "1:30 pm - single digit hour"
			if(pointPosition == POINTONE){
				if(isdigit(text[pointPosition - POINTONE]) && isdigit(text[pointPosition + POINTONE]) && isdigit(text[pointPosition + POINTTWO])){
					hours = stoi(text.substr((pointPosition - POINTONE), POINTONE));
					minutes = stoi(text.substr((pointPosition + POINTONE), POINTTWO));
					_time = text.substr((pointPosition - POINTONE), POINTSIX);
					return true;
				}
				else
					textRemovePoint = pointPosition + POINTONE;
			}
			//"11.30pm and 11.30 pm - double digit hour"
			else{
				if(isdigit(text[pointPosition - POINTTWO]) && isdigit(text[pointPosition - POINTONE]) &&
					isdigit(text[pointPosition + POINTONE]) && isdigit(text[pointPosition + POINTTWO])){
						hours = stoi(text.substr((pointPosition - POINTTWO), POINTTWO));
						minutes = stoi(text.substr((pointPosition + POINTONE), POINTTWO));
						_time = text.substr((pointPosition - POINTTWO), POINTSEVEN);
						return true;
				}
				else if(isdigit(text[pointPosition - POINTONE]) && isdigit(text[pointPosition + POINTONE]) && isdigit(text[pointPosition + POINTTWO])){
					hours = stoi(text.substr((pointPosition - POINTTWO), POINTTWO));
					minutes = stoi(text.substr((pointPosition + POINTONE), POINTTWO));
					_time = text.substr((pointPosition - POINTONE), POINTSIX);
					return true;
				}
				else
					textRemovePoint = pointPosition + POINTONE;
			}
		}
		else
			textRemovePoint = pointPosition + POINTONE;

		text = text.substr(textRemovePoint,(text.size() - textRemovePoint));
		_amPosition = text.find(AM);
		_pmPosition = text.find(PM);
		_dotPosition = text.find(DOTCODE);
		_colonPosition = text.find(COLONCODE);

		if((_amPosition == NOTSTATED && _pmPosition == NOTSTATED) || (_colonPosition == NOTSTATED && _dotPosition == NOTSTATED))
			break;
	}
	return false;
}

bool LogicDateTime::parserMeridiemTime(string text, int& hours){
	string meridiem;
	if(findHoursMeridiemTime(text, meridiem, hours)){
		if(meridiem == AM){
			if(hours == TWELVEHOURS)
				hours = POINTZERO;
			if(hours > TWELVEHOURS){
				_checkTime = false;
				return true;
			}
		}
		if(meridiem == PM)
			if(hours != TWELVEHOURS)
				hours += TWELVEHOURS;
		hours *= HUNDRED;
		if(!checkTime(hours))
			_checkTime = false;
		return true;
	}
	return false;
}

bool LogicDateTime::findHoursMeridiemTime(string text, string& meridiem, int& hours){
	int hrsCheck = POINTZERO;
	int position = POINTZERO;
	int shiftPosition = POINTZERO;

	while(_amPosition != NOTSTATED || _pmPosition != NOTSTATED){
		if(_amPosition != NOTSTATED && _pmPosition == NOTSTATED){
			position = _amPosition;
			meridiem = AM;
		}
		else if(_amPosition == NOTSTATED && _pmPosition != NOTSTATED){
			position = _pmPosition;
			meridiem = PM;
		}
		else if(_amPosition != NOTSTATED && _pmPosition != NOTSTATED && _amPosition < _pmPosition){
			position = _amPosition;
			meridiem = AM;
		}
		else if(_amPosition != NOTSTATED && _pmPosition != NOTSTATED && _amPosition > _pmPosition){
			position = _pmPosition;
			meridiem = PM;
		}

		if(position == POINTZERO){}
		else if(position == POINTONE || (position == POINTTWO && text[POINTONE] == SPACECODE)){
			if(isdigit(text[POINTZERO])){
				hours = stoi(text.substr(POINTZERO, POINTONE));

				if (position == POINTONE)
					_time = text.substr(POINTZERO, POINTTHREE);
				else
					_time = text.substr(POINTZERO, POINTFOUR);
				return true;
			}
		}
		else if(position == POINTTWO){
			if(isdigit(text[POINTZERO]) && isdigit(text[POINTONE])){
				hours = stoi(text.substr(POINTZERO, POINTTWO));
				_time = text.substr(POINTZERO, POINTFOUR);
				return true;
			}
			else if(isdigit(text[POINTONE])){
				hours = stoi(text.substr(POINTONE, POINTONE));
				_time = text.substr(POINTONE, POINTTHREE);
				return true;
			}
		}
		else if(text[position - POINTONE] == SPACECODE){
			if(isdigit(text[position - POINTTHREE]) && isdigit(text[position - POINTTWO])){
				hours = stoi(text.substr((position - POINTTHREE), POINTTWO));
				_time = text.substr((position - POINTTHREE), POINTFIVE);
				return true;
			}
			else if(isdigit(text[position - POINTTWO])){
				hours = stoi(text.substr((position - POINTTWO), POINTONE));
				_time = text.substr((position - POINTTWO), POINTFOUR);
				return true;
			}
		}
		else{
			if(isdigit(text[position - POINTTWO]) && isdigit(text[position - POINTONE])){
				hours = stoi(text.substr((position - POINTTWO), POINTTWO));
				_time = text.substr((position - POINTTWO), POINTFOUR);
				return true;
			}
			else if(isdigit(text[position - POINTONE])){
				hours = stoi(text.substr((position - POINTONE), POINTONE));
				_time = text.substr((position - POINTONE), POINTTHREE);
				return true;
			}
		}

		text = text.substr((position + POINTONE), (text.size() - (position + POINTONE)));
		_amPosition = text.find(AM);
		_pmPosition = text.find(PM);
	}
	return false;
}

bool LogicDateTime::checkTime(int time){
	if(time % HUNDRED < MAXMINUTES && time / HUNDRED < MAXHOURS)
		return true;
	else
		return false;
}

void LogicDateTime::setTaskTime(Task& task, int startHours, int endHours){
	if(startHours == endHours){
		task.setStartTime(startHours);
		task.setEndTime(startHours + HUNDRED);
		if(task.getEndTime() / HUNDRED >= MAXHOURS){
			task.setEndTime(task.getEndTime() - (MAXHOURS * HUNDRED));
			_hoursFlag = true;
		}
	}
	else{
		task.setStartTime(startHours);
		task.setEndTime(endHours);
	}
}

string LogicDateTime::trimFoundTime(string text, string textToTrim){
	int startPosition = text.find(textToTrim);
	if(startPosition != NOTSTATED){
		int endPosition = startPosition + (textToTrim.size() - POINTONE);
		string newText = text.substr(POINTZERO, startPosition) + text.substr((endPosition + POINTONE), text.size() - (endPosition + POINTONE));
		return newText;
	}
	else
		return _taskDescription;
}

void LogicDateTime::setDate(Task& task){
	int year,month,day;
	string dayOfTheWeek;
	retrieveDate(year,month,day);

	task.setStartDay(day);
	task.setStartMonth(month);
	task.setStartYear(year);
	task.setEndDay(day);
	task.setEndMonth(month);
	task.setEndYear(year);
	task.setDay(dayOfTheWeek);
}

void LogicDateTime::findUserInput(Task& task, string parserString){
	int timePosition;
	int datePosition;
	string taskDescription;

	timePosition = parserString.find(_time);
	datePosition = parserString.find(_date);


	if(datePosition == NOTSTATED)
		taskDescription = parserString.substr(POINTZERO, timePosition-POINTONE);
	else if(timePosition == NOTSTATED)
		taskDescription = parserString.substr(POINTZERO, datePosition-POINTONE);
	else if (datePosition < timePosition)
		taskDescription = parserString.substr(POINTZERO, datePosition-POINTONE);
	else if (datePosition > timePosition)
		taskDescription = parserString.substr(POINTZERO, timePosition-POINTONE);

	task.setTaskDescription(taskDescription);
}