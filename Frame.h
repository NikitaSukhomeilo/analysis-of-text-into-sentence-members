#pragma once
#include"TextReader.h"
#include"divide_sentence.h"
//#include<string>
#include<sstream>
//#include<fstream>
//#include<Windows.h>
#include<iomanip>
#include<chrono>
#include<algorithm>
#include<filesystem>
using namespace std;
LPCWSTR string2LPCWSTR(const string&); // функция преобразования строк из std::string в LPCWSTR
void split_text(string&); // функция преобразования исходного текста в пронумерованный файл
void main_function(string&); // основная функция