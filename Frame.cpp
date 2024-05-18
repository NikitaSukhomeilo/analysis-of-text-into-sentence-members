#include"Frame.hpp"
#include"Predicate.hpp"
#include"addition.hpp"
#include"trpo_podl.hpp"
#include"definition.hpp"
#include"divide.hpp"
void split_text(string& line, const string& file_text) // функция преобразования исходного текста в пронумерованный файл
{
	ofstream splitted(file_text);
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
void find_union(vector<vector<Word>>& whole_text) // функция поиска союзов в тексте
{
	const vector<string> unions = { "и", "да", "тоже", "также", "а", "но", "однако", "зато", "же", "или", "либо", "то", "не", "только", "если", "столько", "сколько", "как", "так", "хотя", "что", "чтобы", "будто", "когда", "пока", "едва", "если", "раз", "ибо", "дабы", "для", "хотя", "хоть", "пускай", "как", "словно","кто", "каков", "который", "куда", "откуда", "где", "почему", "зачем" };
	for (auto& sentence : whole_text) // итерация по предложениям
	{
		for (auto& word : sentence) // итерация по предложению
		{
			string temp = word.data;

			for (auto& it : unions)
			{
				if (temp == it)
				{
					word.type = UNION;
				}
			}
		}
	}
}
void find_preposition(vector<vector<Word>>& whole_text) // функция поиска предлогов в тексте
{
	const vector<string> prepositions = { "в","это", "с","к", "до", "по", "через", "после", "из-за", "за", "над", "под", "перед", "у", "через", "возле", "мимо", "около", "от", "ради", "благодаря", "ввиду", "вследствие", "для", "на", "вопреки", "несмотря", "о", "об", "обо", "про", "насчёт","вроде", "наподобие", "без" };
	for (auto& sentence : whole_text) // итерация по предложениям
	{
		for (auto& word : sentence) // итерация по предложению
		{
			string temp = word.data;
			if (temp[0] >= -33 && temp[0] <= -64)
			{
				temp[0] += 32;
			}
			
			for (auto& it : prepositions)
			{
				if (temp == it)
				{
					word.type = PREPOSITION;
				}
			}
		}
	}
}
void find_particle(vector<vector<Word>>& whole_text) // функция поиска частиц в тексте
{
	const vector<string> particles = { "бы", "пусть", "пускай", "да", "давай", "давайте", "не", "ни", "вовсе", "далеко", "отнюдь", "уже"};
	for (auto& sentence : whole_text) // итерация по предложениям
	{
		for (auto& word : sentence) // итерация по предложению
		{
			string temp = word.data;
			if (temp[0] >= -33 && temp[0] <= -64)
			{
				temp[0] += 32;
			}

			for (auto& it : particles)
			{
				if (temp == it)
				{
					word.type = PARTICLE;
				}
			}
		}
	}
}

void filter(vector<vector<Word>>& whole_text) // функция фильтрации слов на члены предложения и части речи
{
	find_union(sentences); // поиск союзов
	find_preposition(sentences); // поиск предлогов
	find_particle(sentences); // поиск частиц
	find_definitions(); // поиск определений
	find_predicate(); // поиск сказуемых
	find_subjects(); // поиск подлежащих
	find_circumstances(); // поиск обстоятельств
	find_addition(); // поиск дополнений
}
string main_function(string& whole_text)
{
	string file_text = "Пронумерованный текст за ";
	file_text = form_filename(file_text);
	split_text(whole_text, file_text); // разделение изначального текста на формат: [номер предложения; правая круглая скобка; пробел; само предложение]
	text_handler(file_text); // формирование вектора векторов структур слов и выставка знаков препинания
	filter(sentences); // фильтрация слов на члены предложения
	uniquify_words(); // функция, осуществляющая подсчет уникальных слов и выставку номеров предложений, где они есть
	return file_text;
}