#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

//Массивы и счетчики

string* exceptions; // Массив исключений
string* mas_of_endings_verb;    //массив окончаний глаголов
string* mas_of_prepositions;    //масив предлогов
string* mas_of_obst_preposition; //Массив предлогов обстоятельства
string* mas_of_suffiks_of_oborot;//Массив суффиксов
string* mas_of_unions;    //Массив союзов
string* mas_of_podl_endings;    //Массив окончаний подлежащего
string* mas_of_adjectives;  //Массив определений
string* obst_word;  //Массив обстоятельства
string* mest_word;  //Массив местоимений
string* particles;  //Массив частиц
string* interjections; //Массив междометий

int endings_count = 0;  //Счетчик массива окончаний глаголов
int exception_count = 0;    //Счетчик массива исключений
int prepositions_count = 0; //Счетчик массива предлогов
int obst_preposition = 0;   //Счетчик массива предлогов обстоятельства
int obst_count = 0;     //Счетчик массива обстоятельств
int mest_count = 0;     //счетчик массива местоимений
int count_of_suffiks_of_oborot = 0;     //Счетчик массива суффиксов
int count_of_unions_soch = 0;       //Счетчик массива союзов
int count_of_podl_endings = 0;      // Счетчик массива подлежащих
int endings_adjectives = 0;     //Счетчик массива определений
int count_particles = 0;        //счетчик массива частиц
int count_interjections = 0;    //Счетчик массива междометий

//Прототипы функций проверок(анализа)
bool is_verb(const string& word);
bool is_preposition(const string& word);
bool is_unions(const string& word);
bool is_obst(const string& word);
bool is_mest(const string& word);
bool is_exception(const string& word);
bool is_adjective(const string& word);
bool is_interjection(const string& word);
bool is_particles(const string& word);


//Прототипы функций анализа
void find_oborots(string* words_in_sentence, int word_count);
void find_addition(vector<vector<Word>>& sentences);


//Прототипы функций заполнения
int countLines(const string& general_file, const string& startMarker, const string& endMarker, string*& temp_array);
string* create_array(int count);


void destroy_arr();

//Рабочие файлы
const string general_file = "all_information.txt";
const string file_text = "splitted_text.txt";