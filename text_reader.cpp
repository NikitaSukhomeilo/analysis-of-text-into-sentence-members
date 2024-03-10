#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <windows.h>
using namespace std;

const string file_text = "input.txt";

// �������� �����
enum Word_type {
    SUBJECT, 
    PREDICATE,
    ADDITION,
    DEFINITION,
    PUNCTUATION,
    CIRCUMSTANCE,
    UNION,
    PREPOSITION,
    PARTICLE,
    UNKNOWN
};

//��������� �����: ���� ����� + ���
struct Word {
    string data;
    Word_type type;
};

//����������� �������������� ���� ��� ��������
//��������� �� ��� ����
string type_decoding(Word_type type) {
    switch (type) {
        case Word_type::SUBJECT:
            return "����������";
        case Word_type::PREDICATE:
            return "���������";
        case Word_type::ADDITION:
            return "����������";
        case Word_type::DEFINITION:
            return "�����������";
        case Word_type::PUNCTUATION:
            return "���� ����������";
        case Word_type::CIRCUMSTANCE:
            return "��������������";
        case Word_type::UNION:
            return "����";
        case Word_type::PREPOSITION:
            return "�������";
        case Word_type::PARTICLE:
            return "�������";
    }
    return "Unknown";
}


//����������� - ������ ����
vector<vector<Word>> sentences;

//��� ����� ����� �������� ������ ������ ��� ���������������� �������, ����� ������ ����������� �������� �����.
//
Word_type getWord_type(const string& current_word) {
    
    return Word_type::UNKNOWN;
}
void separation_sentence()
{
    ifstream file(file_text);
    string line;
    while (getline(file, line)) 
   {
        // ����� ������� escape ������������������ 
        size_t pos = line.find("\n");

        // ���� escape ������������������ �������, �������� ������ �� ���� �������
        if (pos != string::npos) {
            line = line.substr(0, pos);
        }

        // ���������� ������ �� �����
        string current_word;
        vector<Word> words;
        for (size_t i = 0; i < line.size(); ++i) 
        {
            char check = line[i];
            if (isspace(check) || ispunct(check)) 
            {
                // ���� ������� ������ �������� �������� ��� ������ ����������,
                // ��������� ��������� ����� � ������ ����
                if (!current_word.empty()) 
                {
                    words.push_back({current_word, UNKNOWN});
                    current_word.clear();
                }
                // ���� ������� ������ �������� ������ ����������, ��������� ��� ��� ��������� �����
                if (ispunct(check)) {
                    string punctuations(1, check);
                    words.push_back({punctuations, PUNCTUATION});
                }
            } else {
                // ��������� ������� ������ � �������� �����
                current_word += check;
            }
        }
        // ���������, ���� �� ���������� ����� � ������ � ��������� ���, ���� ����
        if (!current_word.empty()) {
            Word_type type = getWord_type(current_word);
            words.push_back({current_word, type});
        }

        
        sentences.push_back(words);
    }
    file.close();
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL,"rus");

    separation_sentence();
    
    //����� �����������
    for (size_t i = 0; i < sentences.size(); ++i) {
        cout << "����������� " << i + 1 << ":" << endl;
        const vector<Word>& sentence = sentences[i];
        for (size_t j = 0; j < sentence.size(); ++j) {
            const Word& word = sentence[j];
            cout << "�����: " << word.data << " - ���: " <<type_decoding(word.type)<< endl;
        }
        cout << "----------" << endl;
    }
    system("pause");
    return 0;
}