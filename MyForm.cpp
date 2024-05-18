#define _CRT_SECURE_NO_WARNINGS
#include "MyForm.h"
#include"divide.hpp"
#include<filesystem>
using namespace System;
using namespace System::Windows::Forms; // пространство имён, предоставляющее доступ к функциям работы с окнами
using namespace std;
using namespace msclr::interop; // пространство имён для работы преобразователя строк marshal
[STAThreadAttribute] // обязательное требование для обмена сообщениями с сервером сообщений Windows с
int main(cli::array<String^> ^ arguments)
{
	Application::EnableVisualStyles(); // включает визуальные стили для приложения
	Application::SetCompatibleTextRenderingDefault(false); // задаёт по умолчанию значения для свойств
	Project4::MyForm Page;
	Application::Run(% Page); // запуск приложения
	Application::Exit(); // завершение работы приложения
	return 0;
}
System::Void Project4::MyForm::SubmitButton_Click(System::Object^ sender, System::EventArgs^ e) // обработка нажатия кнопки для начала анализа
{
	string whole_text;
	if (this->TextDisplay->Text != "") // после ввода текста вручную в окне ввода-показа
	{
		String^ MegaText = "";
		MegaText = this->TextDisplay->Text; // получение всего текста из окна ввода-показа
		whole_text = marshal_as<string>(MegaText); // преобразования текста-строки из System^ в std::string
		// удаление символов переноса строки
		while (whole_text.find('\n') != string::npos)
		{
			whole_text.replace(whole_text.find('\n'), 1, 1, ' ');
		}
	}
	string splitted_filename = main_function(whole_text); // вызов основной функции
	// разрешение выбора кнопок
	this->SelectSentenceMembers->Enabled = true;
	this->TableButton->Enabled = true;
	System::Windows::Forms::DialogResult u = MessageBox::Show("", "Сохранить пронумерованный файл с исходным текстом?", MessageBoxButtons::YesNo);
	if (u == System::Windows::Forms::DialogResult::No)
	{
		int a = filesystem::remove(splitted_filename);
	}
	if (u == System::Windows::Forms::DialogResult::Yes)
	{
		this->DiagnosticsLine->Clear();
		this->DiagnosticsLine->ForeColor = Color::Green;
		string temp = "Текст успешно сохранен в файле с названием " + splitted_filename + ". Ищите его в директории с программой.";
		this->DiagnosticsLine->Text = marshal_as<String^>(temp);
	}
}
String^ Project4::MyForm::get_current_directory() // получение в качестве строки String^ местоположения выбранного пользователем файла
{
	char buffer[MAX_PATH];
	GetCurrentDirectoryA(256, buffer);
	string x = string(buffer) + "\\";
	return marshal_as<String^>(x);// преобразование типов строк
}
System::Void Project4::MyForm::открытьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (sentences.size() != false) // если до этого анализировался текст
	{
		sentences.clear(); // очистка вектора структур слов
	}
	if (SelectSentenceMembers->CheckedItems->Count) // если до этого был выбор вывода членов предложения
	{
		SelectSentenceMembers->ClearSelected(); // очистка выбора
	}
	if (TextDisplay->Text != "") // если окно ввода-вывода было использовано
	{
		TextDisplay->Clear(); // очистка окна
	}
	if (unique_words.size() != false) // если вектор уникальных слов непустой
	{
		unique_words.clear(); // очистить его
	}
	// запрещение использования кнопок
	this->SelectSentenceMembers->Enabled = false;
	this->TableButton->Enabled = false;
	this->SubmitButton->Enabled = false;

	// очистка выбора отображения
	for (int i = 0; i < this->SelectSentenceMembers->Items->Count; i++)
	{
		this->SelectSentenceMembers->SetSelected(i, false);
		this->SelectSentenceMembers->SetItemChecked(i, false);
	}
	this->ShowInTextByColour->Enabled = false;
	// выбрать файл и загрузить структуру
	Stream^ stream;
	OpenFileDialog^ Select_File = gcnew OpenFileDialog(); // открыть диалоговое окно для выбора исходного файла
	Select_File->InitialDirectory = get_current_directory(); // установить первоначальное место открытия окна для
	Select_File->Filter = "txt files (*.txt)|*.txt"; // выбор только текстовых файлов
	this->DialogResult = Select_File->ShowDialog();
	if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
	{
		// обработки кнопки ок при выборе файла в проводнике
		if ((stream = Select_File->OpenFile())) // если файл открывается
		{
			// добавить ветвление по типу ричтекстбокстстримтайп в зависимости от rtf и txt
			this->TextDisplay->LoadFile(Select_File->FileName, System::Windows::Forms::RichTextBoxStreamType::PlainText);
			stream->Close();
		}
	} else
	if (this->DialogResult == System::Windows::Forms::DialogResult::Cancel)
	{
		// обработка кнопки выход при выборе файла в проводнике
	}
	delete Select_File;
	this->SubmitButton->Enabled = true;
}

System::Void Project4::MyForm::ShowInTextByColour_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (SelectSentenceMembers->CheckedItems->Count == false) // вывод диагностического сообщения при попытке отображения цветом членов предложения без конкретного выбора
	{
		MessageBox::Show("Выберите элемент из списка!", "", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else
	{
		TextDisplay->Clear();
		int lines_counter = 0; // счётчик строк окна
		this->TextDisplay->Clear();
		int TextDisplayPosition = 0; // счётчик символов в окне ввода-вывода
		for (auto& sentence : sentences) // итерация по предложениям
		{
			int count = 0;
			bool flag = false; // показатель установки пробела перед словом
			for (auto& word : sentence) // итерация по предложению
			{
				String^ line = marshal_as<String^>(word.data); // преобразование в String^ строки std::string структуры
				switch (word.type)
				{
				case SUBJECT: // подлежащее
				{
					if (this->SelectSentenceMembers->GetItemChecked(0)) // если выбрана опция показать подлежащие
					{
						TextDisplay->SelectionColor = Color::Red;
					}
					else
					{
						TextDisplay->SelectionColor = Color::Black;
					}
					break;
				}
				case PREDICATE: 
				{
					if (this->SelectSentenceMembers->GetItemChecked(1)) // если выбрана опция показать сказуемое
					{
						TextDisplay->SelectionColor = Color::Blue;
					}
					else
					{
						TextDisplay->SelectionColor = Color::Black;
					}
					break;
				}
				case DEFINITION:
				{
					if (this->SelectSentenceMembers->GetItemChecked(2))
					{
						TextDisplay->SelectionColor = Color::Green;
					}
					else
					{
						TextDisplay->SelectionColor = Color::Black;
					}
					break;
				}
				case CIRCUMSTANCE:
				{
					if (this->SelectSentenceMembers->GetItemChecked(3))
					{
						TextDisplay->SelectionColor = Color::DarkOrange;
					}
					else
					{
						TextDisplay->SelectionColor = Color::Black;
					}
				}
				case ADDITION:
				{
					if (this->SelectSentenceMembers->GetItemChecked(4)) // если выбрана опция показать дополнение
					{
						TextDisplay->SelectionColor = Color::DarkTurquoise;
					}
					else
					{
						TextDisplay->SelectionColor = Color::Black;
					}
					break;
				}

				default:
					TextDisplay->SelectionColor = Color::Black;
					break;
				}
				if ((word.type != PUNCTUATION) && (flag != false)) // если слово не является первым в предложении и не является знаком пунктуации
				{
					TextDisplay->AppendText(" ");
					TextDisplayPosition++;
				}
				else
				{
					flag = true; // разрешить постановку пробела
				}
				TextDisplay->Select(TextDisplayPosition, 0); // выбор одного символа для формата цвета по образцу
				TextDisplay->AppendText(line); // запись слова в строку окна ввода-вывода
				TextDisplayPosition += line->Length; // увеличение счётчика символов в окне ввода-вывода
			}
			TextDisplay->AppendText("\n"); // переход на следующую строку окна
			TextDisplayPosition++;
			lines_counter++; // увеличение счётчика строк окна

		}
		this->AntiColour->Enabled = true;
	}
}
System::Void Project4::MyForm::создатьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) // обработка нажатия кнопки работы с новым текстом
{
	if (sentences.size() != false) // если до этого анализировался текст
	{
		sentences.clear(); // очистка вектора структур слов
	}
	if (SelectSentenceMembers->CheckedItems->Count) // если до этого был выбор вывода членов предложения
	{
		SelectSentenceMembers->ClearSelected(); // очистка выбора
	}
	if (TextDisplay->Text != "") // если окно ввода-вывода было использовано
	{
		TextDisplay->Clear(); // очистка окна
	}
	if (unique_words.size() != false) // если вектор уникальных слов непустой
	{
		unique_words.clear(); // очистить его
	}
	// запрещение использования кнопок
	this->SelectSentenceMembers->Enabled = false;
	this->TableButton->Enabled = false;
	this->SubmitButton->Enabled = false;
	// очистка выбора отображения
	for (int i = 0; i < this->SelectSentenceMembers->Items->Count; i++)
	{
		this->SelectSentenceMembers->SetSelected(i, false);
		this->SelectSentenceMembers->SetItemChecked(i, false);
	}
	this->ShowInTextByColour->Enabled = false;
	this->AntiColour->Enabled = false;
}
string wordtype_int_to_string(const int& need_i)//переработка выдачи типа словами под вектор уникальных слов 
{
	switch (need_i)
	{
	case 0:return "Подлежащее";
	case 1:return "Сказуемое";
	case 2:return "Определение";
	case 3:return "Дополнение";
	case 4:return "Обстоятельство";
	default:return "Иное";
	}
}
void write_to_file(ofstream& writing_filestream) // функция записи в выходной файл результатов анализа текста
{
	writing_filestream << "слово" <<";" << "тип"
	<< ";" << "частота встречаемости" << ";"
	<< "предложения включающие данное слово" << endl;
	for (const auto& word : unique_words) // итерация по массиву уникальных слов
	{
		if (word.type != PUNCTUATION)
		{
			writing_filestream << word.data << ";" << wordtype_int_to_string(word.type) << ";" << word.frequency
				<< ";" << word.sentences_included << endl;
		}
	}
}
System::Void Project4::MyForm::сохранитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (unique_words.size()) // если массив уникальных слов сформирован
	{
		string filename = "Результаты анализа текста на члены предложения за ";
		filename = form_filename(filename);
		filename += ".csv";
		ofstream writing_filestream(filename);
		write_to_file(writing_filestream); // записать в файл поля элементов массива уникальных элементов
		writing_filestream.close();
		this->DiagnosticsLine->Clear();
		this->DiagnosticsLine->ForeColor = Color::Green;
		string temp = "Файл успешно сформирован с названием " + filename + ". Ищите его в директории с программой.";
		this->DiagnosticsLine->Text = marshal_as<String^>(temp); 
	}
	else
	{
		MessageBox::Show("Сохранять нечего!", "", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
}
System::Void Project4::MyForm::TableButton_Click(System::Object^ sender, System::EventArgs^ e) // отображение в табличном виде матрицы уникальных слов
{
	MyForm1^ next_page = gcnew MyForm1(this);
	this->Hide();
	next_page->Show();
}
System::Void Project4::MyForm::SelectSentenceMembers_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	this->ShowInTextByColour->Enabled = true;
}
System::Void Project4::MyForm::TextDisplay_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	this->SubmitButton->Enabled = true;
}

System::Void Project4::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	TextDisplay->SelectAll();
	TextDisplay->SelectionColor = Color::Black;
}
