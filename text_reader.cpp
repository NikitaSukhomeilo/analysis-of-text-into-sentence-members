#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <windows.h>
using namespace std;

const string file_text = "input.txt";

// Описание слова
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

//Структура слова: само слово + тип
struct Word {
    string data;
    Word_type type;
};

//Расшифровка перечисляемого типа для удобства
//Добавлены не все типы
string type_decoding(Word_type type) {
    switch (type) {
        case Word_type::SUBJECT:
            return "Подлежащее";
        case Word_type::PREDICATE:
            return "Сказуемое";
        case Word_type::ADDITION:
            return "Дополнение";
        case Word_type::DEFINITION:
            return "Определение";
        case Word_type::PUNCTUATION:
            return "Знак препинания";
        case Word_type::CIRCUMSTANCE:
            return "Обстоятельство";
        case Word_type::UNION:
            return "Союз";
        case Word_type::PREPOSITION:
            return "Предлог";
        case Word_type::PARTICLE:
            return "Частица";
    }
    return "Unknown";
}


//Предложение - вектор слов
vector<vector<Word>> sentences;

//Тут можно будет добавить логику выбора при последовательном анализе, каким членом предложения является слово.
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
        // Поиск позиции escape последовательности 
        size_t pos = line.find("\n");

        // Если escape последовательность найдена, обрезаем строку до этой позиции
        if (pos != string::npos) {
            line = line.substr(0, pos);
        }

        // Разделение строки на слова
        string current_word;
        vector<Word> words;
        for (size_t i = 0; i < line.size(); ++i) 
        {
            char check = line[i];
            if (isspace(check) || ispunct(check)) 
            {
                // Если текущий символ является пробелом или знаком пунктуации,
                // сохраняем собранное слово в вектор слов
                if (!current_word.empty()) 
                {
                    words.push_back({current_word, UNKNOWN});
                    current_word.clear();
                }
                // Если текущий символ является знаком пунктуации, добавляем его как отдельное слово
                if (ispunct(check)) {
                    string punctuations(1, check);
                    words.push_back({punctuations, PUNCTUATION});
                }
            } else {
                // Добавляем текущий символ к текущему слову
                current_word += check;
            }
        }
        // Проверяем, есть ли оставшееся слово в строке и добавляем его, если есть
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
    
    //Вывод предложений
    for (size_t i = 0; i < sentences.size(); ++i) {
        cout << "Предложение " << i + 1 << ":" << endl;
        const vector<Word>& sentence = sentences[i];
        for (size_t j = 0; j < sentence.size(); ++j) {
            const Word& word = sentence[j];
            cout << "Слово: " << word.data << " - Тип: " <<type_decoding(word.type)<< endl;
        }
        cout << "----------" << endl;
    }
    system("pause");
    return 0;
}