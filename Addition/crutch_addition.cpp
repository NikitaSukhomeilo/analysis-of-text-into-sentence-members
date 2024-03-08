#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>



using namespace std;

//Флаги для знаков препинания
bool detect_comma = false; //false - не обнаружена, true - обнаружена запятая
bool detect_ellipses = false;  //false - не обнаружено, true - обнаружено двоеточие
bool detect_semicolon = false; //false - не обнаружена, true - обнаружена точка с запятой
bool detect_dot = false; //false - не обнаружена, true - обнаружена точка
bool question_mark = false;  //false - не обнаружен, true - обнаружен вопросительный знак
bool exclamation_mark = false; //false - не обнаружен, true - обнаружен восклицательный знак

//Массивы и счетчики

string *exceptions; // Массив исключений
string *mas_of_endings_verb;    //массив окончаний глаголов
string *mas_of_prepositions;    //масив предлогов
string *mas_of_obst_preposition; //Массив предлогов обстоятельства
string *mas_of_suffiks_of_oborot;//Массив суффиксов
string *mas_of_unions;    //Массив союзов
string *mas_of_podl_endings;    //Массив окончаний подлежащего
string *mas_of_adjectives;  //Массив определений
string *obst_word;  //Массив наречий
string *mest_word;  //Массив местоимений
string *particles;  //Массив частиц
string *interjections; //Массив междометий

int endings_count = 0;  //Счетчик массива окончаний глаголов
int exception_count = 0;    //Счетчик массива исключений
int prepositions_count = 0; //Счетчик массива предлогов
int obst_preposition = 0;   //Счетчик массива предлогов обстоятельства
int obst_count = 0;     //Счетчик массива наречий
int mest_count = 0;     //счетчик массива местоимений
int count_of_suffiks_of_oborot = 0;     //Счетчик массива суффиксов
int count_of_unions_soch = 0;       //Счетчик массива союзов
int count_of_podl_endings = 0;      // Счетчик массива подлежащих
int endings_adjectives = 0;     //Счетчик массива определений
int count_particles = 0;        //счетчик массива частиц
int count_interjections = 0;    //Счетчик массива междометий

//Прототипы функций проверок(анализа)
bool is_verb(const string& word);  //функция проверки на глагол
bool is_preposition(const string& word); //функция проверки на предлог
bool is_unions(const string& word); //функция проверки на союзы
bool is_obst(const string& word); //функция проверки на наречие
bool is_mest(const string& word); //функция проверки на местоимения
bool is_exception(const string& word); //функция проверки на исключения
bool is_adjective(const string& word); //функция проверки на опредления
bool is_interjection(const string& word); //функция проверки на междометия
bool is_particles(const string& word); //функкция проверки на частицы


//Прототипы функций анализа
void find_oborots(string* words_in_sentence, int word_count); //функция поиска причатсных/ деепричастных оборотов
void form_of_mass_of_sentence(string text, int sentence_count); //функция для формирования последовательности вызовов функций анализа


//Прототипы функций заполнения
int countLines(const string& general_file, const string& startMarker, const string& endMarker, string*& temp_array); //функция формирования массивов частиц, предлогов и т.д
int find_sentence(string text); //функция подсчета кол-ва предложений в тексте
string* create_array(int count); //функция для создания динамического массива
void filling_array();//функция для заполнения массивов частиц, предлогов и т.д


//Рабочие файлы
const string general_file = "all_information.txt"; //в данном файле хранятся частицы, предлоги, окончания глаголов и т.д
const string text_in = "split_text.txt"; //в данном файле будет хранится текст с пронумерованными предложениями
const string task_output ="true_out.txt"; //выходной файл с результатами анализа на дополнения

int counter = 0;

//функция формирования массивов частиц, предлогов и т.д
int countLines(const string& general_file, const string& startMarker, const string& endMarker, string*& temp_array) {
    ifstream file(general_file); //
    string line;
    bool shouldRead = false; //флаг который контролирует считывание между метками start и end
    int wordCount = 0;

    // считывание данных из файла, если найден маркер start, то флаг для считывания активируется
    // если обнаружена метка end, то флаг для считывания деактивируется
    while (getline(file, line)) {
        if (line == startMarker) {
            shouldRead = true;
            continue;
        } else if (line == endMarker) {
            shouldRead = false;
            break;
        }

        if (shouldRead) {
            istringstream iss(line); //считывание данных
            string word;
            while (iss >> word) {
                wordCount++; // подсчет кол-ва слов между метками
            }
        }
    }

    //Сброс указателя в файле в начало для повторного чтения
    file.clear();  
    file.seekg(0, ios::beg);

    int index = 0; 
    //создание динамичсекого массива
    temp_array = new string[wordCount];
    //повторное считывание данных между метками, только уже не для подсчета кол-ва слов,
    // а для заполнения массива
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
    return wordCount; //возвращаемое значение - кол-во слов
}

 //функция для создания динамического массива
string* create_array(int count){
    string *a;
    a = new string[count];
    return a;
}

//Заполнений массивов данными из файлов
void filling_array()
{
    
    string *temp_array = nullptr;
    //вызываются функции дял подсчета кол-ва слов между соответствующими метками в файле general_file
    //и создания динамического массива с считанными словами из файла
    endings_count = countLines(general_file, "глаголы:", "конец1", temp_array);
    mas_of_endings_verb = create_array(endings_count);
    // массив окончаний глаголов
    for( int i = 0; i<endings_count;i++)
    {
        //во временном массиве хранятся считанные данные из файла
        //которые в данном цикле записываются в другой динамический массив
        mas_of_endings_verb[i] = temp_array[i];
    }
    delete[]temp_array;
    temp_array = nullptr;
    //массив предлогов
    prepositions_count = countLines(general_file, "предлоги:", "конец2", temp_array);
    mas_of_prepositions = create_array(prepositions_count);

    for( int i = 0; i<prepositions_count; i++)
    {
        mas_of_prepositions[i] = temp_array[i];
    }
    
    delete[]temp_array;
    temp_array = nullptr;
    //массив суффиксов
    count_of_suffiks_of_oborot = countLines(general_file, "суффиксы:", "конец3", temp_array);
    mas_of_suffiks_of_oborot = create_array(count_of_suffiks_of_oborot);

    for( int i = 0; i<count_of_suffiks_of_oborot; i++)
    {
        mas_of_suffiks_of_oborot[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //массив союзов
    count_of_unions_soch = countLines(general_file, "союзы:", "конец4", temp_array);
    mas_of_unions = create_array(count_of_unions_soch);

    for( int i = 0; i<count_of_unions_soch; i++)
    {
        mas_of_unions[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //массив обстоятельственных предлогов
    obst_preposition = countLines(general_file, "обстоятельственные-предлоги:", "конец5", temp_array);
    mas_of_obst_preposition = create_array(obst_preposition);

    for( int i = 0; i<obst_preposition;i++)
    {
        mas_of_obst_preposition[i] = temp_array[i];
    }
    delete[]temp_array;
    temp_array = nullptr;
    // массив окончаний подлежащих
    count_of_podl_endings = countLines(general_file, "подлежащие:", "конец6", temp_array);
    mas_of_podl_endings = create_array(count_of_podl_endings);

    for( int i = 0; i<count_of_podl_endings; i++)
    {
        mas_of_podl_endings[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //массив окончаний прилагательных
    endings_adjectives = countLines(general_file, "определение:", "конец7", temp_array);
    mas_of_adjectives = create_array(endings_adjectives);

    for( int i = 0; i<endings_adjectives; i++)
    {
        mas_of_adjectives[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    // массив местоимений
    mest_count = countLines(general_file, "местоимения:", "конец8", temp_array);
    mest_word = create_array(mest_count);

    for( int i = 0; i<mest_count; i++)
    {
        mest_word[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //массив исключений
    exception_count = countLines(general_file, "исключения:", "конец9", temp_array);
    exceptions = create_array(exception_count);

    for( int i = 0; i<exception_count; i++)
    {
        exceptions[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //массив наречий
    obst_count = countLines(general_file, "наречия:", "конец10", temp_array);
    obst_word = create_array(obst_count);

    for( int i = 0; i<obst_count; i++)
    {
        obst_word[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //массив частиц
    count_particles = countLines(general_file, "частицы:", "конец11", temp_array);
    particles = create_array(count_particles);

    for( int i = 0; i<count_particles; i++)
    {
        particles[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //массив междометий
    count_interjections = countLines(general_file, "междометия:", "конец12", temp_array);
    interjections = create_array(count_interjections);

    for( int i = 0; i<count_interjections; i++)
    {
        interjections[i] = temp_array[i];
    }
    
    delete[]temp_array;
    temp_array = nullptr;
}

//функция поиска причастных/деепричастных оборотов
void find_oborots(string* words_in_sentence,int word_count){

    //Анализ частых случаев причастных/деепричастных оборотов

     bool oborot_found=false; //флаг для обнаружения оборота
     int oborot_start=0; //начало оборота
     int oborot_finish=0; //конец оборота

    for(int k=0;k<count_of_unions_soch;k++){
    
    for(int i=1;i<word_count;i++){

       if((words_in_sentence[i-1]=="," && oborot_found==false)||( is_particles(words_in_sentence[i-1]) && oborot_found==false)){
           
           for(int j=0;j<count_of_suffiks_of_oborot;j++){

            if(words_in_sentence[i].rfind(mas_of_suffiks_of_oborot[j])!=-1){
                oborot_found = true;
                oborot_start = i-1; //если оборот найден фиксируется место начала и флаг оборота включается
                
            }

           }
       }
    }
    for(int i=1; i < word_count; i++){
      
      if(words_in_sentence[i-1]=="," && oborot_found==true && oborot_start <= i-1  && oborot_start != i-1 ){

         for(int j=0;j<count_of_suffiks_of_oborot;j++){

            if(words_in_sentence[i].rfind(mas_of_suffiks_of_oborot[j])==-1){
                oborot_found = false;
                oborot_finish = i; // как только найден конец оборота, то это место фиксируется и флаг выключается
               
            }
            if(words_in_sentence[i].rfind(mas_of_suffiks_of_oborot[j])!=-1){
                oborot_found = true; //если найдено слово у которого имеется суффикс из массива суффиксов
                // то оборот обнаружен
            }
           }
       }
       else if(words_in_sentence[i]=="." && oborot_found==true){
        oborot_found = false;
        oborot_finish = i; //факт обнаружения конца оборота, если он в конце предложения
       }
    
    }
   
    for(int i = oborot_start;i < oborot_finish;i++){

     words_in_sentence[i].erase(); //удаление оборота из массива

    }

}
}

//функция подсчета кол-ва предложений в тексте
int find_sentence(string text)
{
    int count = 0;
    for(int i = 0;i<text.length();i++){
        if (text[i] == '.' || text[i] == '!' ||text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

//функция проверки на предлог
bool is_preposition(const string& word) { 
    for (int i = 0; i < prepositions_count; i++) {
        if (word == mas_of_prepositions[i]) {
            return true;
        }
    }
    return false;
}
//функция проверки на обстоятельственный предлог
bool is_obst_preposition(const string& word) { 
    for (int i = 0; i <obst_preposition ; i++) {
        if (word == mas_of_obst_preposition[i]) {
            return true;
        }
    }
    return false;
}
//функция проверки на наречие
bool is_obst(const string& word) { 
    for (int i = 0; i < obst_count; i++) {
        if (word == obst_word[i]) {
            return true;
        }
    }
    return false;
}
//функция проверки на местоимение
bool is_mest(const string& word) { 
    for (int i = 0; i < mest_count; i++) {
        if (word == mest_word[i]) {
            return true;
        }
    }
    return false;
}
//функция проверки на союз
bool is_unions(const string& word) { 
    for (int i = 0; i < count_of_unions_soch; i++) {
        if (word == mas_of_unions[i]) {
            return true;
        }
    }
    return false;
}
//функция проверки на исключения
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
//функция проверки на окончания глаголов
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
//функция проверки на прилагательные
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
//функция проверки на междометия
bool is_interjection(const string& word){
     for (int i = 0; i < count_interjections; i++) 
    {
        if (word == interjections[i]) {
            return true; 
        }
    }
    return false; 
}
//функция проверки  на частицы
bool is_particles(const string& word){
     for (int i = 0; i < count_particles; i++) 
    {
        if (word == particles[i]) {
            return true; 
        }
    }
    return false; 
}
//функция заполнения создания и заполнения массива слов рассматриваемого предложения
void create_words(string*& words_in_sentence, int word_start, int word_index, string& sentence)
{
    //Проверки на часто встречаемые знаки препинания

    for (int j = 0; j < sentence.length(); j++) {
            if (sentence[j] == ' ' || sentence[j] == '.' || sentence[j] == ',' || sentence[j] == ';'|| sentence[j] == ':' || sentence[j] == '!'|| sentence[j] == '?') 
            {
                if(sentence[j] == ',' )
                {
                    detect_comma = true;
                }
                if(sentence[j] == ';' )
                {
                    detect_semicolon = true;
                }
                if(sentence[j] == ':' )
                {
                    detect_ellipses = true;
                }
                if(sentence[j] == '.' )                
                {
                    detect_dot = true;
                }
                if(sentence[j] == '!' )                
                {
                    exclamation_mark = true;
                }
                if(sentence[j] == '?' )                 
                {
                    question_mark = true;
                }
                //в массив записывается слово от метки начала до метки конца обнаружения слова
                words_in_sentence[word_index] = sentence.substr(word_start, j - word_start);
                //т.к при записи в массив знаки препинания могли пропасть, то была сделана проверка, для того чтобы этого избежать
                if(detect_comma && words_in_sentence[word_index].empty())
                {
                    words_in_sentence[word_index] = ",";
                    detect_comma = false;
                }
                if(detect_ellipses && words_in_sentence[word_index].empty())
                {
                    words_in_sentence[word_index] = ":";
                    detect_ellipses = false;
                }
                if(detect_semicolon && words_in_sentence[word_index].empty())
                {
                    words_in_sentence[word_index] = ";";
                    detect_semicolon = false;
                }
                if(detect_dot && words_in_sentence[word_index].empty())       
                {
                    words_in_sentence[word_index] = ".";
                    detect_dot = false;
                }
                if(exclamation_mark && words_in_sentence[word_index].empty())        
                {
                    words_in_sentence[word_index] = "!";
                    exclamation_mark = false;
                }
                if(question_mark && words_in_sentence[word_index].empty())        
                {
                    words_in_sentence[word_index] = "?";
                    question_mark = false;
                }
                word_start = j + 1;
                word_index++;
            }
        }
}
 //функция для формирования последовательности вызовов функций анализа
void form_of_mass_of_sentence(string text, int sentence_count) 
{
    ofstream form_text(text_in);
    ofstream appearance_sent(task_output);
    int start_pos = 0;
    int current = 0;

    int word_start = 0;
    int word_index = 0;
    int word_count = 0;

    vector<string> remaining_words;

    string* mas_sentence = new string[sentence_count]; 
    //формирование массива предложений
        for(int i =0; i<text.length();i++)
        {
            if (text[i] == '.' || text[i] == '!' ||text[i] == '?')
            {
               mas_sentence[current] = text.substr(start_pos, i - start_pos + 1);  
               start_pos = i + 1;
               current++;
            }
        }
//нумерация предложения для файла split text
        for(int i =0; i<sentence_count;i++)
        {
            form_text<<i+1<<") "<<mas_sentence[i]<<endl;
        }
        form_text.close();
        
        for (int i = 0; i < sentence_count; i++) {
        string sentence = mas_sentence[i];
        word_count = 0;
        //подсчет кол-ва слов в предложении
        for (int j = 0; j < sentence.length(); j++) {
            if (sentence[j] == ' ' || sentence[j] == '.' || sentence[j] == ',' || sentence[j] == ';'|| sentence[j] == ':' || sentence[j] == '!'|| sentence[j] == '?') 
            {
                word_count++;
            }
        }
    //создание массива слов для рассматриваемого предложения
        string* words_in_sentence = new string[word_count];
        word_start = 0;
        word_index = 0;
        //вызов функции заполнения массива слов
        create_words(words_in_sentence, word_start, word_index, sentence);
        //вызов функции поиска и удаления оборотов из массива слов
        find_oborots( words_in_sentence, word_count);
     
        for (int i = 0; i < word_count; i++) 
        {
//проверка на слова после обстоятельственных предлогов
          if(i!=0  && is_obst_preposition(words_in_sentence[i-1]) == true){

                 for(int j=0;j<count_of_podl_endings;j++){

                      if(words_in_sentence[i].rfind(mas_of_podl_endings[j])!=-1 ||words_in_sentence[i]==mas_of_podl_endings[j] ){
                    // если после предлога есть слово с нужным окончанием, то оно удаляется
                      words_in_sentence[i].erase();
                      }
                 }
            }

        }
        //последовательная проверка элементов массива слов на предлоги, местоимения, частицы и т.д
        // если проверка выполняется, то слово удаляется
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
            // проверка на различные знаки препинания
            else if(words_in_sentence[i]=="—"|| words_in_sentence[i]=="-" || words_in_sentence[i]=="–"|| words_in_sentence[i].find('«')!=string::npos || words_in_sentence[i].find('»')!=string::npos ||
             words_in_sentence[i].find('"')!=string::npos )
            {
                words_in_sentence[i].erase();
      
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
    int current_word = 0;
    int count_v = 0;
    string number_sentence = ""; 

    //Вывод найденных дополнений в отформатированном виде

    appearance_sent<<"Всего найденных дополнений "<<remaining_words.size()<<endl<<endl;

    //Сортировка вектора

    sort(remaining_words.begin(),remaining_words.end());

    appearance_sent<<"Дополнение"<<setw(30)<<"Частота встречи"<<setw(30)<<"В предложениях"<<endl<<endl;
    for(int i = 0; i < remaining_words.size(); i++)
    {
        string* words_in_sentence;
        string number_predl = "";
        count_v = 0;
        for (int j = 0; j < sentence_count; j++) 
         { 
            word_count = 0;
            string sentence_2 = mas_sentence[j];

            //Снова разделяем предложения на слова

            for (int k = 0; k < sentence_2.length(); k++) 
            {
                if (sentence_2[k] == ' ' || sentence_2[k] == '.' || sentence_2[k] == ',' || sentence_2[k] == ';'|| sentence_2[k] == ':' || sentence_2[k] == '!'|| sentence_2[k] == '?') 
                {
                    word_count++;
                }   
             }
                words_in_sentence = new string[word_count];
                word_start = 0;
                word_index = 0;
                create_words(words_in_sentence, word_start, word_index, sentence_2);
            
            //Сравнение вектора дополнений со словами предложения

                for(int m = 0; m<word_count;m++)
                {
                    
                    if(words_in_sentence[m]==remaining_words[i])
                    {
                        //если выполняется то считаем кол-во вхождений и в каком предложении встретилось
                        count_v++;
                        number_predl+=" "+to_string(j+1);
                    }
                }
        }
        
        //Вывод в файл в читаемом формате
        appearance_sent<<remaining_words[i]<<setw(30-remaining_words[i].length())<<count_v<<setw(30+number_predl.length())<<number_predl<<endl;

        //Удаление разбитого на слова предложения
        delete[]words_in_sentence;
    }

    delete[] mas_sentence;

    
    appearance_sent.close();

    cout<<"Отформатированный текст хранится в файле split_text.txt"<<endl;
    cout<<"Список всех дополнений можно посмотреть в файле true_out.txt"<<endl;
}
}
//функция для удаления динамических массивов
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
int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL,"rus");
    string file_name;
    string filename;
       do {
        cout << "Введите название файла с (.txt): ";
        cin >> file_name;

        // Проверка, что последние четыре символа - это ".txt"
        if (file_name.length() < 4 || file_name.substr(file_name.length() - 4) != ".txt") {
            cout << "Файл должен иметь расширение .txt." << endl;
            continue; // Перезапуск цикла
        }

        // Попытка открыть файл для чтения
        ifstream file(file_name);
        if (file.is_open()) {
            file.close(); // Закрыть файл, если он был успешно открыт
        } else {
            cout << "Файл не существует, введите другое название" << endl;
        }

    } while (file_name.length() < 4 || file_name.substr(file_name.length() - 4) != ".txt" || !ifstream(file_name));

    ifstream input_file(file_name);
    string text;
    string sentence;

    //Запись текста в строчку

    while(getline(input_file, sentence))
    {
        text += sentence;
    }

    input_file.close();

    for (int i = 0; i < text.length(); i++) 
    {
            if (text[i] == '.' || text[i] == '?' || text[i] == '!') 
            {
                // Ищем все пробелы после точки, вопросительного или восклицательного знака и удаляем их
                while (i + 1 < text.length() && text[i + 1] == ' ') {
                    text.erase(i + 1, 1);
                }
            }
        }
    //заполнение динамичсеких массиво данными о предологах, местоимениях и т.д
    filling_array();
    // подсчет кол-ва предложений
    int sentence_count = find_sentence(text);

    form_of_mass_of_sentence(text, sentence_count); 

    //удаление массивов
    destroy_arr();
    system("pause");
    return 0;
}