#pragma once
//v0.2.1
#include <iostream>
#include <string>
#include <fstream>
#include "Logic.h"
#include "tasklist.h"
#include "task.h"
#include "storage.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>
#include <ctype.h>
#include <msclr\marshal_cppstd.h>

//using namespace std;
using namespace System;

namespace CataList {

	void MarshalString( String^ s, string& os ) 
	{
		using namespace Runtime::InteropServices;
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MainGUI : public System::Windows::Forms::Form
	{
	private:
		static const int NOWHITESPACE = -1;
		static const int ONEMATCHFOUND = 0;
		static const int MULTIPLEMATCHFOUND = 1;
		Task *_task;
		TaskList *_list;
		Logic *_logic;
		LogicAdd *_addTask;
		LogicDelete *_delTask;
		LogicSearch *_findTask;
		LogicUndo *_undoTask;
		LogicEdit *_editTask;
		String^ str;
		ArrayList^ BL; 
		vector<int> *taskPosition;
		bool delFlag;
		//int searchFlag;		//to indicate/keep track of the search mode
		//vector<int> *indexMap;	// for index mapping used during search (this is to avoid duplicate list to show in table)
		//String^ str;	//The search word
		//int sales;
		//int stock;
		//int index;
		//int prevSize;


	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  number;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  taskDesc;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  startDate;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  startTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  endDate;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  endTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  status;
	private: System::Windows::Forms::MonthCalendar^  monthCalendar1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;

			 //String alpha;

	public:
		MainGUI(void)
		{
			InitializeComponent();
			str = gcnew String("");
			//
			//TODO: Add the constructor code here
			//
			DateTime datetime = DateTime::Now ;
			this->label2->Text=datetime.ToString(); 
		}



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainGUI()
		{
			if (components)
			{
				delete components;
			}
		}
		System::Windows::Forms::ListViewItem^ listViewItem;
		//private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::TextBox^  textBox1;

	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::PictureBox^  pictureBox1;



	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		void parser(string);
		string convertLowercase(string);
		void showData(TaskList list);
		//void (TaskList list);
		void updTable(TaskList list);
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainGUI::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->number = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->taskDesc = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->startDate = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->startTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->endDate = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->endTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->status = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->monthCalendar1 = (gcnew System::Windows::Forms::MonthCalendar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(12) {L"add", L"delete ", L"display", 
				L"show", L"update", L"change ", L"undo", L"exit ", L"done ", L"search ", L"find ", L"redo"});
			this->textBox1->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Append;
			this->textBox1->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->textBox1->BackColor = System::Drawing::Color::Black;
			this->textBox1->ForeColor = System::Drawing::SystemColors::Window;
			this->textBox1->Location = System::Drawing::Point(16, 341);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(663, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainGUI::textBox1_KeyDown);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Black;
			this->label2->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label2->Location = System::Drawing::Point(691, 18);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"label2";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(-2, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(204, 72);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 9;
			this->pictureBox1->TabStop = false;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {this->number, 
				this->taskDesc, this->startDate, this->startTime, this->endDate, this->endTime, this->status});
			this->dataGridView1->Location = System::Drawing::Point(15, 48);
			this->dataGridView1->MaximumSize = System::Drawing::Size(679, 260);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->Size = System::Drawing::Size(664, 260);
			this->dataGridView1->TabIndex = 10;
			// 
			// number
			// 
			this->number->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->number->HeaderText = L"No.";
			this->number->Name = L"number";
			this->number->ReadOnly = true;
			this->number->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->number->Width = 30;
			// 
			// taskDesc
			// 
			this->taskDesc->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->taskDesc->HeaderText = L"Task Description";
			this->taskDesc->Name = L"taskDesc";
			this->taskDesc->ReadOnly = true;
			this->taskDesc->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->taskDesc->Width = 250;
			// 
			// startDate
			// 
			this->startDate->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->startDate->HeaderText = L"Start Date";
			this->startDate->Name = L"startDate";
			this->startDate->ReadOnly = true;
			this->startDate->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->startDate->Width = 70;
			// 
			// startTime
			// 
			this->startTime->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->startTime->HeaderText = L"Start Time";
			this->startTime->Name = L"startTime";
			this->startTime->ReadOnly = true;
			this->startTime->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->startTime->Width = 70;
			// 
			// endDate
			// 
			this->endDate->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->endDate->HeaderText = L"End Date";
			this->endDate->Name = L"endDate";
			this->endDate->ReadOnly = true;
			this->endDate->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->endDate->Width = 70;
			// 
			// endTime
			// 
			this->endTime->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->endTime->HeaderText = L"End Time";
			this->endTime->Name = L"endTime";
			this->endTime->ReadOnly = true;
			this->endTime->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->endTime->Width = 70;
			// 
			// status
			// 
			this->status->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->status->HeaderText = L"Status";
			this->status->Name = L"status";
			this->status->ReadOnly = true;
			this->status->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->status->Width = 80;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Black;
			this->label3->Font = (gcnew System::Drawing::Font(L"Bookman Old Style", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label3->Location = System::Drawing::Point(12, 324);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(174, 14);
			this->label3->TabIndex = 11;
			this->label3->Text = L"What would you like to do\?";
			// 
			// monthCalendar1
			// 
			this->monthCalendar1->BackColor = System::Drawing::SystemColors::ControlText;
			this->monthCalendar1->Location = System::Drawing::Point(690, 51);
			this->monthCalendar1->Name = L"monthCalendar1";
			this->monthCalendar1->TabIndex = 12;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->label1->Location = System::Drawing::Point(691, 217);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(210, 121);
			this->label1->TabIndex = 13;
			this->label1->Text = L"Welcome to CataList\r\n\r\n";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// MainGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(913, 391);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->monthCalendar1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Name = L"MainGUI";
			this->Text = L"CataList";
			this->Load += gcnew System::EventHandler(this, &MainGUI::MainGUI_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	private: System::Void MainGUI_Load(System::Object^  sender, System::EventArgs^  e){
				 _logic=new Logic();
				 _logic->init();
				 dataGridView1->Height=dataGridView1->ColumnHeadersHeight;
				 delFlag=false;
			 }
	private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	};
}

