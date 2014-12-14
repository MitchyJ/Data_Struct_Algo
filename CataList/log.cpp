#include"log.h"
//v0.2.1
const string Log::SUCCESS = " SUCCESS";
const string Log::FAIL = " FAIL";
const string Log::LOGFILE = "Log.txt";
const string Log::SPACE = " ";
const string Log::COLON = ":";

void Log::printTaskToLog(string operation, string logTask, bool success){
	if (success == true)
		logTask = operation + logTask + SUCCESS;
	else 
		logTask = operation + logTask + FAIL;

	ofstream writeLog;
	writeLog.open(LOGFILE, ios::app);

	getDateAndTime(_year, _month, _date, _hour, _minute);

	if (writeLog.is_open()){
		writeLog<<_date<<_month<<_year<<SPACE<<_hour<<COLON<<_minute<<endl;
		writeLog<<logTask<<endl;
		writeLog.close();
	}

}

void Log::getDateAndTime(int& year, int& month, int& day, int& hour, int& minute){
	time_t now = time(ZERO);
	tm *localTime = localtime(&now);

	year = YEAROFFSET + localTime->tm_year;
	month = ONE + localTime->tm_mon;
	day = localTime->tm_mday;
	hour = localTime->tm_hour;
	minute = localTime->tm_min;
}
