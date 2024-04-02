#include"TextReader.h"

const string file_text = "splitted_text.txt";

// Описание слова

//Расшифровка перечисляемого типа для удобства
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

//Тут можно будет добавить логику выбора при последовательном анализе, каким членом предложения является слово.
//
Word_type getWord_type(const string& current_word)
{
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
        // Если строка начинается с числа + ")" (закрывающая скобка),
        // то пропускаем эту нумерацию.
        if (!line.empty()) {
            size_t index_pos = line.find_first_of(") ");
            if (index_pos != string::npos && index_pos != 0 && isdigit(line[index_pos - 1])) {
                line = line.substr(index_pos + 1);
            }
        }
        // Разделение строки на слова
        string current_word;
        vector<Word> words;
        for (size_t i = 0; i < line.size(); ++i)
        {
            unsigned char check = line[i];
            if (isspace(check) || ispunct(check))
            {
                // Если текущий символ является пробелом или знаком пунктуации,
                // сохраняем собранное слово в вектор слов
                if (!current_word.empty())
                {
                    words.push_back({ current_word, UNKNOWN });
                    current_word.clear();
                }
                // Если текущий символ является знаком пунктуации, добавляем его как отдельное слово
                if (ispunct(check)) {
                    string punctuations(1, check);
                    words.push_back({ punctuations, PUNCTUATION });


                } //*******************************************************************
            }
            else if (check == '-') {
                // Если текущий символ - дефис, добавляем его к текущему слову
                current_word += check;
            }
            else {
                // Добавляем текущий символ к текущему слову
                current_word += check;
                // Проверяем, если следующий символ - дефис и не является последним в строке
                if (i + 1 < line.size() && line[i + 1] == '-') {
                    // Добавляем следующий символ (дефис) к текущему слову
                    current_word += line[++i];
                }
            }
        }//********************************************************************************
        // Проверяем, есть ли оставшееся слово в строке и добавляем его, если есть
        if (!current_word.empty()) {
            Word_type type = getWord_type(current_word);
            words.push_back({ current_word, type });
        }


        sentences.push_back(words);
    }
    file.close();
}
void text_handler()
{
    separation_sentence();
    ofstream Out("test.txt");
    // Вывод предложений
    int i = 0;
    for (auto& sentence : sentences) // итерация по предложениям
    {
        Out << "Предложение " << i++ << ":" << endl;
        for (auto& word : sentence) // итерация по предложению
        {
            Out << "Слово: " << word.data << " - Тип: " << type_decoding(word.type) << endl;
        }
        Out << "----------" << endl;
    }
    Out.close();
}