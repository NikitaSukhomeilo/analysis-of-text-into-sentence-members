#pragma once
#include"TextReader.hpp"
#include"Predicate.hpp"
#include"addition.hpp"
#include"circumstance.hpp"
using namespace std;
LPCWSTR string2LPCWSTR(const string&); // функция преобразования строк из std::string в LPCWSTR
void split_text(string&, const string&); // функция преобразования исходного текста в пронумерованный файл
void main_function(string&); // основная функция