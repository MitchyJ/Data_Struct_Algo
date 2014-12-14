#include "MainGUI.h"
//#include "stdafx.h"
//v0.2.1
//using namespace System;
//using namespace System ::Windows::Forms;
using namespace CataList;

[STAThreadAttribute]
int main(array<System::String^>^ arg){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	//MainGUI::MainGUI form;
	Application::Run(gcnew MainGUI());
	return 0;
}

System::Void MainGUI::textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e){
	String ^ userInput =textBox1->Text;
	string stdStringInput;
	vector<int> foundPosition;

	if(e->KeyCode == Keys::Enter && userInput->Length!=0){
		MarshalString(userInput,stdStringInput);
		parser(stdStringInput);
	}
}

void MainGUI::parser(string input){
	string op;
	string taskDetails;
	int positionOfFirstSpace= 0;

	positionOfFirstSpace = input.find(" ");
	if(positionOfFirstSpace == NOWHITESPACE)
	{
		label3->BackColor=System::Drawing::Color::Black;
		input = convertLowercase(input);
		if(input=="display")
		{
			_list = new TaskList();
			if(_logic->displayTask(*_list) && !(_list->checkEmpty()))
			{ 
				showData(*_list);
			}
			else
			{

				label3->BackColor=System::Drawing::Color::Gray;
				label3->Text = "CataList is currently empty!";
			}
		}
		else if(delFlag==true) //user entered choice of task to delete when there is multiple instances from search 
		{   
			int choice = stoi(input);	

			if(choice>0 && choice<=taskPosition->size()){
				_logic->deleteAtPos(taskPosition->at(choice-1));
				delFlag = false; 
				label3->BackColor=System::Drawing::Color::BlueViolet;
				label3->Text="Task has been deleted";
				_list = new TaskList(); //initiation
				updTable(*_list);
			}
			else 
			{
				label3->BackColor=System::Drawing::Color::Gray;
				label3->Text="Task was not deleted";
			}
		}
		//else{
		//	label3->BackColor=System::Drawing::Color::Gray;
		//	label3->Text="Input is not valid";
		//}

		else if(input=="undo"){

			if(_logic->undoParser()){
				_list = new TaskList(); 
				updTable(*_list);
				label3->BackColor=System::Drawing::Color::BlueViolet;
				label3->Text="Operation has been undone";
			}
			else{ 
				label3->BackColor=System::Drawing::Color::Gray;
				label3->Text="No operation to be undone";
			}
		}
		else if(input=="redo"){
			if(_logic->redoParser()){
				_list = new TaskList();
				updTable(*_list);
				label3->BackColor=System::Drawing::Color::BlueViolet;
				label3->Text="Operation has been redone";
			}
			else{ 
				label3->BackColor=System::Drawing::Color::Gray;
				label3->Text="No operation to be redone";
			}
		}
		else if(input=="help" ||input=="help "||input.find("help")==0){
			label3->Text="What would you like to do?";
			label1->Text="Operations available: Add,Delete,Update,Find,Undo,Redo,Display";
		}
		else if(input=="exit" || input=="exit " ||input=="quit")
			Application::Exit();
		else
		{   
			label1->Text="Operations available: Add,Delete,Update,Find,Undo,Redo,Display";
			label3->BackColor=System::Drawing::Color::Red;
			label3->Text="Invalid command!";
		}

	}

	else{
		label3->BackColor=System::Drawing::Color::Black;
		op=input.substr(0,positionOfFirstSpace); // extracting operation type from user input 
		taskDetails=input.substr(positionOfFirstSpace,input.length()); // extracting the details from user input 
		op=convertLowercase(op);
		if(op=="add" || op=="+"){ 
			if(_logic->addTask(taskDetails)){
				_list = new TaskList(); 
				updTable(*_list);
				label3->BackColor=System::Drawing::Color::BlueViolet;
				label3->Text = "Task has been successfully added";
			}
			else{
				label1->Text="To add a new task: key in 'Add''Task details'; For example, 'Add dinner with family 1000hrs to 1200hrs' or '+ assignment submission 1200hrs'";
				label3->BackColor=System::Drawing::Color::Gray;
				label3->Text = "Task has not been added";
			}
		}
		else if(op=="delete"||op=="-"){  
			_list = new TaskList();
			taskPosition = new vector<int>();
			int result = _logic->deleteTask(taskDetails,*taskPosition,*_list);
			if( result == ONEMATCHFOUND) {// only 1 instance of search result 
				//_list = new TaskList(); //try
				updTable(*_list);
				label3->BackColor=System::Drawing::Color::BlueViolet;
				label3->Text="Task has been successfully deleted";
			}
			else if(result==MULTIPLEMATCHFOUND){ //search return multiple results
				showData(*_list);
				delFlag=true;
				label3->Text="Please select Task to be deleted by entering index number of task";
			}
			else{ // search return zero 
				label1->Text="To delete task in list: enter delete 'task to be deleted'; For example: 'delete assignment' or 'delete as'";
				label3->BackColor=System::Drawing::Color::Gray;
				label3->Text="Task is not found";
			}
		}
		else if(op=="edit"||op=="update"||op=="change"){

			if(_logic->updateTask(taskDetails)){
				_list = new TaskList();
				updTable(*_list);
				label3->BackColor=System::Drawing::Color::BlueViolet;
				label3->Text = "Task has been successfully updated";
			}
			else{
				label1->Text="To update a task: key in 'update''Task details'; For example, 'update lunch - from 1000hrs to 1200hrs' or 'change test - exam 1200hrs'";
				label3->BackColor=System::Drawing::Color::Gray;
				label3->Text = "Task has not been updated";
			}
		}
		else if(op=="search"||op=="find"){
			_list = new TaskList();
			if(_logic->searchTask(taskDetails,*_list)){

				int matchFound=_list->getSize();
				showData(*_list);
				label3->BackColor=System::Drawing::Color::BlueViolet;
				label3->Text=matchFound.ToString()+ " matches found";
			}
			else{
				label3->BackColor=System::Drawing::Color::Red;
				label3->Text="No matches found!";
			}
		}
		//else if(op=="undo "){
		//	if(_logic->undoParser()){
		//		_list = new TaskList(); //try
		//		updTable(*_list);
		//		label3->BackColor=System::Drawing::Color::BlueViolet;
		//		label3->Text="Operation has been undone";
		//	}
		//	else{ 
		//		label3->BackColor=System::Drawing::Color::Gray;
		//		label3->Text="No operation to be undone";
		//	}
		//}
		//else if(op=="redo "){
		//	if(_logic->redoParser()){
		//		_list = new TaskList(); //try
		//		updTable(*_list);
		//		label3->BackColor=System::Drawing::Color::BlueViolet;
		//		label3->Text="Operation has been redone";
		//	}
		//	else{ 
		//		label3->BackColor=System::Drawing::Color::Gray;
		//		label3->Text="No operation to be redone";
		//	}
		//}
		else if(op=="help"|| op=="help "){
			label3->Text="What would you like to do?";
			label1->Text="Operations available: Add,Delete,Update,Find,Undo,Redo,Display";
		}
		else if(op=="exit" || op=="exit "){
			Application::Exit();
		}
		else{  
			label1->Text="Operations available: Add,Delete,Update,Find,Undo,Redo,Display";
			label3->BackColor=System::Drawing::Color::Blue;
			label3->Text="Invalid command!";
		}
	}


}
string MainGUI::convertLowercase(string text){
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

void MainGUI::updTable(TaskList list){
	if(_logic->displayTask(*_list))
	{ 
		showData(*_list);
	}
	else
	{
			dataGridView1->Rows->Clear(); // from here extract to method,pass*_list into method
	label3->Text = "displaying...";
	BL= gcnew ArrayList;
	int listSize = _list->getSize();
	for(int i=0;i<listSize;i++)
	{
		_task = new Task();
		_list->getFrontTask(*_task);
		int test1, test4;
		test1 = _task->getStartDay();
		test4 = _task->getEndDay();

		//if(test1 == -1 && test4 == -1){
		//	array<String^>^row = gcnew array<String^>{
		//		gcnew String((i+1).ToString()),
		//			gcnew String(_task->getTaskDescription().c_str()),
		//			gcnew String(""),
		//			gcnew String(""),
		//			gcnew String(""),
		//			gcnew String(""),
		//			gcnew String("FLOATING TASK")
		//	};
		//	dataGridView1->Rows->Add(row);
		//}
		//else{
		array<String^>^row = gcnew array<String^>{
			gcnew String((i+1).ToString()),
				gcnew String("Empty"),
				gcnew String(" "),
				gcnew String(" "),
				gcnew String(" "),
				gcnew String(" "),
				gcnew String(" ")
				//"Meatloaf","Main Dish","ground beef","**"
		};
		dataGridView1->Rows->Add(row);
		/*	}*/
		//dataGridView1->Rows->Add(row);
		_list->removeFrontTask();

	}
	dataGridView1->Height=listSize * dataGridView1->Rows[0]->Height + dataGridView1->ColumnHeadersHeight;//to here

		label3->BackColor=System::Drawing::Color::Yellow;
		label3->Text = "CataList is currently empty!";
	}
}

void MainGUI::showData(TaskList list){
	dataGridView1->Rows->Clear(); // from here extract to method,pass*_list into method
	label3->Text = "displaying...";
	BL= gcnew ArrayList;
	int listSize = _list->getSize();
	for(int i=0;i<listSize;i++)
	{
		_task = new Task();
		_list->getFrontTask(*_task);
		int test1, test4;
		test1 = _task->getStartDay();
		test4 = _task->getEndDay();

		//if(test1 == -1 && test4 == -1){
		//	array<String^>^row = gcnew array<String^>{
		//		gcnew String((i+1).ToString()),
		//			gcnew String(_task->getTaskDescription().c_str()),
		//			gcnew String(""),
		//			gcnew String(""),
		//			gcnew String(""),
		//			gcnew String(""),
		//			gcnew String("FLOATING TASK")
		//	};
		//	dataGridView1->Rows->Add(row);
		//}
		//else{
		array<String^>^row = gcnew array<String^>{
			gcnew String((i+1).ToString()),
				gcnew String(_task->getTaskDescription().c_str()),
				gcnew String(_task->getStartDay().ToString()+"/"+_task->getStartMonth().ToString()+"/"+_task->getStartYear().ToString()),
				gcnew String(_task->getStartTime().ToString()),
				gcnew String(_task->getEndDay().ToString()+"/"+_task->getEndMonth().ToString()+"/"+_task->getEndYear().ToString()),
				gcnew String(_task->getEndTime().ToString()),
				gcnew String(_task->getStatus().c_str())
				//"Meatloaf","Main Dish","ground beef","**"
		};
		dataGridView1->Rows->Add(row);
		/*	}*/
		//dataGridView1->Rows->Add(row);
		_list->removeFrontTask();

	}
	dataGridView1->Height=listSize * dataGridView1->Rows[0]->Height + dataGridView1->ColumnHeadersHeight;//to here
}

//void MainGUI::showData(TaskList list){
//	dataGridView1->Rows->Clear(); // from here extract to method,pass*_list into method
//	label3->Text = "displaying...";
//	BL= gcnew ArrayList;
//	int listSize = _list->getSize();
//	for(int i=0;i<listSize;i++)
//	{
//		_task = new Task();
//		_list->getFrontTask(*_task);
//		array<String^>^row = gcnew array<String^>{
//			gcnew String((i+1).ToString()),
//				gcnew String(_task->getTaskDescription().c_str()),
//				gcnew String(_task->getStartDay().ToString()+"/"+_task->getStartMonth().ToString()+"/"+_task->getStartYear().ToString()),
//				gcnew String(_task->getStartTime().ToString()),
//				gcnew String(_task->getEndDay().ToString()+"/"+_task->getEndMonth().ToString()+"/"+_task->getEndYear().ToString()),
//				gcnew String(_task->getEndTime().ToString()),
//				gcnew String(_task->getStatus().c_str())
//				//"Meatloaf","Main Dish","ground beef","**"
//		};
//		dataGridView1->Rows->Add(row);
//		_list->removeFrontTask();
//
//	}
//	dataGridView1->Height=listSize * dataGridView1->Rows[0]->Height + dataGridView1->ColumnHeadersHeight;//to here
//}

System::Void MainGUI::listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e){

	//listViewItem = gcnew Windows::Forms::ListViewItem(this->textBox1->Text);
	//

	////listViewItem->Name;
	//this->listView1->Items->Add(this->listViewItem);

}