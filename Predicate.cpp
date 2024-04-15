#include"Predicate.h"
#include<unordered_map>
unordered_map<string, vector<string>> files // ������� ��������� ��������
{
	pair<string, vector<string>>{ "RF_FC", { "���", "��","���","���", "���", "���", "���","��","���","���","���" }},
	pair<string, vector<string>>{ "RF_SC", {"���","��","���","���","���","���","���","���", "���","��","��","���"}},
	pair<string, vector<string>>{ "RF_Refl", {"��","���"}},
	pair<string, vector<string>>{ "RF_Pt", {"�","��","��","��","��","��","���","���","���","���",
"���","���","���"}},
	pair<string, vector<string>>{ "RF_ImpM", {"���"}},
	pair<string, vector<string>>{ "RF_First_Person", {"��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��"}}
};
unordered_map<string, vector<string>> exclusions // ������� ����������
{
	pair<string, vector<string>>{ "EM", { "��", "����", "�����", "�����", "������","���������", "������","�����"}},
	pair<string, vector<string>>{"U", {"�����", "�������", "�������", "�������", "�������"}}
};
bool check_for_exclusion(const string& inp, const string& reason)
{
	for (int i = 0; i < exclusions[reason].size(); i++)
	{
		if (exclusions[reason][i] == inp)
		{
			return true;
		}
	}
	return false;
}
bool chk_end(const string& inp, const string& rf) // ������� �������� ����� �� ��������� ��������
{
	for(int i = 0; i < files[rf].size(); i++)
	{
		int position = inp.rfind(files[rf][i]); // ����� ��������� � �����
		if (position != string::npos)
		{
			int length_of_ending = files[rf][i].size(); // ����� ��������� �� �����
			if (inp.size() - position == length_of_ending) // ���� � ����� ����� ���������
			{
				return true;
			}
		}
	}
	return false;
}
bool check_for_verb_signs(const string& inp) // �������� �� �������� �������
{
	if (chk_end(inp, "RF_FC") == true) // ��������� �� ��������� ������� ���������
	{
		return true;
	}
	if (chk_end(inp, "RF_SC") == true) // ��������� �� ��������� ������� ���������
	{
		return true;
	}
	if (chk_end(inp, "RF_Refl") == true) // ��������� �� ��������� ����������� �������
	{
		return true;
	}
	if (chk_end(inp, "RF_Pt") == true) // ��������� �� ��������� ������� ���������� �������
	{
		return true;
	}
	if (chk_end(inp, "RF_ImpM") == true) // ��������� �� ��������� �������� �������������� ����������
	{
		return true;
	}
	if (chk_end(inp, "RF_First_Person") == true) // ��������� �� ��������� �������� ������� ����
	{
		return true;
	}
	// �������� �� ��������� � ����� ����������
	if (check_for_exclusion(inp, "EM") == true) // ��������� -��
	{
		return true;
	}
	if (check_for_exclusion(inp, "U") == true) // ��������� -��
	{
		return true;
	}
	return false;
}
string ComplexVerb(const string& inp, stringstream& buff, int& offset) // ������� ������� �� ��������� ���������� ���������
{
	vector<string> binding_verbs = { "����","���","�����",
"��������","�����","�������","�����","��������","���������",
"������","�����","����","���","���","�����","�����","����","�����" };
	string result;
	string temp;
	for(auto& verb: binding_verbs)
	{
		int  position = inp.find(verb);
		if (position != string::npos) // ���� ����� �������
		{
			if (position == 0)
			{
				result += inp; // �������� ��������������� ������ ��� ���������
				buff >> temp; // ������� ��������� �� ��� �����
				if (check_for_verb_signs(temp) == true) // ���� ��������� ����� ����� ������
				{
					offset++;
					return (result + " " + temp); // �������� ��� � ��������� ������ � ��������������� ��������
				}
				else // ���� �������
				{
					buff >> temp; // ������� ������ ����� �� ��������������� ��������
					if (check_for_verb_signs(temp) == true) // ���� ����� - ������
					{
						offset += 2;
						return (result + " " + temp); // �������� ��� � ��������� ������ � ��������������� ��������
					}
					else
					{
						return result; // ���� ��������� ����� �� �������� ������ ���������� ����������, �� ���������� ��������������� ������ ��� ��������������� �������
					}
				}
			}
		}
	}
	return "";
}
string CompexlNominal(const string& str, stringstream& buff) // ������� ������� �� ��������� ������� ���������
{
	vector<string> binding_verbs = { "���", "�����", "��������",
"����", "�������", "�����", "��������", "��������", "�������", "��������", 
"����", "��������", "����", "������", "������", "������"};

	for(auto &verb :binding_verbs) // ����� ���������� ����� ������ ��������������� ��� ��������� �������
	{
		int position = verb.find(str); // ���� ����� ��������� � ��������������� �������� ���������� �������� ����������
		if (position != string::npos && position == 0) // ���� ����� ����� � ��� ��-���������� ���������
		{
			string next_word; // ������ �������� ������ ����� ���������� ����������
			buff >> next_word; // ������� �� ������ ��������� �� ��� �����
			return str + " " + next_word; // ������� ��������������� ������ � ��������� ����� �� ���
		}
	}
	return ""; // ���� ������ �� �������� ���������������, ������� ������ ������
}
void find_predicate(vector<vector<Word>>& Text) // �������� ������� ������ ���������
{
	for (auto& Sentence : Text)
	{
		stringstream buffer_verb;
		stringstream buffer_for_nominal;

		Word temporary;
		// �������������� ������� �������� � std::string
		for (int i = 0; i != Sentence.size(); i++)
		{
			if (Sentence[i].type == UNKNOWN)
			{
				buffer_verb >> Sentence[i].data;
				buffer_for_nominal >> Sentence[i].data;
				if (Sentence[i].data.size() < 3) // ��������������� ����������� ����� �������
				{
					continue;
				}
				else
				{
					// ��������� ������� ���������
					string temp = CompexlNominal(Sentence[i].data, buffer_for_nominal); // ������� �������� �� ��������� ������� ���������
					if (temp.size() != false)
					{
						Sentence[i].type = PREDICATE;
						Sentence[i].label = 1; // �������� ����� "����������"
					//	Sentence[i].derived[0] = &Sentence[i + 1]; // ��������� ��������� �����
						//Sentence[i + 1].type = PREDICATE;
					}
					else
					{
						int offset = 0;
						// ��������� ���������� ���������
						string temp = ComplexVerb(Sentence[i].data, buffer_verb, offset); // ������� �������� �� ��������� ���������� ���������
						if (temp.size() != false)
						{
							Sentence[i].type = PREDICATE;
							Sentence[i].label = 1;
							//Sentence[i].derived[0] = &Sentence[i + offset];
							//Sentence[i + offset].type = PREDICATE;
						}
						else if (check_for_verb_signs(Sentence[i].data) == true)
						{
							Sentence[i].type = PREDICATE;
							Sentence[i].label = 1;
						}
					}
				}
			}
		}
	}
}