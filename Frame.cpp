#include"Frame.h"
LPCWSTR string2LPCWSTR(const string& str) // функция преобразования строк из std::string в LPCWSTR
{
	wstring wsname = wstring(str.begin(), str.end()); // создать строку типа std::wstring путём конструктора с копированием std::string
	return (wsname.c_str()); // вернуть в качестве параметра строку LPCWSTR путём копирования строки std::wstring
}
void split_text() // функция преобразования исходного текста в пронумерованный файл
{
	// получает на вход название копии файла с исходными данными
	ifstream original("temp.txt");
	ofstream splitted("splitted_text.txt");
	string line; // строка, отвечающая за хранение строки из файла (содержит несколько предложений зачастую)
	size_t sentence_counter = 1; // счётчик числа предложений
	string part_of_sentence; // строка, отвечающая за хранение первой части предложения при переносе
	string sentence; // строка, отвечающая за хранение предложения из строки копии входного файла
	while (getline(original, line)) // построчное считывание из копии оригинального входного файла
	{
		if (line.size() == false) // если из входного файла получена пустая строка
		{
			continue;
		}
		if (part_of_sentence.size() != false) // если строка непустая
		{
			// поиск знаков окончания предложения
			int pos_1 = line.find('.');
			int pos_2 = line.find('?');
			int pos_3 = line.find('!');
			int result_position;
			if (pos_1 == string::npos) // если не найдена точка
			{
				if (pos_2 == string::npos) // если не найден вопросительный знак
				{
					result_position = pos_3; // значит предложений оканчивается на восклицательный знак
				}
				else
				{
					if (pos_3 == string::npos) // если не найден восклицательный знак
					{
						result_position = pos_2; 
					}
					else
					{
						result_position = min(pos_2, pos_3); // выбор ближайшего к началу предложения знака препинания
					}
				}
			}
			else
			{
				if (pos_2 == string::npos) // если не найден вопросительный знак
				{
					if (pos_3 == string::npos) // если не найден восклицательный знак
					{
						result_position = pos_1;
					}
					else
					{
						result_position = min(pos_1, pos_3); // выбор ближайшего к началу предложения знака препинания
					}

				}
				else
				{
					result_position = min(pos_1, pos_2, pos_3); // выбор ближайшего к началу предложения знака препинания
				}
			}
			part_of_sentence += " " + line.substr(0, result_position + 1); // копирование строки до знака препинания
			splitted << sentence_counter++ << ") " << part_of_sentence << endl;
			line.erase(0, result_position + 1); // удаление пробела после знака окончания предложения
			part_of_sentence.clear(); // очистка буфера неполных предложений
		}
		if (line[line.size() - 1] != '.' && line[line.size() - 1] != '!' && line[line.size() - 1] != '?')
		{
			// если в конце строки перенос слова или части предложения
			int pos_1 = line.rfind('.');
			int pos_2 = line.rfind('?');
			int pos_3 = line.rfind('!');
			int res = max(pos_1, pos_2, pos_3);
			if (pos_1 == string::npos && pos_2 == string::npos && pos_3 == string::npos) // если в конце строки из файла нет знаков препинания (перенос части предложения)
			{
				part_of_sentence = line; // записать в буфер неполных предложений часть строки
				continue;
			}
			part_of_sentence = line.substr(res + 2, line.size() - res); // скопировать до конца строки часть предложения
		}
		for (int i = 0; i < line.size(); i++) // итерация по строке из файла
		{
			sentence += line[i]; // посимвольное копирование предложения из строки
			if (line[i] == '.' || line[i] == '?' || line[i] == '!') // если встретился символ окончания предложения
			{
				if ((i!= line.size()-1) && line[i + 1] != ' ') // если нет пробела после этого знака и все предложение не одно во всей строке
				{
					continue;
				}
				if(sentence[0] == ' ') // если в самом начале предложения есть лишние пробелы
				{
					sentence.erase(0, 1);
				}
				splitted << sentence_counter++ << ") " << sentence << endl; // записать в файл предложение
				sentence.clear();
			}
		}
		line.clear();
	}
	original.close(); splitted.close(); // закрыть файловые потоки
	LPCWSTR lpname = string2LPCWSTR("temp.txt");
	DeleteFile(lpname); // удалить промежуточный файл
}
void main_function()
{
	split_text();
}