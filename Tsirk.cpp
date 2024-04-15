#include "÷ирк.h"
#include "TextReader.h"
#include <string>
#include <fstream>
#include <vector>


char** Predlog;
std::string** Okonchanie, * NotAdvNO, * NotAdvPronoun, * Top50Adv;
int PredNum, * OkNum, NotAdvNONum, NotAdvPronounNum, Top50AdvNum;


bool LoadLibs()
{
    std::ifstream fin;
    fin.open("res/ѕредлоги.txt");
    fin >> PredNum;
    Predlog = new char* [PredNum];
    for (int i = 0; i < PredNum; i++)
    {
        Predlog[i] = new char[8];
        fin >> Predlog[i];
    }
    fin.close();
    OkNum = new int[PredNum];
    Okonchanie = new std::string * [PredNum];
    for (int i = 0; i < PredNum; i++)
    {
        fin.open("res/" + std::string(Predlog[i]) + ".txt");
        fin >> OkNum[i];
        Okonchanie[i] = new std::string[OkNum[i]];
        for (int j = 0; j < OkNum[i]; j++)
        {
            fin >> Okonchanie[i][j];
        }
        fin.close();
    }
    fin.open("res/Ќќ.txt");
    fin >> NotAdvNONum;
    NotAdvNO = new std::string[NotAdvNONum];
    for (int i = 0; i < NotAdvNONum; i++)
    {
        fin >> NotAdvNO[i];
    }
    fin.close();
    fin.open("res/ћестоимени€.txt");
    fin >> NotAdvPronounNum;
    NotAdvPronoun = new std::string[NotAdvPronounNum];
    for (int i = 0; i < NotAdvPronounNum; i++)
    {
        fin >> NotAdvPronoun[i];
    }
    fin.close();
    fin.close();
    fin.open("res/“оп.txt");
    fin >> Top50AdvNum;
    Top50Adv = new std::string[Top50AdvNum];
    for (int i = 0; i < Top50AdvNum; i++)
    {
        fin >> Top50Adv[i];
    }
    fin.close();
    return 0;
}
int UnloadLibs()
{
    delete[] NotAdvNO;
    delete[] NotAdvPronoun;
    delete[] Top50Adv;
    for (int i = 0; i < PredNum; i++)
    {
        delete[] Predlog[i];
    }
    delete[] Predlog;
    for (int i = 0; i < PredNum; i++)
    {
        delete[] Okonchanie[i];
    }
    delete[] OkNum;
    delete[] Okonchanie;
    return 0;
}

bool IsPredlog(std::string word) {
    if ((word[0] >= 192) && (word[0] <= 223)) word[0] = word[0] + 32;
    for (int i = 0; i < PredNum; ++i) {
        if (word == Predlog[i]) return true;
    }
    return false;
}

std::string Vowels = "ја≈е®Є»иќо”уџыЁэёюя€";
bool CheckNotVowel(char ch) {          //ѕроверка не €вл€етс€ ли данна€ буква гласной
    for (int i = 0; i < Vowels.length(); i++)
    {
        if (ch == Vowels[i]) return false;
    }
    return true;
}

//bool IsSentenceDelimiter(char s) {
//    return s == '.' || s == '!' || s == '?' || s == ';';
//}

//bool IsWordsDelimiter(char s) {
//    return s == ',' || s == ':' || s == ' ' || s == '\t' || s == '\n' || s == '\"';
//}

void FindAdverbLite(std::vector<std::vector<Word>>& sentences) {
    for (size_t i = 0; i < sentences.size(); ++i) {
        for (size_t j = 0; j < sentences[i].size(); ++j) {
            if (sentences[i][j].data.length() > 2) {
                std::string substr = sentences[i][j].data.substr(sentences[i][j].data.length() - 2, 2);
                if (substr == "но") {
                    bool flag = 1;
                    for (int c = 0; c < NotAdvNONum; c++)
                    {
                        if (sentences[i][j].data == NotAdvNO[c]) flag = 0;
                    }
                    if (flag)
                    {
                        //std::cout << " " << sentences[i][j] << std::endl;
                        sentences[i][j].type = CIRCUMSTANCE;
                    }
                }
            }
            if (sentences[i][j].data.length() > 3) {
                std::string substr = sentences[i][j].data.substr(sentences[i][j].data.length() - 3, 3);
                if (substr == "гда") {  //поиск слов, кончающихс€ на "гда"
                    if ((sentences[i][j].data != " огда") && (sentences[i][j].data != "когда"))
                        //std::cout << " " << sentences[i][j] << std::endl;
                        sentences[i][j].type = CIRCUMSTANCE;
                    continue;
                }
                /*if (substr == "-то") {
                    std::cout << " " << sentences[i][j] << std::endl;
                    Objectives.add(sentences[i][j], i, j);
                    continue;
                }*/
            }
            if (sentences[i][j].data.length() > 4) {
                std::string substr = sentences[i][j].data.substr(sentences[i][j].data.length() - 4, 4);
                if (!CheckNotVowel(substr[0])) {
                    if (CheckNotVowel(substr[1])) {
                        if ((substr[2] == ('н'))) {
                            if (substr[3] == ('е')) {
                                //      std::cout << " " << sentences[i][j] << std::endl;
                                sentences[i][j].type = CIRCUMSTANCE;
                                continue;
                            }
                        }
                    }
                }
            }
            if (sentences[i][j].data.length() > 5) {
                std::string substr = sentences[i][j].data.substr(sentences[i][j].data.length() - 5, 5);
                if (substr == "чески") {
                    //std::cout << " " << sentences[i][j] << std::endl;
                    sentences[i][j].type = CIRCUMSTANCE;
                    continue;
                }
                if (substr == "-таки") {
                    //std::cout << " " << sentences[i][j] << std::endl;
                    sentences[i][j].type = CIRCUMSTANCE;
                    continue;
                }
                /*if (substr == "-либо") {
                    std::cout << " " << sentences[i][j] << std::endl;
                    Objectives.add(sentences[i][j], i, j);
                    continue;
                }*/
            }
            /*if (sentences[i][j].length() > 7) {
                std::string substr = sentences[i][j].substr(sentences[i][j].length() - 7, 7);
                if (substr == "-нибудь") {
                    std::cout << " " << sentences[i][j] << std::endl;
                    Objectives.add(sentences[i][j], i, j);
                    continue;
                }
            }*/
            if (sentences[i][j].data.length() > 3) {
                std::string substr = sentences[i][j].data.substr(0, 3);
                if (substr == "по-") {
                    //std::cout << " " << sentences[i][j] << std::endl;
                    sentences[i][j].type = CIRCUMSTANCE;
                    continue;
                }
            }
            for (int k = 0; k < Top50AdvNum; k++)
            {
                if (sentences[i][j].data == Top50Adv[k]) {
                    //std::cout << " " << sentences[i][j] << std::endl;
                    sentences[i][j].type = CIRCUMSTANCE;
                    break;
                }
            }
        }
    }

}

void FindByEndings(std::vector<Word>& sentence, const int k, size_t from, int sentenceNum) {
    for (size_t i = from; i < sentence.size(); ++i) {
        bool flag = true;
        for (int j = 0; j < NotAdvPronounNum; j++) //вынести в 253
        {
            if (sentence[i].data == NotAdvPronoun[j]) flag = 0;
        }
        for (int j = 0; j < Top50AdvNum; j++) //вынести в 253
        {
            if (sentence[i].data == Top50Adv[j]) flag = 0;
        }
        if (sentence[i].type != UNKNOWN) flag = 0;
        if (flag)
        {
            for (size_t c = 0; c < OkNum[k]; ++c) {
                if (sentence[i].data.length() > Okonchanie[k][c].length()) {
                    std::string substr = sentence[i].data.substr(sentence[i].data.length() - Okonchanie[k][c].length(), Okonchanie[k][c].length());
                    if (substr == Okonchanie[k][c]) {
                        if (CheckNotVowel(sentence[i].data[sentence[i].data.length() - Okonchanie[k][c].length() - 1])) {

                            //std::cout << " " << sentence[i] << std::endl;
                            sentence[i].type = CIRCUMSTANCE;
                        }
                        else if (sentence[i].data == "ше" + Okonchanie[k][c]) {
                            //std::cout << " " << sentence[i] << std::endl;
                            sentence[i].type = CIRCUMSTANCE;
                        }
                        return;
                    }
                }
            }
        }
    }
}

void FindPredlogs(std::vector<std::vector<Word>>& sentences) {
    for (size_t i = 0; i < sentences.size(); ++i) {
        for (size_t j = 0; j < sentences[i].size(); ++j) {
            if (sentences[i][j].type == PREPOSITION)
                if (IsPredlog(sentences[i][j].data)) {
                    // номер предложени€, номер слова, что за предлог
              //      std::cout << " " << sentences[i][j] << " ";
                    for (int k = 0; k < PredNum; k++)
                    {
                        if (sentences[i][j].data == Predlog[k]) {
                            FindByEndings(sentences[i], k, j, i);
                        }
                    }
                    //      std::cout << "\n";
                }
        }
        //std::cout << "\n";
    }
}