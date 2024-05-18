#include"divide.hpp"
vector <Word> New_word;
void word_with_same_name_and_type(int need_i, int need_j)
{
	int count = 0;
	vector<int> members = { 0 };
	string list_of_members;
	for (int i = 0; i < sentences.size(); i++)
	{

		for (int j = 0; j < sentences[i].size(); j++)
		{
			if (i <= need_i && sentences[i][j].data == sentences[need_i][need_j].data && sentences[i][j].type == sentences[need_i][need_j].type)
			{
				count++;
				members.push_back(i);
				list_of_members += "," + to_string(i + 1);
			}
		}
	}
	for (int k = 0; k < members.size(); k++)
	{

		for (int i = 0; i < sentences.size(); i++)
		{

			for (int j = 0; j < sentences[i].size(); j++)
			{
				if (i == k && sentences[i][j].data == sentences[need_i][need_j].data && sentences[i][j].type == sentences[need_i][need_j].type) {
					sentences[i][j].frequency = count;

					for (int g = 0; g < members.size(); g++)
					{
						sentences[i][j].sentences_included = list_of_members;
					}
				}
			}
		}
	}
	sentences[need_i][need_j].frequency = count;
	for (int g = 0; g < members.size(); g++)
	{
		sentences[need_i][need_j].sentences_included = list_of_members;
	}
}
void analysis()
{
	for (int i = 0; i < sentences.size(); i++)
	{
		for (int j = 0; j < sentences[i].size(); j++)
		{
			if (sentences[i][j].type != UNKNOWN)
			{
				word_with_same_name_and_type(i, j);
			}
		}
	}

	for (int i = 0; i < sentences.size(); i++)
	{
		for (int j = 0; j < sentences[i].size(); j++)
		{
			bool not_uniq_detect = false;
			for (int k = 0; k < unique_words.size(); k++)
			{
				if (sentences[i][j].data == unique_words[k].data && sentences[i][j].type == unique_words[k].type)
				{
					not_uniq_detect = true;
				}
			}
			if (not_uniq_detect == false)
			{
				unique_words.push_back(sentences[i][j]);
			}

		}
	}
}

bool comparator(Word& a, Word& b)
{
	return a.data < b.data;
}
void uniquify_words()
{
	analysis();
	for (auto& it : unique_words)
	{
		it.sentences_included.erase(0, 1);
	}
	sort(unique_words.begin(), unique_words.end(), comparator);
}