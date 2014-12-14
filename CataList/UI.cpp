#include "UI.h"
//v0.2.1
string UI::requestInput(){
	cout << "\nWhat would you like to do?\n";
	cin >> userInput;
	return userInput;
}

string UI::requestUserChoice(){
	cout << "\nWhich task would you like to choose?\n";
	cin >> userChoice;
	return userChoice;
}

string UI::getTaskDetails(){
	getline(cin, userInput);
	return userInput;
}

string UI::getInvalidInput(){
	getline(cin, userInput);
	return userInput;
}

void UI::welcomeMessage(){
	cout<<"        *********************************************************\n";
	cout<<"	*                          ___    _                     *\n";            
	cout<<"	*   \\    /_ | _ _ ._ _  _   | _  /  _._|_ _.| o __|_    *\n";
	cout<<"	*    \\/\\/(/_|(_(_)| | |(/_  |(_) \\_(_| |_(_||_|_> |_    *\n";
	cout<<"        *********************************************************";
}

void UI::successMessageForAdd(){
	cout<<"Task has been successfully added to CataList!"<<endl;
}

void UI::errorMessageForAdd(){
	cout<<"Task was not added due to invalid entry.Please retry."<<endl;
}

void UI::successMessageForDelete(){
	cout<<"Task has been removed from CataList!"<<endl;
}

void UI::errorMessageForDelete(){
	cout<<"No task was deleted."<<endl;
}

void UI::successMessageForUpdate(){
	cout<<"Task has been updated!"<<endl;
}

void UI::errorMessageForUpdate(){
	cout<<"Task or date specified is invalid to be updated.Please retry."<<endl;
}

void UI::successMessageForUndo(){
	cout<<"Task has been undone!"<<endl;
}

void UI::errorMessageForUndo(){
	cout<<"There is no changes to be undone!"<<endl;
}

void UI::successMessageForTaskSearch(){
	cout<<"Task match is as follow: "<<endl;
}

void UI::errorMessageForTaskSearch(){
	cout<<"No match found!"<<endl;
}

void UI::successMessageForExit(){
	cout<<"Good Bye Jim!"<<endl;
}

void UI::successMessageForDisplay(){
	cout<<"Task(s) : "<<"\n"<<endl;
}

void displayMessage(string task){
	cout<<task<<" has been successfully added into CataList!"<<endl;
}

bool UI::displayTask(TaskList taskList){
	cout<<"MUHAHAHHAHA!"<<endl;
	Task displayFront;
	int i = 1;
	if(taskList.checkEmpty())
	{
		cout<<"CataList is currently empty."<<endl;
		return false;
	}
	else {
		successMessageForDisplay();
		while(!taskList.checkEmpty()){
			taskList.getFrontTask(displayFront);

			cout<<"Task "<<i<<":\nTASK STARTS ON "<<displayFront.getStartDay()<<"/"<<displayFront.getStartMonth()<<"/"<<displayFront.getStartYear()<<endl;
			cout<<"TIME : "<<displayFront.getStartTime()<<endl;
			cout<<"TASK ENDS ON "<<displayFront.getEndDay()<<"/"<<displayFront.getEndMonth()<<"/"<<displayFront.getEndYear()<<endl;
			cout<<"TIME : "<<displayFront.getEndTime()<<endl;
			cout<<"DESCRIPTION : "<<displayFront.getTaskDescription()<<endl;
			cout<<"STATUS : "<<displayFront.getStatus()<<endl<<endl;
			taskList.removeFrontTask();
			i++;
		}
		return true;
	}
}
