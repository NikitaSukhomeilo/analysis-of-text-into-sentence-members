#pragma once
#pragma comment(lib, "winmm.lib")
#pragma warning(disable : 2020) // для доступности стандарта языка C++ 17
#include<sstream>
#include<exception>
#include<Windows.h>
#include<msclr\marshal_cppstd.h> // библиотека для преобразования строк типа String^ в std::string и обратно
#include"Frame.hpp"
#include"MyForm1.h"
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
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void) // конструктор окна формы
		{
			InitializeComponent();
			LoadLibs(); // Это запускаем в начале
		}
		~MyForm() // деструктор окна формы
		{
			if (components)
			{
				UnloadLibs(); // Это запускаем в конце
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ создатьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ открытьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ сохранитьToolStripMenuItem;
	private: System::Windows::Forms::RichTextBox^ TextDisplay;
	private: System::Windows::Forms::Button^ SubmitButton;

	private: System::Windows::Forms::CheckedListBox^ SelectSentenceMembers;
	private: System::Windows::Forms::Button^ ShowInTextByColour;

	private: System::Windows::Forms::Button^ TableButton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::RichTextBox^ DiagnosticsLine;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ AntiColour;





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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->создатьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->открытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TextDisplay = (gcnew System::Windows::Forms::RichTextBox());
			this->SubmitButton = (gcnew System::Windows::Forms::Button());
			this->SelectSentenceMembers = (gcnew System::Windows::Forms::CheckedListBox());
			this->ShowInTextByColour = (gcnew System::Windows::Forms::Button());
			this->TableButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->DiagnosticsLine = (gcnew System::Windows::Forms::RichTextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->AntiColour = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
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
			this->создатьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::создатьToolStripMenuItem_Click);
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
			this->сохранитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::сохранитьToolStripMenuItem_Click);
			// 
			// TextDisplay
			// 
			this->TextDisplay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->TextDisplay->Location = System::Drawing::Point(532, 44);
			this->TextDisplay->Name = L"TextDisplay";
			this->TextDisplay->Size = System::Drawing::Size(707, 566);
			this->TextDisplay->TabIndex = 1;
			this->TextDisplay->Text = L"";
			this->TextDisplay->TextChanged += gcnew System::EventHandler(this, &MyForm::TextDisplay_TextChanged);
			// 
			// SubmitButton
			// 
			this->SubmitButton->Enabled = false;
			this->SubmitButton->Location = System::Drawing::Point(23, 44);
			this->SubmitButton->Name = L"SubmitButton";
			this->SubmitButton->Size = System::Drawing::Size(247, 54);
			this->SubmitButton->TabIndex = 2;
			this->SubmitButton->Text = L"Провести анализ текста на члены предложения";
			this->SubmitButton->UseVisualStyleBackColor = true;
			this->SubmitButton->Click += gcnew System::EventHandler(this, &MyForm::SubmitButton_Click);
			// 
			// SelectSentenceMembers
			// 
			this->SelectSentenceMembers->CheckOnClick = true;
			this->SelectSentenceMembers->Enabled = false;
			this->SelectSentenceMembers->FormattingEnabled = true;
			this->SelectSentenceMembers->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Подлежащее", L"Сказуемое", L"Определение",
					L"Обстоятельство", L"Дополнение", L"Слова, не являющиеся членами предложения"
			});
			this->SelectSentenceMembers->Location = System::Drawing::Point(23, 284);
			this->SelectSentenceMembers->Name = L"SelectSentenceMembers";
			this->SelectSentenceMembers->Size = System::Drawing::Size(338, 174);
			this->SelectSentenceMembers->TabIndex = 4;
			this->SelectSentenceMembers->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::SelectSentenceMembers_SelectedIndexChanged);
			// 
			// ShowInTextByColour
			// 
			this->ShowInTextByColour->Enabled = false;
			this->ShowInTextByColour->Location = System::Drawing::Point(23, 464);
			this->ShowInTextByColour->Name = L"ShowInTextByColour";
			this->ShowInTextByColour->Size = System::Drawing::Size(247, 60);
			this->ShowInTextByColour->TabIndex = 5;
			this->ShowInTextByColour->Text = L"Выделить цветом выбранные члены предложения";
			this->ShowInTextByColour->UseVisualStyleBackColor = true;
			this->ShowInTextByColour->Click += gcnew System::EventHandler(this, &MyForm::ShowInTextByColour_Click);
			// 
			// TableButton
			// 
			this->TableButton->Enabled = false;
			this->TableButton->Location = System::Drawing::Point(23, 544);
			this->TableButton->Name = L"TableButton";
			this->TableButton->Size = System::Drawing::Size(247, 66);
			this->TableButton->TabIndex = 6;
			this->TableButton->Text = L"Посмотреть в табличном виде найденные члены предложения";
			this->TableButton->UseVisualStyleBackColor = true;
			this->TableButton->Click += gcnew System::EventHandler(this, &MyForm::TableButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(20, 114);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(428, 17);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Выберите члены предложения для выделения цветом в тексте";
			// 
			// DiagnosticsLine
			// 
			this->DiagnosticsLine->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->DiagnosticsLine->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->DiagnosticsLine->Location = System::Drawing::Point(23, 620);
			this->DiagnosticsLine->Name = L"DiagnosticsLine";
			this->DiagnosticsLine->Size = System::Drawing::Size(927, 41);
			this->DiagnosticsLine->TabIndex = 9;
			this->DiagnosticsLine->Text = L"";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.InitialImage")));
			this->pictureBox1->Location = System::Drawing::Point(23, 134);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(186, 136);
			this->pictureBox1->TabIndex = 10;
			this->pictureBox1->TabStop = false;
			// 
			// AntiColour
			// 
			this->AntiColour->Enabled = false;
			this->AntiColour->Location = System::Drawing::Point(286, 464);
			this->AntiColour->Name = L"AntiColour";
			this->AntiColour->Size = System::Drawing::Size(223, 60);
			this->AntiColour->TabIndex = 11;
			this->AntiColour->Text = L"Убрать выделение цветом";
			this->AntiColour->UseVisualStyleBackColor = true;
			this->AntiColour->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1262, 673);
			this->Controls->Add(this->AntiColour);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->DiagnosticsLine);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->TableButton);
			this->Controls->Add(this->ShowInTextByColour);
			this->Controls->Add(this->SelectSentenceMembers);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		String^ get_current_directory(); // получение текущей папки с программой
		System::Void SubmitButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void открытьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ShowInTextByColour_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void создатьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void сохранитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void TableButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void SelectSentenceMembers_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void TextDisplay_TextChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
};
}
