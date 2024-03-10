#pragma once
#pragma comment(lib, "winmm.lib")
#pragma warning(disable : 2020) // для доступности стандарта языка C++ 17
#include<iostream>
#include<fstream>
#include<sstream>
#include<exception>
#include<string>
#include<Windows.h>
#include<msclr\marshal_cppstd.h> // библиотека для преобразования строк типа String^ в std::string и обратно
#include"Frame.h"
namespace Project4 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace std;
	using namespace msclr::interop;
	
	string* inbound_filename; // название входного файла
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void) // конструктор окна формы
		{
			InitializeComponent();
			inbound_filename = new string("");
		}
		~MyForm() // деструктор окна формы
		{
			//delete inbound_filename;
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ создатьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ открытьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ сохранитьToolStripMenuItem;


	private: System::Windows::Forms::RichTextBox^ TextDisplay;
	private: System::Windows::Forms::Button^ SubmitButton;
	private: System::Windows::Forms::Label^ SubmitSuccessLabel;
	private: System::Windows::Forms::CheckedListBox^ SelectSentenceMembers;
	private: System::Windows::Forms::Button^ ShowStatistics;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->создатьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->открытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TextDisplay = (gcnew System::Windows::Forms::RichTextBox());
			this->SubmitButton = (gcnew System::Windows::Forms::Button());
			this->SubmitSuccessLabel = (gcnew System::Windows::Forms::Label());
			this->SelectSentenceMembers = (gcnew System::Windows::Forms::CheckedListBox());
			this->ShowStatistics = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->файлToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1262, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->создатьToolStripMenuItem,
					this->открытьToolStripMenuItem, this->сохранитьToolStripMenuItem
			});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(59, 24);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// создатьToolStripMenuItem
			// 
			this->создатьToolStripMenuItem->Name = L"создатьToolStripMenuItem";
			this->создатьToolStripMenuItem->Size = System::Drawing::Size(166, 26);
			this->создатьToolStripMenuItem->Text = L"Создать";
			// 
			// открытьToolStripMenuItem
			// 
			this->открытьToolStripMenuItem->Name = L"открытьToolStripMenuItem";
			this->открытьToolStripMenuItem->Size = System::Drawing::Size(166, 26);
			this->открытьToolStripMenuItem->Text = L"Открыть";
			this->открытьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::открытьToolStripMenuItem_Click);
			// 
			// сохранитьToolStripMenuItem
			// 
			this->сохранитьToolStripMenuItem->Name = L"сохранитьToolStripMenuItem";
			this->сохранитьToolStripMenuItem->Size = System::Drawing::Size(166, 26);
			this->сохранитьToolStripMenuItem->Text = L"Сохранить";
			// 
			// TextDisplay
			// 
			this->TextDisplay->Location = System::Drawing::Point(383, 44);
			this->TextDisplay->Name = L"TextDisplay";
			this->TextDisplay->Size = System::Drawing::Size(856, 500);
			this->TextDisplay->TabIndex = 1;
			this->TextDisplay->Text = L"";
			// 
			// SubmitButton
			// 
			this->SubmitButton->Location = System::Drawing::Point(1066, 559);
			this->SubmitButton->Name = L"SubmitButton";
			this->SubmitButton->Size = System::Drawing::Size(173, 87);
			this->SubmitButton->TabIndex = 2;
			this->SubmitButton->Text = L"Провести анализ";
			this->SubmitButton->UseVisualStyleBackColor = true;
			this->SubmitButton->Click += gcnew System::EventHandler(this, &MyForm::SubmitButton_Click);
			// 
			// SubmitSuccessLabel
			// 
			this->SubmitSuccessLabel->AutoSize = true;
			this->SubmitSuccessLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SubmitSuccessLabel->ForeColor = System::Drawing::Color::Green;
			this->SubmitSuccessLabel->Location = System::Drawing::Point(881, 590);
			this->SubmitSuccessLabel->Name = L"SubmitSuccessLabel";
			this->SubmitSuccessLabel->Size = System::Drawing::Size(163, 32);
			this->SubmitSuccessLabel->TabIndex = 3;
			this->SubmitSuccessLabel->Text = L"загружено";
			this->SubmitSuccessLabel->Visible = false;
			// 
			// SelectSentenceMembers
			// 
			this->SelectSentenceMembers->CheckOnClick = true;
			this->SelectSentenceMembers->FormattingEnabled = true;
			this->SelectSentenceMembers->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Подлежащее", L"Сказуемое", L"Определение",
					L"Обстоятельство", L"Дополнение", L"Слова, не являющиеся членами предложения"
			});
			this->SelectSentenceMembers->Location = System::Drawing::Point(39, 156);
			this->SelectSentenceMembers->Name = L"SelectSentenceMembers";
			this->SelectSentenceMembers->Size = System::Drawing::Size(338, 140);
			this->SelectSentenceMembers->TabIndex = 4;
			// 
			// ShowStatistics
			// 
			this->ShowStatistics->Location = System::Drawing::Point(89, 342);
			this->ShowStatistics->Name = L"ShowStatistics";
			this->ShowStatistics->Size = System::Drawing::Size(195, 38);
			this->ShowStatistics->TabIndex = 5;
			this->ShowStatistics->Text = L"Показать статистику";
			this->ShowStatistics->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1262, 673);
			this->Controls->Add(this->ShowStatistics);
			this->Controls->Add(this->SelectSentenceMembers);
			this->Controls->Add(this->SubmitSuccessLabel);
			this->Controls->Add(this->SubmitButton);
			this->Controls->Add(this->TextDisplay);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		String^ get_current_directory(); // получение текущей папки с программой
		System::Void SubmitButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void открытьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
};
}
