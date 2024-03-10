#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <windows.h>
using namespace std;

const string file_text = "input.txt";

// Îïèñàíèå ñëîâà
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

//Ñòðóêòóðà ñëîâà: ñàìî ñëîâî + òèï
struct Word {
    string data;
    Word_type type;
};

//Ðàñøèôðîâêà ïåðå÷èñëÿåìîãî òèïà äëÿ óäîáñòâà
//Äîáàâëåíû íå âñå òèïû
string type_decoding(Word_type type) {
    switch (type) {
        case Word_type::SUBJECT:
            return "Ïîäëåæàùåå";
        case Word_type::PREDICATE:
            return "Ñêàçóåìîå";
        case Word_type::ADDITION:
            return "Äîïîëíåíèå";
        case Word_type::DEFINITION:
            return "Îïðåäåëåíèå";
        case Word_type::PUNCTUATION:
            return "Çíàê ïðåïèíàíèÿ";
        case Word_type::CIRCUMSTANCE:
            return "Îáñòîÿòåëüñòâî";
        case Word_type::UNION:
            return "Ñîþç";
        case Word_type::PREPOSITION:
            return "Ïðåäëîã";
        case Word_type::PARTICLE:
            return "×àñòèöà";
    }
    return "Unknown";
}


//Ïðåäëîæåíèå - âåêòîð ñëîâ
vector<vector<Word>> sentences;

//Òóò ìîæíî áóäåò äîáàâèòü ëîãèêó âûáîðà ïðè ïîñëåäîâàòåëüíîì àíàëèçå, êàêèì ÷ëåíîì ïðåäëîæåíèÿ ÿâëÿåòñÿ ñëîâî.
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
        // Ïîèñê ïîçèöèè escape ïîñëåäîâàòåëüíîñòè 
        size_t pos = line.find("\n");

        // Åñëè escape ïîñëåäîâàòåëüíîñòü íàéäåíà, îáðåçàåì ñòðîêó äî ýòîé ïîçèöèè
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
        // Ðàçäåëåíèå ñòðîêè íà ñëîâà
        string current_word;
        vector<Word> words;
        for (size_t i = 0; i < line.size(); ++i) 
        {
            char check = line[i];
            if (isspace(check) || ispunct(check)) 
            {
                // Åñëè òåêóùèé ñèìâîë ÿâëÿåòñÿ ïðîáåëîì èëè çíàêîì ïóíêòóàöèè,
                // ñîõðàíÿåì ñîáðàííîå ñëîâî â âåêòîð ñëîâ
                if (!current_word.empty()) 
                {
                    words.push_back({current_word, UNKNOWN});
                    current_word.clear();
                }
                // Åñëè òåêóùèé ñèìâîë ÿâëÿåòñÿ çíàêîì ïóíêòóàöèè, äîáàâëÿåì åãî êàê îòäåëüíîå ñëîâî
                if (ispunct(check)) {
                    string punctuations(1, check);
                    words.push_back({punctuations, PUNCTUATION});
                }
            } else {
                // Äîáàâëÿåì òåêóùèé ñèìâîë ê òåêóùåìó ñëîâó
                current_word += check;
            }
        }
        // Ïðîâåðÿåì, åñòü ëè îñòàâøååñÿ ñëîâî â ñòðîêå è äîáàâëÿåì åãî, åñëè åñòü
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
    
    //Âûâîä ïðåäëîæåíèé
    for (size_t i = 0; i < sentences.size(); ++i) {
        cout << "Ïðåäëîæåíèå " << i + 1 << ":" << endl;
        const vector<Word>& sentence = sentences[i];
        for (size_t j = 0; j < sentence.size(); ++j) {
            const Word& word = sentence[j];
            cout << "Ñëîâî: " << word.data << " - Òèï: " <<type_decoding(word.type)<< endl;
        }
        cout << "----------" << endl;
    }
    system("pause");
    return 0;
}
