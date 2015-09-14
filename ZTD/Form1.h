#pragma once

namespace ZTD {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			listen = true;
			cellColors = new unsigned char[40];
			for(int i=0; i<40; ++i)
				cellColors[i] = 0;
			listItems = gcnew array< System::Object^  >(8) {L"undug", L"green rupee", L"blue rupee", 
				L"red rupee", L"silver rupee", L"gold rupee", L"rupoor", L"bomb"};
			s = new solver(cellColors);

			InitializeComponent();
			
			comboBoxs = gcnew array< System::Windows::Forms::ComboBox^ >(40);
			labels = gcnew array< System::Windows::Forms::Label^ >(40);
			panels = gcnew array< System::Windows::Forms::Panel^ >(40);
			for(int i=0; i<40; ++i){
				comboBoxs[i] = (gcnew System::Windows::Forms::ComboBox());
				comboBoxs[i]->Dock = System::Windows::Forms::DockStyle::Bottom;
				comboBoxs[i]->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				comboBoxs[i]->Items->AddRange(listItems);
				comboBoxs[i]->SelectedIndex = 0;
				comboBoxs[i]->Tag = i;
				comboBoxs[i]->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboListener);
				labels[i] = (gcnew System::Windows::Forms::Label());
				labels[i]->Dock = System::Windows::Forms::DockStyle::Fill;
				labels[i]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
						static_cast<System::Byte>(0)));
				labels[i]->Text = L"40%";
				labels[i]->TextAlign = System::Drawing::ContentAlignment::TopCenter;
				panels[i] = (gcnew System::Windows::Forms::Panel());
				panels[i]->Controls->Add(comboBoxs[i]);
				panels[i]->Controls->Add(labels[i]);
				panels[i]->Dock = System::Windows::Forms::DockStyle::Fill;
				panels[i]->Margin = System::Windows::Forms::Padding(0);
				panels[i]->BackColor = Color::FromArgb(153, 153, 153);
				tableLayoutPanel1->Controls->Add(panels[i], i%8, i/8);
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 8;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				12.5F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				12.5F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				12.5F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				12.5F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				12.5F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				12.5F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				12.5F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				12.5F)));
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 28);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 5;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1045, 541);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1045, 28);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(57, 24);
			this->fileToolStripMenuItem->Text = L"Reset";
			this->fileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::resetItemSelection);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(45, 24);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitMenuListener);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1045, 569);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->menuStrip1);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		// 0 is brown  for undug
		// 1 is green  for green rupee
		// 2 is cyan   for blue rupee
		// 3 is red    for red rupee
		// 4 is silver for silver rupee
		// 5 is gold   for gold rupee
		// 6 is d gray for rupoor
		// 7 is d blue for bomb
		unsigned char* cellColors;
		array< System::Object^  >^ listItems;
		array<System::Windows::Forms::Panel^>^  panels;
		array<System::Windows::Forms::ComboBox^>^  comboBoxs;
		array<System::Windows::Forms::Label^>^  labels;
		solver *s;

		System::Void cellPaint(int index) {
			switch(cellColors[index]){
			//case 0: panels[index]->BackColor = (Color::Peru);					break;
			case 1: panels[index]->BackColor = (Color::Chartreuse);				break;
			case 2: panels[index]->BackColor = (Color::DarkTurquoise);			break;
			case 3: panels[index]->BackColor = (Color::Red);					break;
			case 4: panels[index]->BackColor = (Color::LightSteelBlue);			break;
			case 5: panels[index]->BackColor = (Color::Gold);					break;
			case 6: panels[index]->BackColor = (Color::FromArgb(48, 48, 48));	break;
			case 7: panels[index]->BackColor = (Color::DarkBlue);				break;
			}
		}

		bool listen;
		System::Void comboListener(System::Object^  sender, System::EventArgs^  e) {
			if(!listen){
				listen = true;
				return;
			}
			ComboBox^ comboBox = (ComboBox^)(sender);
			int index = (int)comboBox->Tag;
			unsigned char oldColor = cellColors[index];
			cellColors[index] = comboBox->SelectedIndex;
			comboBox->DroppedDown = false;
			if(!s->vaildBoard()){
				listen = false;
				cellColors[index] = oldColor;
				comboBox->SelectedIndex = oldColor;
			}
			else{
				cellPaint(index);
				if(comboBox->SelectedIndex == 6 || comboBox->SelectedIndex == 7)
					labels[index]->ForeColor = Color::White;
				else
					labels[index]->ForeColor = Color::Black;
				if(comboBox->SelectedIndex != 0)
					labels[index]->Text = comboBox->Text;
				s->solve();
				for(int i=0; i<40; ++i){
					char percent = s->getPecent(i);
					if(percent != -1){
						if(percent>50)
							labels[i]->ForeColor = Color::White;
						else
							labels[i]->ForeColor = Color::Black;
						labels[i]->Text = percent+"%";
						int color = (int)((100-percent)*2.55);
						if (color < 0 || color > 255)
							continue;
						panels[i]->BackColor = (Color::FromArgb(color, color, color));
					}
				}
			}
		}

		System::Void resetItemSelection(System::Object^  sender, System::EventArgs^  e) {
			for(int i=0; i<40; ++i){
				listen = false;
				comboBoxs[i]->SelectedIndex = 0;
				cellColors[i] = 0;
				labels[i]->Text = L"40%";
				labels[i]->ForeColor = Color::Black;
				panels[i]->BackColor = Color::FromArgb(153, 153, 153);
			}
			listen = true;
		}

		System::Void exitMenuListener(System::Object^  sender, System::EventArgs^  e) {
			Application::Exit();
		}
};
}

