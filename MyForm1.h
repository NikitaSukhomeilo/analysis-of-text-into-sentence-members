#pragma once
#include"TextReader.h"
#include<msclr\marshal_cppstd.h> // библиотека для преобразования строк типа String^ в std::string и обратно
namespace Project4
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;
	/// <summary>
	/// Сводка для MyForm1
	/// </summary>
	public ref class MyForm1 : public System::Windows::Forms::Form
	{
	public:
		MyForm1(void)
		{
			InitializeComponent();
		}
		MyForm1(System::Windows::Forms::Form^ prev)
		{
			prev_page = prev;
			InitializeComponent();
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ Screen;
	protected:

	protected:
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
		   System::Windows::Forms::Form^ prev_page;
	private: System::Windows::Forms::Button^ CloseButton;
	private: System::Windows::Forms::Button^ ShowSubject;
	private: System::Windows::Forms::Button^ ShowPredicate;
	private: System::Windows::Forms::Button^ ShowAttribute;
	private: System::Windows::Forms::Button^ ShowObject;
	private: System::Windows::Forms::Button^ ShowAdverbialModifier;
	private: System::Windows::Forms::VScrollBar^ vScrollBar1;
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
			this->Screen = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->CloseButton = (gcnew System::Windows::Forms::Button());
			this->ShowSubject = (gcnew System::Windows::Forms::Button());
			this->ShowPredicate = (gcnew System::Windows::Forms::Button());
			this->ShowAttribute = (gcnew System::Windows::Forms::Button());
			this->ShowObject = (gcnew System::Windows::Forms::Button());
			this->ShowAdverbialModifier = (gcnew System::Windows::Forms::Button());
			this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Screen))->BeginInit();
			this->SuspendLayout();
			// 
			// Screen
			// 
			this->Screen->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->Screen->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->Screen->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->Screen->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Column1, this->Column2,
					this->Column3
			});
			this->Screen->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->Screen->Location = System::Drawing::Point(0, 92);
			this->Screen->Name = L"Screen";
			this->Screen->ReadOnly = true;
			this->Screen->RowHeadersWidth = 51;
			this->Screen->RowTemplate->Height = 24;
			this->Screen->Size = System::Drawing::Size(1262, 581);
			this->Screen->TabIndex = 0;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Название";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Частота";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Номера предложений";
			this->Column3->MinimumWidth = 6;
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			// 
			// CloseButton
			// 
			this->CloseButton->Location = System::Drawing::Point(1136, 5);
			this->CloseButton->Name = L"CloseButton";
			this->CloseButton->Size = System::Drawing::Size(114, 50);
			this->CloseButton->TabIndex = 1;
			this->CloseButton->Text = L"закрыть";
			this->CloseButton->UseVisualStyleBackColor = true;
			this->CloseButton->Click += gcnew System::EventHandler(this, &MyForm1::CloseButton_Click);
			// 
			// ShowSubject
			// 
			this->ShowSubject->Location = System::Drawing::Point(12, 12);
			this->ShowSubject->Name = L"ShowSubject";
			this->ShowSubject->Size = System::Drawing::Size(140, 36);
			this->ShowSubject->TabIndex = 2;
			this->ShowSubject->Text = L"Подлежащее";
			this->ShowSubject->UseVisualStyleBackColor = true;
			this->ShowSubject->Click += gcnew System::EventHandler(this, &MyForm1::ShowSubject_Click);
			// 
			// ShowPredicate
			// 
			this->ShowPredicate->Location = System::Drawing::Point(171, 12);
			this->ShowPredicate->Name = L"ShowPredicate";
			this->ShowPredicate->Size = System::Drawing::Size(140, 36);
			this->ShowPredicate->TabIndex = 3;
			this->ShowPredicate->Text = L"Сказуемое";
			this->ShowPredicate->UseVisualStyleBackColor = true;
			this->ShowPredicate->Click += gcnew System::EventHandler(this, &MyForm1::ShowPredicate_Click);
			// 
			// ShowAttribute
			// 
			this->ShowAttribute->Location = System::Drawing::Point(335, 12);
			this->ShowAttribute->Name = L"ShowAttribute";
			this->ShowAttribute->Size = System::Drawing::Size(140, 36);
			this->ShowAttribute->TabIndex = 4;
			this->ShowAttribute->Text = L"Определение";
			this->ShowAttribute->UseVisualStyleBackColor = true;
			this->ShowAttribute->Click += gcnew System::EventHandler(this, &MyForm1::ShowAttribute_Click);
			// 
			// ShowObject
			// 
			this->ShowObject->Location = System::Drawing::Point(493, 12);
			this->ShowObject->Name = L"ShowObject";
			this->ShowObject->Size = System::Drawing::Size(140, 36);
			this->ShowObject->TabIndex = 5;
			this->ShowObject->Text = L"Дополнение";
			this->ShowObject->UseVisualStyleBackColor = true;
			this->ShowObject->Click += gcnew System::EventHandler(this, &MyForm1::ShowObject_Click);
			// 
			// ShowAdverbialModifier
			// 
			this->ShowAdverbialModifier->Location = System::Drawing::Point(650, 12);
			this->ShowAdverbialModifier->Name = L"ShowAdverbialModifier";
			this->ShowAdverbialModifier->Size = System::Drawing::Size(140, 36);
			this->ShowAdverbialModifier->TabIndex = 6;
			this->ShowAdverbialModifier->Text = L"Обстоятельство";
			this->ShowAdverbialModifier->UseVisualStyleBackColor = true;
			this->ShowAdverbialModifier->Click += gcnew System::EventHandler(this, &MyForm1::ShowAdverbialModifier_Click);
			// 
			// vScrollBar1
			// 
			this->vScrollBar1->Location = System::Drawing::Point(1241, 92);
			this->vScrollBar1->Name = L"vScrollBar1";
			this->vScrollBar1->Size = System::Drawing::Size(21, 581);
			this->vScrollBar1->TabIndex = 7;
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1262, 673);
			this->ControlBox = false;
			this->Controls->Add(this->vScrollBar1);
			this->Controls->Add(this->ShowAdverbialModifier);
			this->Controls->Add(this->ShowObject);
			this->Controls->Add(this->ShowAttribute);
			this->Controls->Add(this->ShowPredicate);
			this->Controls->Add(this->ShowSubject);
			this->Controls->Add(this->CloseButton);
			this->Controls->Add(this->Screen);
			this->Name = L"MyForm1";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Статистика";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Screen))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		System::Void CloseButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ShowSubject_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ShowPredicate_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ShowAttribute_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ShowObject_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ShowAdverbialModifier_Click(System::Object^ sender, System::EventArgs^ e);
};
}