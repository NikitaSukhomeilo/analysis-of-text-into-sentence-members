#pragma once
#include"TextReader.h"
#include<sstream>
#include<iomanip>
#include<chrono>
#include<algorithm>
#include<filesystem>
#include"Predicate.h"
#include"addition.h"
using namespace std;
LPCWSTR string2LPCWSTR(const string&); // функция преобразования строк из std::string в LPCWSTR
void split_text(string&); // функция преобразования исходного текста в пронумерованный файл
void main_function(string&); // основная функция