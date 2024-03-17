#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms; // пространство имЄн, предоставл¤ющее доступ к функци¤м работы с окнами
using namespace std;
using namespace msclr::interop; // пространство имЄн дл¤ работы преобразовател¤ строк marshal
[STAThreadAttribute] // об¤зательное требование дл¤ обмена сообщени¤ми с сервером сообщений Windows с
int main(cli::array<String^> ^ arguments)
{
	Application::EnableVisualStyles(); // включает визуальные стили дл¤ приложени¤
	Application::SetCompatibleTextRenderingDefault(false); // задаЄт по умолчанию значени¤ дл¤ свойств
	Project4::MyForm Page;
	Application::Run(% Page); // запуск приложени¤
	Application::Exit(); // завершение работы приложени¤
	return 0;
}

System::Void Project4::MyForm::SubmitButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	string whole_text;
	if (this->TextDisplay->Text != "") // после ввода текста вручную в окне ввода-показа
	{
		String^ MegaText = "";
		MegaText = this->TextDisplay->Text; // получение всего текста из окна ввода-показа
		whole_text = marshal_as<string>(MegaText); // преобразовани¤ текста-строки из System^ в std::string
		// удаление символов переноса строки
		while (whole_text.find('\n') != string::npos)
		{
			whole_text.replace(whole_text.find('\n'), 1, 1, ' ');
		}
	}
	this->SubmitSuccessLabel->Visible = true;
	main_function(whole_text); // вызов основной функции
	this->SubmitButton->Enabled = false;
	this->SelectSentenceMembers->Enabled = true;
	this->ShowStatistics->Enabled = true;
}
String^ Project4::MyForm::get_current_directory() // получение в качестве строки String^ местоположени¤ выбранного пользователем файла
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
	OpenFileDialog^ Select_File = gcnew OpenFileDialog(); // открыть диалоговое окно дл¤ выбора исходного файла
	Select_File->InitialDirectory = get_current_directory(); // установить первоначальное место открыти¤ окна дл¤
	Select_File->Filter = "txt files (*.txt)|*.txt"; // выбор только текстовых файлов
	this->DialogResult = Select_File->ShowDialog();
	if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
	{
		// обработки кнопки ок при выборе файла в проводнике
		if ((stream = Select_File->OpenFile())) // если файл открываетс¤
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
		MessageBox::Show("¬ыберите элемент из списка!", "", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else
	{
		// здесь необходимы пока —”ў≈—“¬≈ЌЌџ≈ доработки
		int lines_counter = 0; // счЄтчик строк окна
		this->TextDisplay->Clear();
		for (auto& sentence : sentences) // итераци¤ по предложени¤м
		{
			for (auto& word : sentence) // итераци¤ по предложению
			{
				String^ line = marshal_as<String^>(word.data) + " "; // преобразование в String^ строки std::string структуры
				TextDisplay->AppendText(line); // запись слова в строку окна ввода-вывода
				int startPosition = this->TextDisplay->Lines[lines_counter]->Length - 2; // определение позиции в строке окна ввода-вывода начала слова
				TextDisplay->Select(startPosition, line->Length); // выделение слова
				// далее ¤ случайным образом назначил цвета
				if (word.type == 0 && this->SelectSentenceMembers->GetItemChecked(0))
				{
					TextDisplay->SelectionColor = Color::Red;
				}
				if (word.type == 1 && this->SelectSentenceMembers->GetItemChecked(1))
				{
					TextDisplay->SelectionColor = Color::Blue;
				}
				if (word.type == 2 && this->SelectSentenceMembers->GetItemChecked(2))
				{
					TextDisplay->SelectionColor = Color::Violet;
				}
				if (word.type == 3 && this->SelectSentenceMembers->GetItemChecked(3))
				{
					TextDisplay->SelectionColor = Color::Green;
				}
				if (word.type == 4 && this->SelectSentenceMembers->GetItemChecked(5))
				{
					TextDisplay->SelectionColor = Color::Pink;
				}
				// =================
				int s = this->TextDisplay->Lines[lines_counter]->Length - 1;
				TextDisplay->Select(s, 1); // выбор пробела за словом
				TextDisplay->SelectionColor = Color::Black; // установка черного цвета
			}
			TextDisplay->AppendText("\n"); // переход на следующую строку окна
			lines_counter++; // увеличение счЄтчика строк окна
		}
	}
}

System::Void Project4::MyForm::создатьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (sentences.size() != false) // если до этого анализировалс¤ текст
	{
		sentences.clear(); // очистка вектора структур слов
	}
	if (SelectSentenceMembers->CheckedItems->Count) // если до этого был выбор вывода членов предложени¤
	{
		SelectSentenceMembers->ClearSelected(); // очистка выбора
	}
	if (TextDisplay->Text != "") // если окно ввода-вывода было использовано
	{
		TextDisplay->Clear(); // очистка окна
	}
}

System::Void Project4::MyForm::сохранитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	// здесь будет сохранение векторов структур слов в форматированном виде в файл
}
