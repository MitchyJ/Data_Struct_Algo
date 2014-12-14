#include "logic_detail_parser.h"

const string LogicDetailParser::CANNOTFIND = "CANNOTFIND";
const string LogicDetailParser::HOURS = "hrs";
const string LogicDetailParser::AM = "am";
const string LogicDetailParser::PM = "pm";

bool LogicDetailParser::parser(Task& task, string text, string operation){
	int dateCheck;
	int timeCheck;
	string tempDate;
	string lowercaseText = textChangeLowercase(text);

	_hoursFlag = false;
	_taskDescription = text;
	_time = CANNOTFIND;
	_date = CANNOTFIND;

	getIndicators(lowercaseText);

	if(_slashPosition == NOTSTATED && _hrsPosition == NOTSTATED &&
		_dotPosition == NOTSTATED && _colonPosition == NOTSTATED &&
		_amPosition == NOTSTATED && _pmPosition == NOTSTATED){
			task.setTaskDescription(text);
			return true;
	}

	if(_slashPosition != NOTSTATED){
		dateCheck = findDate(task, lowercaseText);
		if(dateCheck == ERROR)
			return false;
		else if(dateCheck == FOUND){
			tempDate = _date;
			_taskDescription = trimFoundText(_taskDescription, _date);

			lowercaseText = textChangeLowercase(_taskDescription);
			getIndicators(lowercaseText);

			dateCheck = findDate(task, lowercaseText);
			if(dateCheck == ERROR)
				return false;
			else if(dateCheck == FOUND)
				_taskDescription = trimFoundText(_taskDescription, _date);
			else if(dateCheck == NOTFOUND)
				setTaskDate(task, task.getStartDay(), task.getStartMonth(), task.getStartYear());
		}
	}
	_date = tempDate;

	if(!findTime(task, textChangeLowercase(text)))
		return false;

	removeUnwantedText();
	if(_taskDescription.size() != POINTZERO)
		task.setTaskDescription(_taskDescription);

	if(operation == "change"){
		if(task.getStartDay() == task.getEndDay() && _hoursFlag)
			task.setEndDay(task.getStartDay() + POINTONE);
		return true;
	}

	if(operation == "add"){
		if(task.getStartDay() == task.getEndDay() && _hoursFlag)
			task.setEndDay(task.getStartDay() + POINTONE);

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
}

string LogicDetailParser::textChangeLowercase(string text){
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

void LogicDetailParser::getIndicators(string text){
	_slashPosition = text.find(SLASHCODE);
	_hrsPosition = text.find(HOURS);
	_dotPosition = text.find(DOTCODE);
	_colonPosition = text.find(COLONCODE);
	_amPosition = text.find(AM);
	_pmPosition = text.find(PM);
}

int LogicDetailParser::findDate(Task& task, string text){
	int day, month, year;
	day = month = year = NOTSTATED;

	if(parserDate(text, day, month, year)){
		if(year < YEARCHECK)
			year += TWOTHOUSAND;
		if(checkDate(day, month, year)){
			setTaskDate(task, day, month, year);
			return FOUND;
		}
		else
			return ERROR;
	}
	return NOTFOUND;
}

bool LogicDetailParser::parserDate(string text, int& day, int& month, int& year){
	int startPosition, endPosition;

	while(_slashPosition != NOTSTATED){
		if(_slashPosition == POINTZERO){}
		//date format: 1/1/11 or 11/1/11 or 1/1/1111 or 11/1/1111
		else if(_slashPosition + POINTFOUR <= text.size() - POINTONE){
			if(isdigit(text[_slashPosition - POINTONE]) && isdigit(text[_slashPosition + POINTONE]) && text[_slashPosition + POINTTWO] == SLASHCODE && isdigit(text[_slashPosition + POINTTHREE]) && isdigit(text[_slashPosition + POINTFOUR])){
				day = stoi(text.substr((_slashPosition - POINTONE), POINTONE));
				month = stoi(text.substr((_slashPosition + POINTONE), POINTONE));
				year = stoi(text.substr((_slashPosition + POINTTHREE), POINTTWO));
				startPosition = _slashPosition - POINTONE;
				endPosition = POINTSIX;
				if(_slashPosition == POINTONE){
					// check if year is written as 4 digits: x/x/xxxx
					if(_slashPosition + POINTSIX <= text.size() - POINTONE){
						if(text.size() - _slashPosition >= POINTSEVEN){
							if(isdigit(text[_slashPosition + POINTFIVE]) && isdigit(text[_slashPosition + POINTSIX])){
								year = stoi(text.substr((_slashPosition + POINTTHREE), POINTFOUR));
								endPosition = POINTEIGHT;
							}
						}
					}
				}
				else{ 
					// check if day is 2 digits: xx/x/xx or xx/x/xxxx
					if(_slashPosition + POINTFOUR <= text.size() - POINTONE){
						if(isdigit(text[_slashPosition - POINTTWO])){
							day = stoi(text.substr((_slashPosition - POINTTWO), POINTTWO));
							startPosition = _slashPosition - POINTTWO;
							endPosition = POINTSEVEN;
						}
					}
					// check if year is 4 digits: xx/x/xxxx or x/x/xxxx
					if(_slashPosition + POINTSIX <= text.size() - POINTONE){
						if(text.size() - _slashPosition >= POINTSEVEN){
							if(isdigit(text[_slashPosition + POINTFIVE]) && isdigit(text[_slashPosition + POINTSIX])){
								year = stoi(text.substr((_slashPosition + POINTTHREE), POINTFOUR));
								if(isdigit(text[_slashPosition - POINTTWO]))
									endPosition = POINTNINE;
								else
									endPosition = POINTEIGHT;
							}
						}
					}
				}
				_date = text.substr(startPosition, endPosition);
				return true;
			}
			// date format: 1/11/11 or 11/11/11 or 1/11/1111 or 11/11/1111
			else if(_slashPosition + POINTFIVE <= text.size() - POINTONE){
				if(text.size() - _slashPosition >= POINTSIX){
					if(isdigit(text[_slashPosition - POINTONE]) && isdigit(text[_slashPosition + POINTONE]) && isdigit(text[_slashPosition + POINTTWO]) && text[_slashPosition + POINTTHREE] == SLASHCODE && isdigit(text[_slashPosition + POINTFOUR]) && isdigit(text[_slashPosition + POINTFIVE])){
						day = stoi(text.substr((_slashPosition - POINTONE), POINTONE));
						month = stoi(text.substr((_slashPosition + POINTONE), POINTTWO));
						year = stoi(text.substr((_slashPosition + POINTFOUR), POINTTWO));
						startPosition = _slashPosition - POINTONE;
						endPosition = POINTSEVEN;

						if(_slashPosition == POINTONE){
							// check if year is written as 4 digits: x/xx/xxxx
							if(_slashPosition + POINTSEVEN <= text.size() - POINTONE){
								if(text.size() - _slashPosition >= POINTEIGHT){
									if(isdigit(text[_slashPosition + POINTSIX]) && isdigit(text[_slashPosition + POINTSEVEN])){
										year = stoi(text.substr((_slashPosition + POINTFOUR), POINTFOUR));
										endPosition = POINTNINE;
									}
								}
							}
						}
						else{ 
							// check if day is 2 digits: xx/xx/xx or xx/xx/xxxx
							if(_slashPosition + POINTFIVE <= text.size() - POINTONE){
								if(isdigit(text[_slashPosition - POINTTWO])){
									day = stoi(text.substr((_slashPosition - POINTTWO), POINTTWO));
									startPosition = _slashPosition - POINTTWO;
									endPosition = POINTEIGHT;
								}
							}
							// check if year is 4 digits: xx/xx/xxxx or x/xx/xxxx
							if(_slashPosition + POINTSEVEN <= text.size() - POINTONE){
								if(text.size() - _slashPosition >= POINTEIGHT){
									if(isdigit(text[_slashPosition + POINTSIX]) && isdigit(text[_slashPosition + POINTSEVEN])){
										year = stoi(text.substr((_slashPosition + POINTFOUR), POINTFOUR));
										if(isdigit(text[_slashPosition - POINTTWO]))
											endPosition = POINTTEN;
										else
											endPosition = POINTNINE;
									}
								}
							}
						}
						_date = text.substr(startPosition, endPosition);
						return true;
					}
				}
			}
		}
		text = text.substr((_slashPosition + POINTONE), (text.size() - (_slashPosition + POINTONE)));
		getIndicators(text);
	}
	return false;
}

bool LogicDetailParser::checkDate(int day, int month, int year){
	int currentYear, currentMonth, currentDay, days;
	retrieveDate(currentYear, currentMonth, currentDay);

	switch (month){
	case POINTONE: case POINTTHREE: case POINTFIVE: case POINTSEVEN: case POINTEIGHT: case POINTTEN: case POINTTWELVE:
		days = THREEONEDAYS;
		break;
	case POINTFOUR: case POINTSIX: case POINTNINE: case POINTELEVEN:
		days = THREEZERODAYS;
		break;
	case POINTTWO: 
		if(((year % POINTFOUR == POINTZERO) && (year % HUNDRED != POINTZERO))||(year % FOURHUNDRED == POINTZERO))
			days = TWONINEDAYS;
		else
			days = TWOEIGHTDAYS;
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

void LogicDetailParser::retrieveDate(int& year, int& month, int& day){
	time_t now = time(POINTZERO);
	tm *ltm = localtime(&now);
	year = FIXEDYEAR + ltm->tm_year;
	month = POINTONE + ltm->tm_mon;
	day = ltm->tm_mday;
}

void LogicDetailParser::setTaskDate(Task& task, int day, int month, int year){
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

string LogicDetailParser::trimFoundText(string text, string textToTrim){
	string lowercaseText = textChangeLowercase(text);
	int startPosition = lowercaseText.find(textToTrim);
	if(startPosition != NOTSTATED){
		int endPosition = startPosition + (textToTrim.size() - POINTONE);
		string newText = text.substr(POINTZERO, startPosition) + text.substr((endPosition + POINTONE), text.size() - (endPosition + POINTONE));
		return newText;
	}
	else
		return _taskDescription;
}

int LogicDetailParser::findTime(Task& task, string text){
	int tempHours1 = NOTSTATED;
	int tempHours2 = NOTSTATED;
	int time;

	string stringTime = CANNOTFIND;
	string tempTime1 = CANNOTFIND;
	string tempTime2 = CANNOTFIND;

	if(!getTime(tempTime1, tempTime2, tempHours1, tempHours2))
		return false;

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

	if(!getTime(tempTime1, tempTime2, tempHours1, tempHours2))
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

bool LogicDetailParser::getTime(string& tempTime1, string& tempTime2, int& tempHours1, int& tempHours2){
	int hoursTimeCheck;
	int symbolledTimeCheck;
	int meridiemTimeCheck;
	int hours;
	string lowercaseText = textChangeLowercase(_taskDescription);
	getIndicators(lowercaseText);

	hoursTimeCheck = getHoursTime(lowercaseText, hours);
	if(hoursTimeCheck == ERROR)
		return false;
	else if(hoursTimeCheck == FOUND){
		tempHours1 = hours;
		tempTime1 = _time;
		_taskDescription = trimFoundText(_taskDescription, _time);
	}

	lowercaseText = textChangeLowercase(_taskDescription);
	getIndicators(lowercaseText);

	symbolledTimeCheck = getSymbolledTime(lowercaseText, hours);
	if(symbolledTimeCheck == ERROR)
		return false;
	else if(symbolledTimeCheck == FOUND){
		tempHours2 = hours;
		tempTime2 = _time;
		_taskDescription = trimFoundText(_taskDescription, _time);
	}

	if(symbolledTimeCheck == NOTFOUND){
		lowercaseText = textChangeLowercase(_taskDescription);
		getIndicators(lowercaseText);

		meridiemTimeCheck = getMeridiemTime(lowercaseText, hours);
		if(meridiemTimeCheck == ERROR)
			return false;
		else if(meridiemTimeCheck == FOUND){
			tempHours2 = hours;
			tempTime2 = _time;
			_taskDescription = trimFoundText(_taskDescription, _time);
		}
	}
	return true;
}

int LogicDetailParser::getHoursTime(string text, int& hours){
	if(parserHoursTime(text, hours)){
		if(!checkTime(hours))
			return ERROR;
		return FOUND;
	}
	else
		return NOTFOUND;
}

bool LogicDetailParser::parserHoursTime(string text, int& hours){
	while(_hrsPosition != NOTSTATED){
		if(_hrsPosition < POINTFOUR){}
		else if(isdigit(text[_hrsPosition - POINTFOUR]) && isdigit(text[_hrsPosition - POINTTHREE]) && isdigit(text[_hrsPosition - POINTTWO]) && isdigit(text[_hrsPosition - POINTONE])){
			hours = stoi(text.substr((_hrsPosition - POINTFOUR), POINTFOUR));
			_time = text.substr((_hrsPosition - POINTFOUR), POINTSEVEN);
			return true;
		}
		else if(_hrsPosition >= POINTFIVE){
			if(isdigit(text[_hrsPosition - POINTFIVE]) && isdigit(text[_hrsPosition - POINTFOUR]) && isdigit(text[_hrsPosition - POINTTHREE]) && isdigit(text[_hrsPosition - POINTTWO]) && (_hrsPosition - POINTONE) == SPACECODE){
				hours = stoi(text.substr((_hrsPosition - POINTFIVE), POINTFOUR));
				_time = text.substr((_hrsPosition - POINTFIVE), POINTEIGHT);
				return true;
			}
		}

		text = text.substr((_hrsPosition + POINTONE), (text.size() - (_hrsPosition + POINTONE)));
		getIndicators(text);
	}
	return false;
}

int LogicDetailParser::getSymbolledTime(string text, int& hours){
	string meridiem;
	int minutes;
	if(parserSymbolledTime(text, meridiem, hours, minutes)){
		if(meridiem == AM){
			if(hours == TWELVEHOURS)
				hours = POINTZERO;
			if(hours > TWELVEHOURS)
				return ERROR;
		}
		if(meridiem == PM)
			if(hours != TWELVEHOURS)
				hours += TWELVEHOURS;
		hours = hours * HUNDRED + minutes;
		if(!checkTime(hours))
			return ERROR;
		return FOUND;
	}
	return NOTFOUND;
}

bool LogicDetailParser::parserSymbolledTime(string text, string& meridiem, int& hours, int& minutes){

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
					if(text[meridiemPosition - POINTONE] == SPACECODE)
						_time = text.substr((pointPosition - POINTONE), POINTSEVEN);
					else
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
						if(text[meridiemPosition - POINTONE] == SPACECODE)
							_time = text.substr((pointPosition - POINTTWO), POINTEIGHT);
						else
							_time = text.substr((pointPosition - POINTTWO), POINTSEVEN);
						return true;
				}
				else if(isdigit(text[pointPosition - POINTONE]) && isdigit(text[pointPosition + POINTONE]) && isdigit(text[pointPosition + POINTTWO])){
					hours = stoi(text.substr((pointPosition - POINTTWO), POINTTWO));
					minutes = stoi(text.substr((pointPosition + POINTONE), POINTTWO));
					if(text[meridiemPosition - POINTONE] == SPACECODE)
						_time = text.substr((pointPosition - POINTONE), POINTSEVEN);
					else
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

int LogicDetailParser::getMeridiemTime(string text, int& hours){
	string meridiem;
	if(parserMeridiemTime(text, meridiem, hours)){
		if(meridiem == AM){
			if(hours == TWELVEHOURS)
				hours = POINTZERO;
			if(hours > TWELVEHOURS)
				return ERROR;
		}
		if(meridiem == PM)
			if(hours != TWELVEHOURS)
				hours += TWELVEHOURS;
		hours *= HUNDRED;
		if(!checkTime(hours))
			return ERROR;
		return FOUND;
	}
	return NOTFOUND;
}

bool LogicDetailParser::parserMeridiemTime(string text, string& meridiem, int& hours){
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

bool LogicDetailParser::checkTime(int time){
	if(time % HUNDRED < MAXMINUTES && time / HUNDRED < MAXHOURS)
		return true;
	else
		return false;
}

void LogicDetailParser::setTaskTime(Task& task, int startHours, int endHours){
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

void LogicDetailParser::removeUnwantedText(){
	bool spaceCheck = false;
	while(!spaceCheck){
		while(_taskDescription.size() != POINTZERO && (_taskDescription[POINTZERO] == SPACECODE || _taskDescription[_taskDescription.size() - POINTONE] == SPACECODE)){
			if(_taskDescription[POINTZERO] == SPACECODE)
				_taskDescription = _taskDescription.substr(POINTONE, (_taskDescription.size() - POINTONE));
			if(_taskDescription.size() >= POINTONE){
				if(_taskDescription[_taskDescription.size() - POINTONE] == SPACECODE)
					_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTONE));
			}
		}

		spaceCheck = true;

		if(_taskDescription.find("to") == POINTZERO){
			_taskDescription = _taskDescription.substr(POINTTWO, (_taskDescription.size() - POINTTWO));
			spaceCheck = false;
		}
		if(_taskDescription.size() >= POINTTWO){
			if(_taskDescription.substr((_taskDescription.size() - POINTTWO), POINTTWO) == "to"){
				_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTTWO));
				spaceCheck = false;
			}
		}

		if(_taskDescription.find("on") == POINTZERO){
			_taskDescription = _taskDescription.substr(POINTTWO, (_taskDescription.size() - POINTTWO));
			spaceCheck = false;
		}
		if(_taskDescription.size() >= POINTTWO){
			if(_taskDescription.substr((_taskDescription.size() - POINTTWO), POINTTWO) == "on"){
				_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTTWO));
				spaceCheck = false;
			}
		}

		if(_taskDescription.find("at") == POINTZERO){
			_taskDescription = _taskDescription.substr(POINTTWO, (_taskDescription.size() - POINTTWO));
			spaceCheck = false;
		}
		if(_taskDescription.size() >= POINTTWO){
			if(_taskDescription.substr((_taskDescription.size() - POINTTWO), POINTTWO) == "at"){
				_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTTWO));
				spaceCheck = false;
			}
		}

		if(_taskDescription.find("from") == POINTZERO){
			_taskDescription = _taskDescription.substr(POINTFOUR, (_taskDescription.size() - POINTTWO));
			spaceCheck = false;
		}
		if(_taskDescription.size() >= POINTFOUR){
			if(_taskDescription.substr((_taskDescription.size() - POINTFOUR), POINTFOUR) == "from"){
				_taskDescription = _taskDescription.substr(POINTZERO, (_taskDescription.size() - POINTFOUR));
				spaceCheck = false;
			}
		}
	}
}

void LogicDetailParser::setDate(Task& task){
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