#include "Logic.h"
//v0.2.1
const string Logic::STARTPROGRAM = "PROGRAM START";
const string Logic::LOGTASK = " ";
const string Logic::ADD = "add";
const string Logic::DELETE = "delete";
const string Logic::EDIT = "change";
const string Logic::DONE = "done";
const string Logic::SEARCH = "search";
const string Logic::DISPLAY = "display";
const string Logic::UNDO = "undo";
const string Logic::REDO = "redo";
const string Logic::EXIT = "exit";
const string Logic::UPDATE = "update";
const string Logic::SHOW = "show";
const string Logic::FIND = "find";
const string Logic::COMPLETE = "complete";

//void Logic::main(){
//	_io.welcomeMessage();
//	_log.printTaskToLog(STARTPROGRAM, LOGTASK, true);
//	
//	_fileStorage.readFile(_taskList);
//	do{
//		try{
//			_operation = _io.requestInput();
//			//	try{
//			if(userCommand(_operation))
//				_userInput = _io.getTaskDetails();
//			else
//				_userInput = _io.getInvalidInput();
//			//				if(((_userInput.length()==0)||_userInput==" ") && (_operation!="display" && _operation!="exit" && _operation!="undo"))
//			//		throw "error";
//			//}
//			//catch(const char* error)
//			//{
//			//	cerr << "Task details are not entered!Please retry."<<endl;
//			//}
//
//			if(_operation == ADD){
//				if(_add.newTaskParser(_taskList, _task,_userInput, _position)){
//					//_position = _taskList.getSize() - 1;
//					//		_assertion.intAssert(_position);		//assertion
//					//		_assertion.stringAssert(_operation);	//assertion
//					_redo.task.clearList();
//					_undo.addToList(_task, _operation, _position);
//					_fileStorage.updateFile(_taskList);
//					//fileStorage.addTaskToFile(_task, _position);
//					_io.successMessageForAdd();
//					_log.printTaskToLog(_operation, _userInput, true);
//				}
//				else{
//					_io.errorMessageForAdd();
//					_log.printTaskToLog(_operation, _userInput, false);
//				}
//			}
//
//			else if (_operation == DELETE){
//				if(_delete.delTask(_taskList,_task, _userInput,_position)){
//					_redo.task.clearList();					
//					_undo.addToList(_task, _operation, _position);
//					_fileStorage.updateFile(_taskList);
//					_io.successMessageForDelete();
//					_log.printTaskToLog(_operation, _userInput, true);
//				}
//				else{
//					_io.errorMessageForDelete();
//					_log.printTaskToLog(_operation, _userInput, false);
//				}
//			}
//			else if (_operation == EDIT){
//				int oldPosition, newPosition;
//				Task newTaskInfo, oldTaskInfo;
//				if(_edit.changeTaskInfo(_taskList, newTaskInfo, oldTaskInfo, _userInput, _operation, oldPosition, newPosition)){
//					_redo.task.clearList();
//					_undo.addToList(oldTaskInfo, _operation, oldPosition);
//					_undo.addToList(newTaskInfo, _operation, newPosition);
//					_fileStorage.updateFile(_taskList);
//					_log.printTaskToLog(_operation, _userInput, true);
//					_io.successMessageForUpdate();
//				}
//				else{
//					_io.errorMessageForUpdate();
//					_log.printTaskToLog(_operation, _userInput, false);
//				}
//			}
//			else if (_operation == DONE){
//				if(_done.findDoneTask(_taskList, _task, _userInput, _position))	{}	// error and success message from ui is needed
//				//_undo.addToUndoList(_task, _operation, _position);
//				//fileStorage.updateFile(_taskList);
//				//fileStorage.completeTask(_task);
//				//_io.successMessageForDone();
//				else		{}			// *** <<< REMOVE BOTH CURLY BRACKET ^^^^^ ***
//				//_io.errorMessageForDone();
//			}
//			else if (_operation == SEARCH){
//				if(!searchTask(_userInput))
//					_io.errorMessageForTaskSearch();
//
//			}
//			else if (_operation == DISPLAY){
//				if(!_io.displayTask(_taskList))
//					_log.printTaskToLog(_operation, _userInput, true);
//
//			}
//
//			else if(_operation == UNDO){
//				if(undoParser()){
//					_io.successMessageForUndo();
//					_log.printTaskToLog(_operation, _userInput, true);
//				}
//				else{
//					_io.errorMessageForUndo();
//					_log.printTaskToLog(_operation, _userInput, false);
//				}
//
//			}
//			else if(_operation == REDO){
//				if(redoParser()){
//					cout<<"YAY!"<<endl;
//					_log.printTaskToLog(_operation, _userInput, true);
//				}
//				else{
//					cout<<"NOO!"<<endl;
//					_log.printTaskToLog(_operation, _userInput, false);
//				}
//			}
//			else if (_operation == EXIT){
//				_operation = EXIT;
//				_log.printTaskToLog(_operation, _userInput, true);
//				_io.successMessageForExit();
//			}
//
//			if(_operation != "+" && _operation != "-" && _operation != ADD &&
//				_operation != DELETE &&_operation != SEARCH && _operation != FIND && _operation != EDIT &&
//				_operation != UPDATE && _operation != SHOW && _operation != EXIT && _operation != DISPLAY && _operation != UNDO)
//				throw (_operation.c_str());
//
//			//if(((_userInput.length()==0)||_userInput==" ") && (_operation!="display" && _operation!="exit" && _operation!="undo"))
//			//	throw _userInput.length();
//		}
//		//	catch(char* operation)
//		//{
//		//cerr << operation<<" is not a valid operation!Please retry."<<endl;
//		//}
//		//catch(int error)
//		//{
//		//	cerr << error<<" is not a valid operation!Please retry."<<endl;
//		//}
//		catch(char const* operation)
//		{
//			cerr << operation <<" is not a valid input!Please re-enter."<<endl;
//		}
//		catch(...)
//		{
//			cout<<"unknown error occurred!"<<endl;
//		}
//		//else
//		//_io.invalidCommand();
//	}while(_operation != EXIT);
//}


void Logic:: init(){

   _fileStorage.readFile(_taskList);

}

bool Logic::addTask(string input){
	_task.setTask(0,0,0,0,0,0,0,0,"","","",false,false);
	//UI _ui;
	//_ui.displayTask(_taskList);
	_operation = ADD;
	if(_add.newTaskParser(_taskList, _task,input, _position)){
		//_position = _taskList.getSize() - 1;
		//		_assertion.intAssert(_position);		//assertion
		//		_assertion.stringAssert(_operation);	//assertion
		_redo.task.clearList();
		_undo.addToList(_task, _operation, _position);
		_fileStorage.addTaskToFile(_task, _position);
		_log.printTaskToLog(_operation, input, true);
		return true;
	}
	else{
		_log.printTaskToLog(_operation, input, false);
		return false;
	}
}

bool Logic::updateTask(string userInput){
	int oldPosition, newPosition;
	Task newTaskInfo, oldTaskInfo;
	_operation = EDIT;
	if(_edit.changeTaskInfo(_taskList, newTaskInfo, oldTaskInfo, userInput, _operation, oldPosition, newPosition)){
		_redo.task.clearList();
		_undo.addToList(oldTaskInfo, _operation, oldPosition);
		_undo.addToList(newTaskInfo, _operation, newPosition);
		_fileStorage.updateFile(_taskList);
		_log.printTaskToLog(_operation, userInput, true);
		return true;
		//_io.successMessageForUpdate();
	}
	else{
		//_io.errorMessageForUpdate();
		_log.printTaskToLog(_operation, userInput, false);
		return false;
	}
}

int Logic::deleteTask(string input,vector<int>& taskPosition,TaskList& searchResult){
	string operation = "delete";
	int result = _delete.delTask(_taskList,_task, input,_position,taskPosition,searchResult);
	if(result==0){ // only 1 search result
		_redo.task.clearList();
		_undo.addToList(_task, operation, _position);
		_fileStorage.updateFile(_taskList);
		//_io.successMessageForDelete();
		_log.printTaskToLog(operation, input, true);
		return 0;
	}
	else if(result==1)
	{
		return 1;
	}
	else{
		//_io.errorMessageForDelete();
		_log.printTaskToLog(_operation, _userInput, false);
		return -1;
	}
}

void Logic::deleteAtPos(int pos){
	string operation = DELETE;
	_redo.task.clearList();
	_undo.addToList(_task, operation, pos);
	_delete.deleteAtPos(_taskList,_task,pos);
	_fileStorage.updateFile(_taskList);
	//_log.printTaskToLog(operation, input, true);
}

bool Logic::searchTask(string userInput, TaskList& searchResult){
	//TaskList searchResult;
	vector<int> taskFoundPosition;

	if(_search.searchTaskList(_taskList, searchResult, taskFoundPosition, userInput)){
		//	_io.displayTask(searchResult);
		return true;
	}
	else
		return false;
}

bool Logic::undoParser(){
	if(_undo.getLatestInfo(_task, _operation, _position)){
		_redo.task.addToList(_task, _operation, _position);
		//_assertion.intAssert(_position);	//assertion
		if(_operation == ADD){
			_delete.deleteAddedTask(_taskList, _task, _position);
			_fileStorage.updateFile(_taskList);
		}
		else if(_operation == DELETE){
			_add.addDeletedTask(_taskList, _task, _position);
			_fileStorage.updateFile(_taskList);
		}
		else if(_operation == EDIT){
			_delete.deleteAddedTask(_taskList, _task, _position); //delete new edit
			if(	_undo.getLatestInfo(_task, _operation, _position)){// retrieve old change
				_redo.task.addToList(_task, _operation, _position);//add old change to redo
				_add.addDeletedTask(_taskList, _task, _position);//add back old item
			}
			_fileStorage.updateFile(_taskList);
		}
		else if(_operation == DONE){}
		//_edit.addDeletedTask(_taskList, _task, _position);
		return true;
	}
	else
		return false;
}

bool Logic::redoParser(){
	if(_redo.task.getLatestInfo(_task, _operation, _position)){
		_undo.addToList(_task, _operation, _position);
		if(_operation == DELETE){
			_delete.deleteAddedTask(_taskList, _task, _position);
			_fileStorage.updateFile(_taskList);
		}
		else if(_operation == ADD){
			_add.addDeletedTask(_taskList, _task, _position);
			_fileStorage.updateFile(_taskList);
		}
		else if(_operation == EDIT){
			_delete.deleteAddedTask(_taskList, _task, _position);
			if(_redo.task.getLatestInfo(_task, _operation, _position)){
				_add.addDeletedTask(_taskList, _task, _position);
				_undo.addToList(_task, _operation, _position);
			}
			_fileStorage.updateFile(_taskList);
		}
		else if(_operation == DONE){}
		//_edit.addDeletedTask(_taskList, _task, _position);
		return true;
	}
	else
		return false;
}

bool Logic::userCommand(string& operation){
	operation = convertLowercase(operation);

	if(operation.find(ADDSIGN) == STARTPOSITION){
		operation = ADD;
		return true;
	}
	else if(operation.find(DELSIGN) == STARTPOSITION){
		operation = DELETE;
		return true;
	}
	else if (operation.find(ADD) == STARTPOSITION){
		return true;
	}
	else if(operation.find(DELETE) == STARTPOSITION){
		return true;
	}
	else if(operation.find(SEARCH) == STARTPOSITION){
		return true;
	}
	else if(operation.find(FIND) == STARTPOSITION){
		operation = SEARCH;
		return true;
	}
	else if(operation.find(EDIT) == STARTPOSITION){
		return true;
	}
	else if(operation.find(UPDATE) == STARTPOSITION){
		operation = EDIT;
		return true;
	}
	else if(operation.find(COMPLETE) == STARTPOSITION){
		operation = DONE;
		return true;
	}
	else if(operation.find(SHOW) == STARTPOSITION){
		operation = DISPLAY;
		return false;
	}
	else if(operation.find(UNDO) ==STARTPOSITION){
		operation=UNDO;
		return false;
	}
	else if(operation.find(REDO) ==STARTPOSITION){
		operation=REDO;
		return false;
	}
	else
		return false;
}

string Logic::convertLowercase(string text){
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

bool Logic::displayTask(TaskList& list){
	if(_taskList.checkEmpty())
		return false;
	else{
		list=_taskList;
		return true;
	}
}

bool Logic::statusUpdate(string input){
	string operation = "done";
	if(_done.findDoneTask(_taskList, _task, _userInput, _position))	{return true;}	// error and success message from ui is needed
	//_undo.addToUndoList(_task, _operation, _position);
	//fileStorage.updateFile(_taskList);
	//fileStorage.completeTask(_task);
	//_io.successMessageForDone();

	else		{return false;}			// *** <<< REMOVE BOTH CURLY BRACKET ^^^^^ ***
	//_io.errorMessageForDone();

}

//else if(_operation == REDO){
//	if(redoParser()){
//		cout<<"YAY!"<<endl;
//		_log.printTaskToLog(_operation, _userInput, true);
//	}
//	else{
//		cout<<"NOO!"<<endl;
//		_log.printTaskToLog(_operation, _userInput, false);
//	}
//}