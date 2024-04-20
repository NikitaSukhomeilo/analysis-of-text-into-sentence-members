#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<cctype>
#include<windows.h>
#include<algorithm>
#include<iomanip>
using namespace std;
//Структура слова: само слово + тип
enum Word_type
{
    // основные части речи
    SUBJECT, // подлежащее
    PREDICATE, // сказуемое
    ADDITION, // дополнение
    DEFINITION, // определение
    PUNCTUATION, // знаки пунктуации
    CIRCUMSTANCE, // обстоятельство
    UNKNOWN,

    // служебные части речи
    UNION, // союз
    PREPOSITION, // предлог
    PARTICLE // частица
};
struct Word // структура слово
{
    string data; // название
    Word_type type; // тип слова
    int frequency; // частота встречаемости слова в тексте
    string sentences_included; // номера предложений, в которых встречается слово
    vector<Word*> derived; // указатель на дочерний элемент
};
//Предложение - вектор слов
inline vector<vector<Word>> sentences;
inline vector<Word> unique_words;
void text_handler(const string&);
string form_filename(string&);