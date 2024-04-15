#include "MyForm.h"
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

System::Void Project4::MyForm::SubmitButton_Click(System::Object^ sender, System::EventArgs^ e)
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
	this->SubmitSuccessLabel->Visible = true;
	main_function(whole_text); // вызов основной функции
	//this->SubmitButton->Enabled = false; // посмотреть позднее
	//this->SelectSentenceMembers->Enabled = true;
	//this->ShowStatistics->Enabled = true;
	//this->TableButton->Enabled = true;
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
}

System::Void Project4::MyForm::ShowStatistics_Click(System::Object^ sender, System::EventArgs^ e)
{
	TextDisplay->Clear();
	if (SelectSentenceMembers->CheckedItems->Count == false) // защита от
	{
		MessageBox::Show("Выберите элемент из списка!", "", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else
	{
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
					if (this->SelectSentenceMembers->GetItemChecked(0)) // если выбрана опция показать подлежащие
					{
						TextDisplay->SelectionColor = Color::Red;
					}
					break;
				case PREDICATE:
					if (this->SelectSentenceMembers->GetItemChecked(1)) // если выбрана опция показать сказуемое
					{
						TextDisplay->SelectionColor = Color::Blue;
					}
					break;
				case ADDITION:
					if (this->SelectSentenceMembers->GetItemChecked(2)) // если выбрана опция показать дополнение
					{
						TextDisplay->SelectionColor = Color::Violet;
					}
					break;
				case DEFINITION:
					if (this->SelectSentenceMembers->GetItemChecked(4))
					{
						TextDisplay->SelectionColor = Color::Green;
					}
					break;
				case PUNCTUATION:
					if (this->SelectSentenceMembers->GetItemChecked(5))
					{
						TextDisplay->SelectionColor = Color::Pink;
					}
					break;
				default:
					TextDisplay->SelectionColor = Color::Black;
					if (!true)
					{
						switch (count++%4)
						{
						case 0:
							TextDisplay->SelectionColor = Color::Red;
							break;
						case 1:
							TextDisplay->SelectionColor = Color::Blue;
							break;
						case 2:
							TextDisplay->SelectionColor = Color::Violet;
							break;
						case 3:
							TextDisplay->SelectionColor = Color::Green;
							break;
						default:
							break;
						}
					}
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
	}
}

System::Void Project4::MyForm::создатьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
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
	this->SubmitSuccessLabel->Visible = false;
}

System::Void Project4::MyForm::сохранитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	// здесь будет сохранение векторов структур слов в форматированном виде в файл
}

System::Void Project4::MyForm::TableButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyForm1^ next_page = gcnew MyForm1(this);
	this->Hide();
	next_page->Show();
}