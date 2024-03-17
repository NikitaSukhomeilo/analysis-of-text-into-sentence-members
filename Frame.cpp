#include"Frame.h"
LPCWSTR string2LPCWSTR(const string& str) // функция преобразования строк из std::string в LPCWSTR
{
	wstring wsname = wstring(str.begin(), str.end()); // создать строку типа std::wstring путём конструктора с копированием std::string
	return (wsname.c_str()); // вернуть в качестве параметра строку LPCWSTR путём копирования строки std::wstring
}
void split_text(string& line) // функция преобразования исходного текста в пронумерованный файл
{
	ofstream splitted("splitted_text.txt");
	size_t sentence_counter = 1; // счётчик числа предложений
	string part_of_sentence; // строка, отвечающая за хранение первой части предложения при переносе
	string sentence; // строка, отвечающая за хранение предложения из строки копии входного файла
	for (int i = 0; i < line.size(); i++) // итерация по строке из файла
	{
		sentence += line[i]; // посимвольное копирование предложения из строки
		if (line[i] == '.' || line[i] == '?' || line[i] == '!') // если встретился символ окончания предложения
		{
			if ((i != line.size() - 1) && line[i + 1] != ' ') // если нет пробела после этого знака и все предложение не одно во всей строке
			{
				continue;
			}
			while (sentence[0] == ' ') // если в самом начале предложения есть лишние пробелы
			{
				sentence.erase(0, 1); // удаление пробелов в самом начале предложения
			}
			splitted << sentence_counter++ << ") " << sentence << endl; // записать в файл предложение
			sentence.clear();
		}
	}
	splitted.close(); // закрыть файловые потоки
}
void main_function(string& whole_text)
{
	split_text(whole_text); // разделение изначального текста на формат: [номер предложения; правая круглая скобка; пробел; само предложение]
	// функция разделения слов на признаки?
	text_handler();
	//kolyan();
	// дальнейшее разделение по признакам?
}