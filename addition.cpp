#include "addition.h"
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


//Прототипы функций заполнения
int countLines(const string& general_file, const string& startMarker, const string& endMarker, string*& temp_array);
string* create_array(int count);


void destroy_arr();

//Рабочие файлы
const string general_file = "all_information.txt";
const string file_text = "splitted_text.txt";
int countLines(const string& general_file, const string& startMarker, const string& endMarker, string*& temp_array) {
    ifstream file(general_file);
    string line;
    bool shouldRead = false;
    int wordCount = 0;
 
    while (getline(file, line)) {
        if (line == startMarker) {
            shouldRead = true;
            continue;
        } else if (line == endMarker) {
            shouldRead = false;
            break;
        }
 
        if (shouldRead) {
            istringstream iss(line);
            string word;
            while (iss >> word) {
                wordCount++;
            }
        }
    }
 
    //Сброс указателя в файле в начало для повторного чтения
    file.clear();  
    file.seekg(0, ios::beg);
 
    int index = 0; 
    temp_array = new string[wordCount];
 
    while (getline(file, line)) {
        if (line == startMarker) {
            shouldRead = true;
            continue;
        } else if (line == endMarker) {
            shouldRead = false;
            break;
        }
 
        if (shouldRead) {
            istringstream iss(line);
            string word;
            while (iss >> word) {
                temp_array[index] = word; // Запись слова в массив
                index++;
            }
        }
    }
     file.close();
    return wordCount;
}
 
string* create_array(int count){
    string *a;
    a = new string[count];
    return a;
}
 
//Заполнений массивов данными из файлов
//Если создавать массив, то здесь
//Объявлять сверху указатель и счетчик и дальше по аналогии, как в функции
void filling_array()
{
    //Следует избавиться от дублированного кода*
    //*Требуется рефакторинг
 
    string *temp_array = nullptr;
    //1
    endings_count = countLines(general_file, "глаголы:", "конец1", temp_array);
    mas_of_endings_verb = create_array(endings_count);
 
    for( int i = 0; i<endings_count;i++)
    {
        mas_of_endings_verb[i] = temp_array[i];
    }
    delete[]temp_array;
    temp_array = nullptr;
    //2
    prepositions_count = countLines(general_file, "предлоги:", "конец2", temp_array);
    mas_of_prepositions = create_array(prepositions_count);
 
    for( int i = 0; i<prepositions_count; i++)
    {
        mas_of_prepositions[i] = temp_array[i];
    }
 
    delete[]temp_array;
    temp_array = nullptr;
    //3 и так далее
    count_of_suffiks_of_oborot = countLines(general_file, "суффиксы:", "конец3", temp_array);
    mas_of_suffiks_of_oborot = create_array(count_of_suffiks_of_oborot);
 
    for( int i = 0; i<count_of_suffiks_of_oborot; i++)
    {
        mas_of_suffiks_of_oborot[i] = temp_array[i];
    }
 
    delete[]temp_array;
    temp_array = nullptr;
 
    count_of_unions_soch = countLines(general_file, "союзы:", "конец4", temp_array);
    mas_of_unions = create_array(count_of_unions_soch);
 
    for( int i = 0; i<count_of_unions_soch; i++)
    {
        mas_of_unions[i] = temp_array[i];
    }
 
    delete[]temp_array;
    temp_array = nullptr;
 
    obst_preposition = countLines(general_file, "обстоятельственные-предлоги:", "конец5", temp_array);
    mas_of_obst_preposition = create_array(obst_preposition);
 
    for( int i = 0; i<obst_preposition;i++)
    {
        mas_of_obst_preposition[i] = temp_array[i];
    }
    delete[]temp_array;
    temp_array = nullptr;
 
    count_of_podl_endings = countLines(general_file, "подлежащие:", "конец6", temp_array);
    mas_of_podl_endings = create_array(count_of_podl_endings);
 
    for( int i = 0; i<count_of_podl_endings; i++)
    {
        mas_of_podl_endings[i] = temp_array[i];
    }
 
    delete[]temp_array;
    temp_array = nullptr;
 
    endings_adjectives = countLines(general_file, "определение:", "конец7", temp_array);
    mas_of_adjectives = create_array(endings_adjectives);
 
    for( int i = 0; i<endings_adjectives; i++)
    {
        mas_of_adjectives[i] = temp_array[i];
    }
 
    delete[]temp_array;
    temp_array = nullptr;
 
    mest_count = countLines(general_file, "местоимения:", "конец8", temp_array);
    mest_word = create_array(mest_count);
 
    for( int i = 0; i<mest_count; i++)
    {
        mest_word[i] = temp_array[i];
    }
 
    delete[]temp_array;
    temp_array = nullptr;
 
    exception_count = countLines(general_file, "исключения:", "конец9", temp_array);
    exceptions = create_array(exception_count);
 
    for( int i = 0; i<exception_count; i++)
    {
        exceptions[i] = temp_array[i];
    }
 
    delete[]temp_array;
    temp_array = nullptr;
 
    obst_count = countLines(general_file, "наречия:", "конец10", temp_array);
    obst_word = create_array(obst_count);
 
    for( int i = 0; i<obst_count; i++)
    {
        obst_word[i] = temp_array[i];
    }
 
    delete[]temp_array;
    temp_array = nullptr;
 
    count_particles = countLines(general_file, "частицы:", "конец11", temp_array);
    particles = create_array(count_particles);
 
    for( int i = 0; i<count_particles; i++)
    {
        particles[i] = temp_array[i];
    }
 
    delete[]temp_array;
    temp_array = nullptr;
 
    count_interjections = countLines(general_file, "междометия:", "конец12", temp_array);
    interjections = create_array(count_interjections);
 
    for( int i = 0; i<count_interjections; i++)
    {
        interjections[i] = temp_array[i];
    }
 
    delete[]temp_array;
    temp_array = nullptr;
}
 
 
void find_oborots(string* words_in_sentence,int word_count){
 
    //Анализ частых случаев причатных/деепричатных оборотов
 
     bool oborot_found=false;
     bool oborot_flag=false;
     int oborot_start=0;
     int oborot_finish=0;
 
    for(int k=0;k<count_of_unions_soch;k++){
 
    for(int i=1;i<word_count;i++){
 
       if((words_in_sentence[i-1]=="," && oborot_found==false)||( is_particles(words_in_sentence[i-1]) && oborot_found==false)){
 
           for(int j=0;j<count_of_suffiks_of_oborot;j++){
 
            if(words_in_sentence[i].rfind(mas_of_suffiks_of_oborot[j])!=-1){
                oborot_found = true;
                oborot_start = i-1;
 
            }
 
           }
       }
    }
    for(int i=1; i < word_count; i++){
 
      if(words_in_sentence[i-1]=="," && oborot_found==true && oborot_start <= i-1  && oborot_start != i-1 ){
 
         for(int j=0;j<count_of_suffiks_of_oborot;j++){
 
            if(words_in_sentence[i].rfind(mas_of_suffiks_of_oborot[j])==-1){
                oborot_found = false;
                oborot_finish = i;
 
            }
            if(words_in_sentence[i].rfind(mas_of_suffiks_of_oborot[j])!=-1){
                oborot_found = true;
 
 
            }
           }
       }
       else if(words_in_sentence[i]=="." && oborot_found==true){
        oborot_found = false;
        oborot_finish = i;
       }
 
    }
 
 
 
    for(int i = oborot_start;i < oborot_finish;i++){
 
     words_in_sentence[i].erase();
 
    }
 
}
}
 
bool is_preposition(const string& word) { 
    for (int i = 0; i < prepositions_count; i++) {
        if (word == mas_of_prepositions[i]) {
            return true;
        }
    }
    return false;
}
bool is_obst_preposition(const string& word) { 
    for (int i = 0; i <obst_preposition ; i++) {
        if (word == mas_of_obst_preposition[i]) {
            return true;
        }
    }
    return false;
}
 
bool is_obst(const string& word) { 
    for (int i = 0; i < obst_count; i++) {
        if (word == obst_word[i]) {
            return true;
        }
    }
    return false;
}
 
bool is_mest(const string& word) { 
    for (int i = 0; i < mest_count; i++) {
        if (word == mest_word[i]) {
            return true;
        }
    }
    return false;
}
 
bool is_unions(const string& word) { 
    for (int i = 0; i < count_of_unions_soch; i++) {
        if (word == mas_of_unions[i]) {
            return true;
        }
    }
    return false;
}
 
bool is_exception(const string& word)
{
    for (int i = 0; i < exception_count; i++) 
    {
        if (word == exceptions[i]) {
            return true; 
        }
    }
    return false; 
}
 
bool is_verb(const string& word ) 
{
    for (int i = 0; i < endings_count; i++) {
        if (word.size() >= mas_of_endings_verb[i].size() &&
            word.compare(word.size() - mas_of_endings_verb[i].size(), mas_of_endings_verb[i].size(), mas_of_endings_verb[i]) == 0) 
            {
                if(!is_exception(word))
                {
                    return true;
                }
            }
        }
        return false;
} 
 
bool is_adjective(const string& word) 
{
    for (int i = 0; i < endings_adjectives; i++) {
        if (word.size() >= mas_of_adjectives[i].size() &&
            word.compare(word.size() - mas_of_adjectives[i].size(), mas_of_adjectives[i].size(), mas_of_adjectives[i]) == 0) 
            {
                if(!is_exception(word))
                {
                    return true;
                }
            }
        }
        return false;
} 
bool is_interjection(const string& word){
     for (int i = 0; i < count_interjections; i++) 
    {
        if (word == interjections[i]) {
            return true; 
        }
    }
    return false; 
}
 
bool is_particles(const string& word){
     for (int i = 0; i < count_particles; i++) 
    {
        if (word == particles[i]) {
            return true; 
        }
    }
    return false; 
}
 
void find_addition(vector<vector<Word>>& sentences)
{
    filling_array();
    int senteces_count = sentences.size();
    int word_count = 0;
    vector<string> remaining_words;
   for (int i = 0; i<senteces_count;++i ) 
   {
        word_count = sentences[i].size();
        if(word_count == 0)
        {
            break;
        }
        string* words_in_sentence = new string[word_count];
        for(int k = 0; k <word_count; k++)
        {
            words_in_sentence[k] = sentences[i][k].data;
            
        }
        find_oborots( words_in_sentence, word_count);
        for (int i = 0; i < word_count; i++) 
        {
 
          if(i!=0  && is_obst_preposition(words_in_sentence[i-1]) == true){
 
                 for(int j=0;j<count_of_podl_endings;j++){
 
                      if(words_in_sentence[i].rfind(mas_of_podl_endings[j])!=-1 ||words_in_sentence[i]==mas_of_podl_endings[j] ){
 
                      words_in_sentence[i].erase();
                      }
                 }
            }
 
        }
       for (int i = 0; i < word_count; i++) 
        {
 
            string lower_word = words_in_sentence[i];  //Перевод в нижний регистр для анализа
 
            for (int k = 0; k < lower_word.length(); k++) 
            {
                lower_word[0] = tolower(lower_word[0]);  
            }                                          
            if (is_verb(lower_word)) 
            {
 
                words_in_sentence[i].erase();
 
            }
            else if(is_unions(lower_word)==true){
 
                 words_in_sentence[i].erase();
            }
 
            else if(is_preposition(lower_word)) 
            {
                words_in_sentence[i].erase();
 
            }
            else if(is_adjective(lower_word))
            {
 
                words_in_sentence[i].erase();
            }
            else if (is_obst(lower_word))
            {
 
                words_in_sentence[i].erase();
            }
            else if (is_mest(lower_word))
            {
 
                words_in_sentence[i].erase();
            }
            else if (is_interjection(lower_word))
            {
 
                words_in_sentence[i].erase();
            }
            else if (is_particles(lower_word))
            {
 
                words_in_sentence[i].erase();
            }
            else if(words_in_sentence[i]=="—"|| words_in_sentence[i]=="-" || words_in_sentence[i]=="–"|| words_in_sentence[i].find('«')!=string::npos || words_in_sentence[i].find('»')!=string::npos ||
             words_in_sentence[i].find('"')!=string::npos )
            {
                words_in_sentence[i].erase();
            }
        }
        //Заполнение вектора теми словами. которые остались после анализа текста(т.е предполагаемые дополнения)
 
        bool detect_vector_str = false;
        for(int i = 0;i< word_count;i++)
        {
            detect_vector_str = false;
            if(!words_in_sentence[i].empty()&& words_in_sentence[i]!="—" && words_in_sentence[i]!="." && words_in_sentence[i]!="," && 
            words_in_sentence[i]!=";"&& words_in_sentence[i]!="!" && words_in_sentence[i]!="?" && words_in_sentence[i]!=":" )
            {
                for(int j = 0; j<remaining_words.size();j++){
                    if(remaining_words[j]!=words_in_sentence[i])
                    {
                        detect_vector_str=false;
                    }
                    else 
                    {
                        detect_vector_str = true;
                        break;
                    }
                }
                if(detect_vector_str == false)
                {
                    remaining_words.push_back(words_in_sentence[i]);
                }
            }
        }
         delete[] words_in_sentence;
    } 

    for (size_t k = 0; k < remaining_words.size(); k++)
    {           
        for (size_t i = 0; i < sentences.size(); i++)
        {
            for (size_t j = 0; j < sentences[i].size(); j++)
            {
                if (remaining_words[k] == sentences[i][j].data && sentences[i][j].type == UNKNOWN)
                {
                    sentences[i][j].type = ADDITION;
                }
            }
        }
    }
    destroy_arr();
}
void destroy_arr()
{
    delete[] exceptions;//
    delete[] mas_of_endings_verb; //
    delete[] mas_of_prepositions;//
    delete[] mas_of_obst_preposition;
    delete[] mas_of_suffiks_of_oborot;//
    delete[] mas_of_unions;//
    delete[] mas_of_podl_endings;//
    delete[] mas_of_adjectives;//
    delete[] obst_word;//
    delete[] mest_word;//
    delete[] particles;//
    delete[] interjections;//
}

