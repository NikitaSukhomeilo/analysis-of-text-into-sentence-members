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

//������� � ��������

string* exceptions; // ������ ����������
string* mas_of_endings_verb;    //������ ��������� ��������
string* mas_of_prepositions;    //����� ���������
string* mas_of_obst_preposition; //������ ��������� ��������������
string* mas_of_suffiks_of_oborot;//������ ���������
string* mas_of_unions;    //������ ������
string* mas_of_podl_endings;    //������ ��������� �����������
string* mas_of_adjectives;  //������ �����������
string* obst_word;  //������ ��������������
string* mest_word;  //������ �����������
string* particles;  //������ ������
string* interjections; //������ ����������

int endings_count = 0;  //������� ������� ��������� ��������
int exception_count = 0;    //������� ������� ����������
int prepositions_count = 0; //������� ������� ���������
int obst_preposition = 0;   //������� ������� ��������� ��������������
int obst_count = 0;     //������� ������� �������������
int mest_count = 0;     //������� ������� �����������
int count_of_suffiks_of_oborot = 0;     //������� ������� ���������
int count_of_unions_soch = 0;       //������� ������� ������
int count_of_podl_endings = 0;      // ������� ������� ����������
int endings_adjectives = 0;     //������� ������� �����������
int count_particles = 0;        //������� ������� ������
int count_interjections = 0;    //������� ������� ����������

//��������� ������� ��������(�������)
bool is_verb(const string& word);
bool is_preposition(const string& word);
bool is_unions(const string& word);
bool is_obst(const string& word);
bool is_mest(const string& word);
bool is_exception(const string& word);
bool is_adjective(const string& word);
bool is_interjection(const string& word);
bool is_particles(const string& word);


//��������� ������� �������
void find_oborots(string* words_in_sentence, int word_count);
void find_addition(vector<vector<Word>>& sentences);


//��������� ������� ����������
int countLines(const string& general_file, const string& startMarker, const string& endMarker, string*& temp_array);
string* create_array(int count);


void destroy_arr();

//������� �����
const string general_file = "all_information.txt";
const string file_text = "splitted_text.txt";