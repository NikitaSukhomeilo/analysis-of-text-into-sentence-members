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
	if (this->TextDisplay->Text != "") // после ввода текста вручную в окне ввода-показа
	{
		ofstream wrfstr("temp.txt"); // создание потока на запись и файла для дальнейшей нумерации
		for (int i = 0; i < (this->TextDisplay->Lines->Length); i++) // итерация по строкам окна
		{
			string temporary; // буферная строка для записи в файл
			temporary = marshal_as<string>(this->TextDisplay->Lines[i]->ToString()); // преобразование типов строк
			wrfstr << temporary << endl; // запись строки в файл
		}
		wrfstr.close(); // закрытие файлового потока на запись
	}
	else if (inbound_filename->size() != 0) // после выбора готового текста в проводнике
	{
		LPCWSTR lpname = string2LPCWSTR("temp.txt");
		LPCWSTR lpname2 = string2LPCWSTR(*inbound_filename);
		CopyFile(lpname2, lpname, false); // копирование исходного выбранного файла
	}
	this->SubmitSuccessLabel->Visible = true;
	main_function(); // вызов основной функции
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
			*inbound_filename = marshal_as<string>(Select_File->FileName); // привести к строковому типу
			stream->Close();
		}
	}
	if (this->DialogResult == System::Windows::Forms::DialogResult::Cancel)
	{
		// обработка кнопки выход при выборе файла в проводнике
	}
	delete Select_File;
}
