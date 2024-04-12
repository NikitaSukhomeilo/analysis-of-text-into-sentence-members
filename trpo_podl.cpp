#include <iostream>
#include <string>
#include <fstream>
//#include <cstring>
//#include <string.h>
//#include <sstream>
#include <conio.h>
#include <iomanip>
//#include <chrono>
#include <Windows.h>
#include <vector>

using namespace std;

enum Word_type
{
	// основные части речи
	SUBJECT, // подлежащее
	PREDICATE, // сказуемое
	ADDITION, // дополнение
	DEFINITION, // определение
	PUNCTUATION, // знаки пунктуации
	CIRCUMSTANCE, // обстоятельство
	UNKNOWN,

	// служебные части речи
	UNION, // союз
	PREPOSITION, // предлог
	PARTICLE // частица
};
struct Word // структура слово
{
	string data; // название
	Word_type type; // тип слова
	int frequency; // частота встречаемости слова в тексте
	string sentences_included; // номера предложений, в которых встречается слово
	char label; // метка состояния
	vector<Word*> derived; // указатель на дочерний элемент
};
//Предложение - вектор слов
vector<vector<Word>> sentences;

vector <string> isc_podl;//найденные в текущем предложении подлежащие


bool mestoimenia(vector <string>& piece_of_sentence);
bool imena(string first_word);
bool find_skazyemoe(vector <string>& piece_of_sentence);
bool side_of_podl(vector <string>& piece_of_sentence, int poz_skaz);//poz_skaz позиция рассматриваемого сказцемого выраженного глаголом 
void analysis(vector <string>& piece_of_sentence);
bool Capitalized_word(vector <string>& piece_of_sentence);


void main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	system("chcp 1251 >> null");
	
	for (int i = 0; i < sentences.size(); ++i)//цикл по всем предложениям 
	{
		//цикл по опредленному предложению для нахождения знаков препинания и и количества ячеек до него 
		int counter = 0;
		int g = 0;//запоминает старт части предложения 
		string new_word;
		vector <string> piece_of_sentence;
		bool No_commas = false;//флаг если нет запятой
		while (counter < sentences[i].size())//разбиение предложения на подпредложения
		{
			piece_of_sentence.push_back(sentences[i][counter].data);//кладем слово во временный вектор piece_of_sentence
			if (sentences[i][counter + 1].data == "," or sentences[i][counter + 1].data == "." or sentences[i][counter + 1].data == "!" or sentences[i][counter + 1].data == "?")//+ 1 так как у нас знаки препинания тоже часть вектора и надо их скипать 
			{
				No_commas = true;
				analysis(piece_of_sentence);//вызываем функцию анализатора
				for (int r = counter; r >= g; --r )//обратный ход по части предложения для установки соответсвия
				{
					if (isc_podl[0] == sentences[i][r].data && sentences[i][r].type == UNKNOWN)//если найденное подлежащее равно тому что есть в предложении И оно еще не было назначено другим членом предложения 
					{
						sentences[i][g].type = SUBJECT;
					}
				}
				counter = counter + 2;//скипаем занк препинания в тексте 
				isc_podl.clear();
				piece_of_sentence.clear();
			}
			else
			{
				++counter;
			}
		}

	}

}


void analysis(vector <string>& piece_of_sentence)
{
	bool flag_spec = false;
	char break_point = 0;//номер аналзируемого признака
	while (!flag_spec)
	{

		++break_point;
		switch (break_point)
		{
		case 1: flag_spec = mestoimenia(piece_of_sentence);
			break;
		case 2: flag_spec = Capitalized_word(piece_of_sentence);//imena(piece_of_sentence)
			break;
		case 3: flag_spec = find_skazyemoe(piece_of_sentence);
			break;
		case 4: flag_spec = true;//что бы выйти
			break;
		}
	}
}



bool mestoimenia(vector <string>& piece_of_sentence)
{
	int h = 0;
	vector <string> mestoim{ "я", "ты", "мы", "вы", "он", "она", "оно", "они", "Я", "Ты", "Мы", "Вы", "Он", "Она", "Оно", "Они" };
	while (mestoim.size() < h)
	{
		for (int i = 0; i < piece_of_sentence.size(); ++i)
		{
			if (i == piece_of_sentence.size() - 1)
			{
				string last_word = piece_of_sentence[i];
				last_word.erase(last_word.end() - 1);
				if (last_word == mestoim[h])
				{
					isc_podl.push_back(mestoim[h]);
					return  true;
				}
			}
			if (piece_of_sentence[i] == mestoim[h])
			{
				isc_podl.push_back(mestoim[h]);
				return  true;
			}
		}
		++h;
	}
	return false;
}

bool imena(string first_word)
{
	vector <string> imena{ "Саша", "Александр", "Маша", "Мария", "Таня", "Татьяна", "Герасим", "Иван", "Ваня", "Анастасия", "Настя", "Алексей", "Оля", "Ольга", "Дима", "Дмитрий", "Анна", "Аня", "Дмитрий", "Дима", "Сергей", "Катя", "Алексей", "Леша", "Захар", "Михей" };
	int k = 0;
	while (imena.size() < k)
	{
		if (first_word[first_word.length() - 1] == '.' or first_word[first_word.length() - 1] == '!' or first_word[first_word.length() - 1] == '?')
		{
			first_word.erase(first_word.end() - 1);
		}
		if (first_word == imena[k])
		{
			return true;
		}
		++k;
	}
	return false;
}


bool Capitalized_word(vector <string>& piece_of_sentence)
{
	int i = 0;//счетчик элементов вектора
	bool capital_first = false;
	while (i < piece_of_sentence.size())
	{
		if (i == 0)
		{
			string first_word = piece_of_sentence[i];
			capital_first = imena(first_word);
			if (capital_first == true)
			{
				isc_podl.push_back(first_word);
				return true;
			}
		}
		else
		{
			string anyword = piece_of_sentence[i];
			if (anyword[0] > 'А' and anyword[0] < 'Я')
			{
				isc_podl.push_back(anyword);
				return true;
			}
		}
		++i;

	}

	return capital_first;
}

bool find_skazyemoe(vector <string>& piece_of_sentence)
{
	vector <string> skaz{ "Был", "Была", "Было", "Быва", "Бывала", "Бывало", "был", "была", "было", "бывал", "бывала", "бывало " };
	int i = 0;
	bool ska = false;
	char brakepoint = 0;
	int j = 0;
	string current_word;
	string ending_word_from;
	while (skaz.size() < i or ska == true)
	{
		int j = 0;//счетчик на количество слов в части предложения 
		int size_endig = skaz[i].size();
		bool word_less_ending = false;// слово меньше окончания 
		while (j < piece_of_sentence.size())
		{
			current_word = piece_of_sentence[j];
			if (j == piece_of_sentence.size() - 1)
			{
				current_word.erase(current_word.end() - 1);
			}
			if (current_word.size() <= skaz[i].size())
			{
				++j;
			}
			else
			{
				ending_word_from = current_word.substr(current_word.size() - size_endig, size_endig);//кладем в переменную строку с окончанием текущео слова
				if (skaz[i] == ending_word_from)
				{
					ska = side_of_podl(piece_of_sentence, j);//возвращаем true если нашли подлежащее
					if (ska == true)
					{
						return true;
					}
					//вызываем функцию в которой будем искать с какой стороны находится подлежащее слева или справа сначала смотрим нет ли точки или не конец предлежния слева или справа, а мб и вообще с двух сторон запятые. вызывая, проверку наличия предлога и в случае если его нет проверяем существительное слева и справа.					}
				}
				++j;
			}
		}
		++i;
	}
	return ska;
}

bool side_of_podl(vector <string>& piece_of_sentence, int poz_skaz)
{
	if (piece_of_sentence.size() <= 1)//если в векторе одно слово
	{
		return false;
	}
	if (poz_skaz == 0)
	{
		isc_podl.push_back(piece_of_sentence[poz_skaz + 1]);//если это начало предложения, то тогда второе слово подлежащее
		return true;
	}
	if (poz_skaz == piece_of_sentence.size() - 1)
	{
		isc_podl.push_back(piece_of_sentence[poz_skaz - 1]);//если это конец предложения, то тогда предыдущее слово подлежащее
		return true;
	}
	else
	{
		vector <string> predlog{ "Без", "Между", "Под", "В", "На", "По", "Вокруг", "О", "Про", "До", "Об", "С", "Для", "Около", "Из-за", "За", "От", "Из-под", "К", "Перед", "Не", "И", "Что", "Его", "Только", "без", "между", "под", "в", "на", "по", "вокруг", "о", "про", "до", "об", "с", "для", "около", "из-за", "за", "от", "из-под", "к", "перед", "не", "и", "что", "его", "только" };
		int i = 0;
		while (predlog.size() < i)
		{
			int j = 0;
			while (j < piece_of_sentence.size())
			{
				if (predlog[i] == piece_of_sentence[j])//добавить типо расстояние до нашего сказуемного равное или меньшее 0
				{
					if (j < poz_skaz)
					{
						isc_podl.push_back(piece_of_sentence[poz_skaz + 1]);

						return true;
					}
					if (j > poz_skaz)
					{
						isc_podl.push_back(piece_of_sentence[poz_skaz - 1]);
						return true;
					}
				}
				++j;
			}
		}
		++i;
	}
	return false;
}
