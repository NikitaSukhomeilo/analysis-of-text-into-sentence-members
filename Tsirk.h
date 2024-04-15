#ifndef CIRC_H
#define CIRC_H

#include <string>
#include <fstream>
#include <vector>

bool LoadLibs(); // ��� ��������� � ������

int UnloadLibs(); // ��� ��������� � �����

void FindAdverbLite(const std::vector<std::vector<Word>>& sentences); // ��� ��������� �����

void FindPredlogs(const std::vector<std::vector<Word>>& sentences); // ��� ��������� �����, ����

#endif
