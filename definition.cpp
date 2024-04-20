#include"definition.hpp"
const vector<string> reg = { //Массив окончаний, свойственных определениям
"ий", "ый", "им",
"ым","ого","его",
"ему","ому","нем","шем","ьем",
"ом","ней","жей","шей","чей","ой",
"ое","ее","ая",
"яя","ую","юю",
"ыми","ими",
"ые","ие",
"ых","их"
};
void find_definitions() // функция поиска определений
{
	for (auto& Sentence : sentences) // итерация по предложениям
	{
		for (auto& word : Sentence) // итерация по словам в конкретном предложении
		{
			if (word.type == UNKNOWN) // если тип слова не был определен
			{
				for (const auto& it : reg) // итерация по окончаниям прилагательных
				{
					int position = word.data.rfind(it); // поиск окончания в слове
					if ((position != string::npos) && (it.size() != word.data.size())) // если найдено окончание в слове
					{
						int length_of_ending = it.size(); // длина окончания из файла
						if (word.data.size() - position == length_of_ending) // если в конце слова окончание
						{
							word.type = DEFINITION; // установка типа слова как член предложения определение
						}
					}
				}
			}
		}
	}
}