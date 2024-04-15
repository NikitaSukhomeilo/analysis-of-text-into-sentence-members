#ifndef CIRC_H
#define CIRC_H

#include <string>
#include <fstream>
#include <vector>

bool LoadLibs(); // Это запускаем в начале

int UnloadLibs(); // Это запускаем в конце

void FindAdverbLite(const std::vector<std::vector<Word>>& sentences); // Это запускаем между

void FindPredlogs(const std::vector<std::vector<Word>>& sentences); // Это запускаем между, тоже

#endif
