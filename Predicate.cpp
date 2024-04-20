#include"Predicate.hpp"
#include<unordered_map>
unordered_map<string, vector<string>> files // словарь признаков глаголов
{
	pair<string, vector<string>>{ "RF_FC", { "ешь", "ет","уем","аем", "юем", "яем", "ете","ут","ать","ять","еть" }},
	pair<string, vector<string>>{ "RF_SC", {"ишь","ит","дим","рим","зим","тим","оим","пим", "ите","ат","ят","ить"}},
	pair<string, vector<string>>{ "RF_Refl", {"ся","ось", "ись","ась"}},
	pair<string, vector<string>>{ "RF_Pt", {"л","ал","ял","ил","ла","ло","али","или","ели","яли",
"ули","сли","шли"}},
	pair<string, vector<string>>{ "RF_ImpM", {"ите"}},
	pair<string, vector<string>>{"RF_participle", {"та","ана", "мо", "то","ано","ыты", "ена"}},
	pair<string, vector<string>>{ "RF_First_Person", {"му","шу","щу","ду","ву","ру","ну","зу","су","чу","аю","яю","ую","ею","рю","лю"}}
};
unordered_map<string, vector<string>> exclusions // словарь исключений
{
	pair<string, vector<string>>{ "EM", { "ем", "едем", "пишем", "тонем", "топнем","завладеем", "двинем","печем"}},
	pair<string, vector<string>>{"U", {"укажу", "снаряжу", "нагружу", "подрежу", "разрежу"}}
};
bool check_for_exclusion(const string& inp, const string& reason) // проверка слова на исключительные признаки сказуемого
{
	for (int i = 0; i < exclusions[reason].size(); i++) // итерация по словам-исключениям с заданным окончанием
	{
		if (exclusions[reason][i] == inp) // если исходное слово найдено в словаре исключений
		{
			return true; 
		}
	}
	return false;
}
bool chk_end(const string& inp, const string& rf) // функция проверки слова на окончания глаголов
{
	for(int i = 0; i < files[rf].size(); i++) // итерация по словарю окончаний сказуемых
	{
		int position = inp.rfind(files[rf][i]); // поиск окончания в слове
		if (position != string::npos) // если окончание найдено в исходном слове
		{
			int length_of_ending = files[rf][i].size(); // длина окончания из файла
			if (inp.size() - position == length_of_ending) // если в конце слова окончание
			{
				return true;
			}
		}
	}
	return false;
}
bool check_for_verb_signs(const string& inp) // проверка на признаки сказуемого по всем его особенностям 
{
	if (chk_end(inp, "RF_FC") == true) // проверить на окончание первого спряжения
	{
		return true;
	}
	if (chk_end(inp, "RF_SC") == true) // проверить на окончание второго спряжения
	{
		return true;
	}
	if (chk_end(inp, "RF_Refl") == true) // проверить на окончание возвратного глагола
	{
		return true;
	}
	if (chk_end(inp, "RF_Pt") == true) // проверить на окончание глагола прошедшего времени
	{
		return true;
	}
	if (chk_end(inp, "RF_ImpM") == true) // проверить на окончание глаголов повелительного наклонения
	{
		return true;
	}
	if (chk_end(inp, "RF_participle") == true) // проверить на окончание глаголов повелительного наклонения
	{
		return true;
	}
	if (chk_end(inp, "RF_First_Person") == true) // проверить на окончание глаголов первого лица
	{
		return true;
	}
	// проверка на вхождение в число исключений
	if (check_for_exclusion(inp, "EM") == true) // окончание -ем
	{
		return true;
	}
	if (check_for_exclusion(inp, "U") == true) // окончание -ем
	{
		return true;
	}
	return false;
}
string ComplexVerb(const string& inp, stringstream& buff, int& offset) // функция анализа на составное глагольное сказуемое
{
	vector<string> binding_verbs = { "нача","ста","пусти",
"продолжа","остал","переста","броси","прекрати","намеревал",
"обязал","готов","долж","рад","был","хотел","мечта","буде","пытал" }; // массив начальных частей основных вспомогательных глаголов
	string result;
	string temp;
	for(const auto& verb: binding_verbs) // итерация по массиву начальных частей вспомогательных глаголов
	{
		int position = inp.find(verb); // поиск в исходном слове начала вспомогательного глагола
		if (position != string::npos) // если слово найдено
		{
			if (position == 0) // если найдено в самом начале слова
			{
				result += inp; // записать вспомогательный глагол как сказуемое
				buff >> temp; // извлечь следующее за ним слово
				if (check_for_verb_signs(temp) == true) // если следующее слово также глагол
				{
					offset += 1; // добавить к вспомогательному глаголу основной и
					return (result + " " + temp); // записать его в результат вместе с вспомогательным глаголом в результирующую строку
				}
				else // если наречие
				{
					buff >> temp; // извлечь второе слово за вспомогательным глаголом
					if (check_for_verb_signs(temp) == true) // если слово - глагол
					{
						offset += 2; // добавить к глаголу еще один и
						return (result + " " + temp); // записать его в результирующую строку
					}
					else
					{
						return result; // если следующее слово не является частью составного сказуемого, то определить вспомогательный глагол как самостоятельный простой
					}
				}
			}
		}
	}
	return result;
}
string CompexlNominal(const string& str, stringstream& buff) // функция анализа на составные именные сказуемые
{
	vector<string> binding_verbs = { "был", "будет", "является",
"стал", "остался", "бывал", "оказался", "считался", "казался", "является", 
"слыл", "называли", "были", "бывают", "бываем", "явился"};

	for(auto &verb :binding_verbs) // поиск сказуемого среди списка вспомогательных для составных именных
	{
		int position = verb.find(str); // если слово совпадает с вспомогательным глаголом составного именного сказуемого
		if (position != string::npos && position == 0) // если нашли слово и они по-настоящему совпадают
		{
			string next_word; // строка хранения второй части составного сказуемого
			buff >> next_word; // извлечь из строки следующее за ним слово
			return str + " " + next_word; // вернуть вспомогательный глагол и следующее слово за ним
		}
	}
	return ""; // если глагол не является вспомогательным, вернуть пустую строку
}
void find_predicate() // основная функция поиска сказуемых
{
	for (auto& Sentence : sentences) // итерация по предложениям в тексте
	{
		stringstream buffer_verb; // буферный строковый поток для составных глагольных сказуемых
		stringstream buffer_for_nominal; // буферный строковый поток для составных именных сказуемых
		Word temporary; // временный объект структуры Слово
		for (int i = 0; i != Sentence.size(); i++) // итерация по словам в предложении 
		{
			if (Sentence[i].type == UNKNOWN) // если у слова тип не определен
			{
				buffer_verb >> Sentence[i].data; // занести в строковый поток для составных глагольных сказуемых слово из предложения
				buffer_for_nominal >> Sentence[i].data;// занести в строковый поток для составных именных сказуемых слово из предложения
				if (Sentence[i].data.size() < 3) // если слово меньше, чем приблизительная минимальная длина глагола
				{
					continue; // не рассматривать его при анализе
				}
				else
				{
					// составное именное сказуемое
					string temp = CompexlNominal(Sentence[i].data, buffer_for_nominal); // функция проверки на составное именное сказуемое
					if (temp.size() != false)
					{
						Sentence[i].type = PREDICATE;
						//Sentence[i].derived[0] = &Sentence[i + 1]; // получение дочернего слова
						//Sentence[i + 1].type = PREDICATE;
					}
					else
					{
						int offset = 0;
						// составное глагольное сказуемое
						string temp = ComplexVerb(Sentence[i].data, buffer_verb, offset); // функция проверки на составное глагольное сказуемое
						if (temp.size() != false)
						{
							Sentence[i].type = PREDICATE;
							//Sentence[i].derived[0] = &Sentence[i + offset];
							//Sentence[i + offset].type = PREDICATE;
						}
						else if (check_for_verb_signs(Sentence[i].data) == true)
						{
							Sentence[i].type = PREDICATE;
						}
					}
				}
			}
		}
	}
}