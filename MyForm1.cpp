#include "MyForm1.h"

System::Void Project4::MyForm1::CloseButton_Click(System::Object^ sender, System::EventArgs^ e) // обработка кнопки закрытия страницы
{
	prev_page->Show();
	this->Close();
}

System::Void Project4::MyForm1::ShowSubject_Click(System::Object^ sender, System::EventArgs^ e) // отображение всех подлежащих
{
	// очищение таблицы показа
	while (this->Screen->Rows->Count > 1)
	{
		for (int i = 0; i < this->Screen->Rows->Count - 1; i++)
		{
			this->Screen->Rows->Remove(this->Screen->Rows[i]); // очистка строки таблицы
		}
	}
	int counter = 0; // переменная-счетчик
	for (const auto& word : unique_words) // итерация по массиву уникальных слов
	{
		if (word.type == SUBJECT) // если у слова тип - подлежащее
		{
			this->Screen->Rows->Add(); // добавить строку в таблицу
			this->Screen->Rows[counter]->Cells[0]->Value = marshal_as<String^>(word.data); // преобразовать в формат String^ поля объекта std::string
			this->Screen->Rows[counter]->Cells[1]->Value = word.frequency; // вывести частоту встречаемости в тексте этого слова
			this->Screen->Rows[counter++]->Cells[2]->Value = marshal_as<String^>(word.sentences_included); // вывести номера предложений, где встретилось это слово
		}
	}
}

System::Void Project4::MyForm1::ShowPredicate_Click(System::Object^ sender, System::EventArgs^ e) // отображение всех сказуемых
{
	// очищение таблицы показа
	while (this->Screen->Rows->Count > 1)
	{
		for (int i = 0; i < this->Screen->Rows->Count - 1; i++)
		{
			this->Screen->Rows->Remove(this->Screen->Rows[i]);// очистка строки таблицы
		}
	}
	int counter = 0; // переменная-счетчик

	for (const auto& word : unique_words) // итерация по массиву уникальных слов
	{
		if (word.type == PREDICATE) // если у слова тип - сказуемое
		{
			this->Screen->Rows->Add();  // добавить строку в таблицу
			this->Screen->Rows[counter]->Cells[0]->Value = marshal_as<String^>(word.data); // преобразовать в формат String^ поля объекта std::string
			this->Screen->Rows[counter]->Cells[1]->Value = word.frequency; // вывести частоту встречаемости в тексте этого слова
			this->Screen->Rows[counter++]->Cells[2]->Value = marshal_as<String^>(word.sentences_included); // вывести номера предложений, где встретилось это слово
		}
	}
}

System::Void Project4::MyForm1::ShowAttribute_Click(System::Object^ sender, System::EventArgs^ e)
{
	// очищение таблицы показа
	while (this->Screen->Rows->Count > 1)
	{
		for (int i = 0; i < this->Screen->Rows->Count - 1; i++)
		{
			this->Screen->Rows->Remove(this->Screen->Rows[i]);
		}
	}
	int counter = 0;

	for (const auto& word : unique_words) // итерация по массиву уникальных слов
	{
		if (word.type == DEFINITION) // если у слова тип - определение
		{
			this->Screen->Rows->Add();  // добавить строку в таблицу
			this->Screen->Rows[counter]->Cells[0]->Value = marshal_as<String^>(word.data); // преобразовать в формат String^ поля объекта std::string
			this->Screen->Rows[counter]->Cells[1]->Value = word.frequency; // вывести частоту встречаемости в тексте этого слова
			this->Screen->Rows[counter++]->Cells[2]->Value = marshal_as<String^>(word.sentences_included); // вывести номера предложений, где встретилось это слово
		}
	}
}

System::Void Project4::MyForm1::ShowObject_Click(System::Object^ sender, System::EventArgs^ e)
{
	// очищение таблицы показа
	while (this->Screen->Rows->Count > 1)
	{
		for (int i = 0; i < (this->Screen->Rows->Count - 1); i++)
		{
			this->Screen->Rows->Remove(this->Screen->Rows[i]);
		}
	}
	int counter = 0;

	for (const auto& word : unique_words) // итерация по массиву уникальных слов
	{
		if (word.type == ADDITION) // если у слова тип - дополнение
		{
			this->Screen->Rows->Add();  // добавить строку в таблицу
			this->Screen->Rows[counter]->Cells[0]->Value = marshal_as<String^>(word.data); // преобразовать в формат String^ поля объекта std::string
			this->Screen->Rows[counter]->Cells[1]->Value = word.frequency; // вывести частоту встречаемости в тексте этого слова
			this->Screen->Rows[counter++]->Cells[2]->Value = marshal_as<String^>(word.sentences_included); // вывести номера предложений, где встретилось это слово
		}
	}
}

System::Void Project4::MyForm1::ShowAdverbialModifier_Click(System::Object^ sender, System::EventArgs^ e)
{
	// очищение таблицы показа
	while (this->Screen->Rows->Count > 1)
	{
		for (int i = 0; i < this->Screen->Rows->Count - 1; i++)
		{
			this->Screen->Rows->Remove(this->Screen->Rows[i]);
		}
	}
	int counter = 0;

	for (const auto& word : unique_words) // итерация по массиву уникальных слов
	{
		if (word.type == CIRCUMSTANCE) // если у слова тип - обстоятельство
		{
			this->Screen->Rows->Add();  // добавить строку в таблицу
			this->Screen->Rows[counter]->Cells[0]->Value = marshal_as<String^>(word.data); // преобразовать в формат String^ поля объекта std::string
			this->Screen->Rows[counter]->Cells[1]->Value = word.frequency; // вывести частоту встречаемости в тексте этого слова
			this->Screen->Rows[counter++]->Cells[2]->Value = marshal_as<String^>(word.sentences_included); // вывести номера предложений, где встретилось это слово
		}
	}
}
