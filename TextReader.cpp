#include"TextReader.hpp"
//Расшифровка перечисляемого типа для удобства
string type_decoding(Word_type type)
{
    switch (type) 
    {
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
string form_filename(string& filename) // формирование названия файла по системному времени
{
    string h;
    stringstream temp;
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    temp << now->tm_mday << '.' << (now->tm_mon + 1) << '.'
        << (now->tm_year + 1900) << "_" << (now->tm_hour) << "." << (now->tm_min);
    temp >> h;
    filename += h;
    return filename;
}
void text_handler(const string& file_text)
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
                }
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
        }
        sentences.push_back(words);
    }
    file.close();
}