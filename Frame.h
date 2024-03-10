#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<Windows.h>
#include<vector>
#include<iomanip>
#include<chrono>
#include<format>
#include<algorithm>
#include<filesystem>
using namespace std;
LPCWSTR string2LPCWSTR(const string&); // функция преобразования строк из std::string в LPCWSTR
void split_text(); // функция преобразования исходного текста в пронумерованный файл
void main_function(); // основная функция