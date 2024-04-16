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
void find_definitions()
{
	for (auto& Sentence : sentences)
	{
		for (auto& word : Sentence)
		{
			if (word.type == UNKNOWN)
			{
				for (const auto& it : reg)
				{
					int position = word.data.rfind(it); // поиск окончания в слове
					if (position != string::npos)
					{
						int length_of_ending = it.size(); // длина окончания из файла
						if (word.data.size() - position == length_of_ending) // если в конце слова окончание
						{
							word.type = DEFINITION;
						}
					}
				}
			}
		}
	}
}