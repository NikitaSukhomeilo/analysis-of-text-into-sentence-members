#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>



using namespace std;

//����� ��� ������ ����������
bool detect_comma = false; //false - �� ����������, true - ���������� �������
bool detect_ellipses = false;  //false - �� ����������, true - ���������� ���������
bool detect_semicolon = false; //false - �� ����������, true - ���������� ����� � �������
bool detect_dot = false; //false - �� ����������, true - ���������� �����
bool question_mark = false;  //false - �� ���������, true - ��������� �������������� ����
bool exclamation_mark = false; //false - �� ���������, true - ��������� ��������������� ����

//������� � ��������

string *exceptions; // ������ ����������
string *mas_of_endings_verb;    //������ ��������� ��������
string *mas_of_prepositions;    //����� ���������
string *mas_of_obst_preposition; //������ ��������� ��������������
string *mas_of_suffiks_of_oborot;//������ ���������
string *mas_of_unions;    //������ ������
string *mas_of_podl_endings;    //������ ��������� �����������
string *mas_of_adjectives;  //������ �����������
string *obst_word;  //������ �������
string *mest_word;  //������ �����������
string *particles;  //������ ������
string *interjections; //������ ����������

int endings_count = 0;  //������� ������� ��������� ��������
int exception_count = 0;    //������� ������� ����������
int prepositions_count = 0; //������� ������� ���������
int obst_preposition = 0;   //������� ������� ��������� ��������������
int obst_count = 0;     //������� ������� �������
int mest_count = 0;     //������� ������� �����������
int count_of_suffiks_of_oborot = 0;     //������� ������� ���������
int count_of_unions_soch = 0;       //������� ������� ������
int count_of_podl_endings = 0;      // ������� ������� ����������
int endings_adjectives = 0;     //������� ������� �����������
int count_particles = 0;        //������� ������� ������
int count_interjections = 0;    //������� ������� ����������

//��������� ������� ��������(�������)
bool is_verb(const string& word);  //������� �������� �� ������
bool is_preposition(const string& word); //������� �������� �� �������
bool is_unions(const string& word); //������� �������� �� �����
bool is_obst(const string& word); //������� �������� �� �������
bool is_mest(const string& word); //������� �������� �� �����������
bool is_exception(const string& word); //������� �������� �� ����������
bool is_adjective(const string& word); //������� �������� �� ����������
bool is_interjection(const string& word); //������� �������� �� ����������
bool is_particles(const string& word); //�������� �������� �� �������


//��������� ������� �������
void find_oborots(string* words_in_sentence, int word_count); //������� ������ ����������/ ������������� ��������
void form_of_mass_of_sentence(string text, int sentence_count); //������� ��� ������������ ������������������ ������� ������� �������


//��������� ������� ����������
int countLines(const string& general_file, const string& startMarker, const string& endMarker, string*& temp_array); //������� ������������ �������� ������, ��������� � �.�
int find_sentence(string text); //������� �������� ���-�� ����������� � ������
string* create_array(int count); //������� ��� �������� ������������� �������
void filling_array();//������� ��� ���������� �������� ������, ��������� � �.�


//������� �����
const string general_file = "all_information.txt"; //� ������ ����� �������� �������, ��������, ��������� �������� � �.�
const string text_in = "split_text.txt"; //� ������ ����� ����� �������� ����� � ���������������� �������������
const string task_output ="true_out.txt"; //�������� ���� � ������������ ������� �� ����������

int counter = 0;

//������� ������������ �������� ������, ��������� � �.�
int countLines(const string& general_file, const string& startMarker, const string& endMarker, string*& temp_array) {
    ifstream file(general_file); //
    string line;
    bool shouldRead = false; //���� ������� ������������ ���������� ����� ������� start � end
    int wordCount = 0;

    // ���������� ������ �� �����, ���� ������ ������ start, �� ���� ��� ���������� ������������
    // ���� ���������� ����� end, �� ���� ��� ���������� ��������������
    while (getline(file, line)) {
        if (line == startMarker) {
            shouldRead = true;
            continue;
        } else if (line == endMarker) {
            shouldRead = false;
            break;
        }

        if (shouldRead) {
            istringstream iss(line); //���������� ������
            string word;
            while (iss >> word) {
                wordCount++; // ������� ���-�� ���� ����� �������
            }
        }
    }

    //����� ��������� � ����� � ������ ��� ���������� ������
    file.clear();  
    file.seekg(0, ios::beg);

    int index = 0; 
    //�������� ������������� �������
    temp_array = new string[wordCount];
    //��������� ���������� ������ ����� �������, ������ ��� �� ��� �������� ���-�� ����,
    // � ��� ���������� �������
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
                temp_array[index] = word; // ������ ����� � ������
                index++;
            }
        }
    }
     file.close();
    return wordCount; //������������ �������� - ���-�� ����
}

 //������� ��� �������� ������������� �������
string* create_array(int count){
    string *a;
    a = new string[count];
    return a;
}

//���������� �������� ������� �� ������
void filling_array()
{
    
    string *temp_array = nullptr;
    //���������� ������� ��� �������� ���-�� ���� ����� ���������������� ������� � ����� general_file
    //� �������� ������������� ������� � ���������� ������� �� �����
    endings_count = countLines(general_file, "�������:", "�����1", temp_array);
    mas_of_endings_verb = create_array(endings_count);
    // ������ ��������� ��������
    for( int i = 0; i<endings_count;i++)
    {
        //�� ��������� ������� �������� ��������� ������ �� �����
        //������� � ������ ����� ������������ � ������ ������������ ������
        mas_of_endings_verb[i] = temp_array[i];
    }
    delete[]temp_array;
    temp_array = nullptr;
    //������ ���������
    prepositions_count = countLines(general_file, "��������:", "�����2", temp_array);
    mas_of_prepositions = create_array(prepositions_count);

    for( int i = 0; i<prepositions_count; i++)
    {
        mas_of_prepositions[i] = temp_array[i];
    }
    
    delete[]temp_array;
    temp_array = nullptr;
    //������ ���������
    count_of_suffiks_of_oborot = countLines(general_file, "��������:", "�����3", temp_array);
    mas_of_suffiks_of_oborot = create_array(count_of_suffiks_of_oborot);

    for( int i = 0; i<count_of_suffiks_of_oborot; i++)
    {
        mas_of_suffiks_of_oborot[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //������ ������
    count_of_unions_soch = countLines(general_file, "�����:", "�����4", temp_array);
    mas_of_unions = create_array(count_of_unions_soch);

    for( int i = 0; i<count_of_unions_soch; i++)
    {
        mas_of_unions[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //������ ������������������ ���������
    obst_preposition = countLines(general_file, "������������������-��������:", "�����5", temp_array);
    mas_of_obst_preposition = create_array(obst_preposition);

    for( int i = 0; i<obst_preposition;i++)
    {
        mas_of_obst_preposition[i] = temp_array[i];
    }
    delete[]temp_array;
    temp_array = nullptr;
    // ������ ��������� ����������
    count_of_podl_endings = countLines(general_file, "����������:", "�����6", temp_array);
    mas_of_podl_endings = create_array(count_of_podl_endings);

    for( int i = 0; i<count_of_podl_endings; i++)
    {
        mas_of_podl_endings[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //������ ��������� ��������������
    endings_adjectives = countLines(general_file, "�����������:", "�����7", temp_array);
    mas_of_adjectives = create_array(endings_adjectives);

    for( int i = 0; i<endings_adjectives; i++)
    {
        mas_of_adjectives[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    // ������ �����������
    mest_count = countLines(general_file, "�����������:", "�����8", temp_array);
    mest_word = create_array(mest_count);

    for( int i = 0; i<mest_count; i++)
    {
        mest_word[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //������ ����������
    exception_count = countLines(general_file, "����������:", "�����9", temp_array);
    exceptions = create_array(exception_count);

    for( int i = 0; i<exception_count; i++)
    {
        exceptions[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //������ �������
    obst_count = countLines(general_file, "�������:", "�����10", temp_array);
    obst_word = create_array(obst_count);

    for( int i = 0; i<obst_count; i++)
    {
        obst_word[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //������ ������
    count_particles = countLines(general_file, "�������:", "�����11", temp_array);
    particles = create_array(count_particles);

    for( int i = 0; i<count_particles; i++)
    {
        particles[i] = temp_array[i];
    }

    delete[]temp_array;
    temp_array = nullptr;
    //������ ����������
    count_interjections = countLines(general_file, "����������:", "�����12", temp_array);
    interjections = create_array(count_interjections);

    for( int i = 0; i<count_interjections; i++)
    {
        interjections[i] = temp_array[i];
    }
    
    delete[]temp_array;
    temp_array = nullptr;
}

//������� ������ ����������/������������� ��������
void find_oborots(string* words_in_sentence,int word_count){

    //������ ������ ������� ����������/������������� ��������

     bool oborot_found=false; //���� ��� ����������� �������
     int oborot_start=0; //������ �������
     int oborot_finish=0; //����� �������

    for(int k=0;k<count_of_unions_soch;k++){
    
    for(int i=1;i<word_count;i++){

       if((words_in_sentence[i-1]=="," && oborot_found==false)||( is_particles(words_in_sentence[i-1]) && oborot_found==false)){
           
           for(int j=0;j<count_of_suffiks_of_oborot;j++){

            if(words_in_sentence[i].rfind(mas_of_suffiks_of_oborot[j])!=-1){
                oborot_found = true;
                oborot_start = i-1; //���� ������ ������ ����������� ����� ������ � ���� ������� ����������
                
            }

           }
       }
    }
    for(int i=1; i < word_count; i++){
      
      if(words_in_sentence[i-1]=="," && oborot_found==true && oborot_start <= i-1  && oborot_start != i-1 ){

         for(int j=0;j<count_of_suffiks_of_oborot;j++){

            if(words_in_sentence[i].rfind(mas_of_suffiks_of_oborot[j])==-1){
                oborot_found = false;
                oborot_finish = i; // ��� ������ ������ ����� �������, �� ��� ����� ����������� � ���� �����������
               
            }
            if(words_in_sentence[i].rfind(mas_of_suffiks_of_oborot[j])!=-1){
                oborot_found = true; //���� ������� ����� � �������� ������� ������� �� ������� ���������
                // �� ������ ���������
            }
           }
       }
       else if(words_in_sentence[i]=="." && oborot_found==true){
        oborot_found = false;
        oborot_finish = i; //���� ����������� ����� �������, ���� �� � ����� �����������
       }
    
    }
   
    for(int i = oborot_start;i < oborot_finish;i++){

     words_in_sentence[i].erase(); //�������� ������� �� �������

    }

}
}

//������� �������� ���-�� ����������� � ������
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

//������� �������� �� �������
bool is_preposition(const string& word) { 
    for (int i = 0; i < prepositions_count; i++) {
        if (word == mas_of_prepositions[i]) {
            return true;
        }
    }
    return false;
}
//������� �������� �� ������������������ �������
bool is_obst_preposition(const string& word) { 
    for (int i = 0; i <obst_preposition ; i++) {
        if (word == mas_of_obst_preposition[i]) {
            return true;
        }
    }
    return false;
}
//������� �������� �� �������
bool is_obst(const string& word) { 
    for (int i = 0; i < obst_count; i++) {
        if (word == obst_word[i]) {
            return true;
        }
    }
    return false;
}
//������� �������� �� �����������
bool is_mest(const string& word) { 
    for (int i = 0; i < mest_count; i++) {
        if (word == mest_word[i]) {
            return true;
        }
    }
    return false;
}
//������� �������� �� ����
bool is_unions(const string& word) { 
    for (int i = 0; i < count_of_unions_soch; i++) {
        if (word == mas_of_unions[i]) {
            return true;
        }
    }
    return false;
}
//������� �������� �� ����������
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
//������� �������� �� ��������� ��������
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
//������� �������� �� ��������������
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
//������� �������� �� ����������
bool is_interjection(const string& word){
     for (int i = 0; i < count_interjections; i++) 
    {
        if (word == interjections[i]) {
            return true; 
        }
    }
    return false; 
}
//������� ��������  �� �������
bool is_particles(const string& word){
     for (int i = 0; i < count_particles; i++) 
    {
        if (word == particles[i]) {
            return true; 
        }
    }
    return false; 
}
//������� ���������� �������� � ���������� ������� ���� ���������������� �����������
void create_words(string*& words_in_sentence, int word_start, int word_index, string& sentence)
{
    //�������� �� ����� ����������� ����� ����������

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
                //� ������ ������������ ����� �� ����� ������ �� ����� ����� ����������� �����
                words_in_sentence[word_index] = sentence.substr(word_start, j - word_start);
                //�.� ��� ������ � ������ ����� ���������� ����� ��������, �� ���� ������� ��������, ��� ���� ����� ����� ��������
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
 //������� ��� ������������ ������������������ ������� ������� �������
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
    //������������ ������� �����������
        for(int i =0; i<text.length();i++)
        {
            if (text[i] == '.' || text[i] == '!' ||text[i] == '?')
            {
               mas_sentence[current] = text.substr(start_pos, i - start_pos + 1);  
               start_pos = i + 1;
               current++;
            }
        }
//��������� ����������� ��� ����� split text
        for(int i =0; i<sentence_count;i++)
        {
            form_text<<i+1<<") "<<mas_sentence[i]<<endl;
        }
        form_text.close();
        
        for (int i = 0; i < sentence_count; i++) {
        string sentence = mas_sentence[i];
        word_count = 0;
        //������� ���-�� ���� � �����������
        for (int j = 0; j < sentence.length(); j++) {
            if (sentence[j] == ' ' || sentence[j] == '.' || sentence[j] == ',' || sentence[j] == ';'|| sentence[j] == ':' || sentence[j] == '!'|| sentence[j] == '?') 
            {
                word_count++;
            }
        }
    //�������� ������� ���� ��� ���������������� �����������
        string* words_in_sentence = new string[word_count];
        word_start = 0;
        word_index = 0;
        //����� ������� ���������� ������� ����
        create_words(words_in_sentence, word_start, word_index, sentence);
        //����� ������� ������ � �������� �������� �� ������� ����
        find_oborots( words_in_sentence, word_count);
     
        for (int i = 0; i < word_count; i++) 
        {
//�������� �� ����� ����� ������������������ ���������
          if(i!=0  && is_obst_preposition(words_in_sentence[i-1]) == true){

                 for(int j=0;j<count_of_podl_endings;j++){

                      if(words_in_sentence[i].rfind(mas_of_podl_endings[j])!=-1 ||words_in_sentence[i]==mas_of_podl_endings[j] ){
                    // ���� ����� �������� ���� ����� � ������ ����������, �� ��� ���������
                      words_in_sentence[i].erase();
                      }
                 }
            }

        }
        //���������������� �������� ��������� ������� ���� �� ��������, �����������, ������� � �.�
        // ���� �������� �����������, �� ����� ���������
       for (int i = 0; i < word_count; i++) 
        {
             string lower_word = words_in_sentence[i];  //������� � ������ ������� ��� �������

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
            // �������� �� ��������� ����� ����������
            else if(words_in_sentence[i]=="�"|| words_in_sentence[i]=="-" || words_in_sentence[i]=="�"|| words_in_sentence[i].find('�')!=string::npos || words_in_sentence[i].find('�')!=string::npos ||
             words_in_sentence[i].find('"')!=string::npos )
            {
                words_in_sentence[i].erase();
      
        }
        //���������� ������� ���� �������. ������� �������� ����� ������� ������(�.� �������������� ����������)

        bool detect_vector_str = false;
        for(int i = 0;i< word_count;i++)
        {
            detect_vector_str = false;
            if(!words_in_sentence[i].empty()&& words_in_sentence[i]!="�" && words_in_sentence[i]!="." && words_in_sentence[i]!="," && 
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

    //����� ��������� ���������� � ����������������� ����

    appearance_sent<<"����� ��������� ���������� "<<remaining_words.size()<<endl<<endl;

    //���������� �������

    sort(remaining_words.begin(),remaining_words.end());

    appearance_sent<<"����������"<<setw(30)<<"������� �������"<<setw(30)<<"� ������������"<<endl<<endl;
    for(int i = 0; i < remaining_words.size(); i++)
    {
        string* words_in_sentence;
        string number_predl = "";
        count_v = 0;
        for (int j = 0; j < sentence_count; j++) 
         { 
            word_count = 0;
            string sentence_2 = mas_sentence[j];

            //����� ��������� ����������� �� �����

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
            
            //��������� ������� ���������� �� ������� �����������

                for(int m = 0; m<word_count;m++)
                {
                    
                    if(words_in_sentence[m]==remaining_words[i])
                    {
                        //���� ����������� �� ������� ���-�� ��������� � � ����� ����������� �����������
                        count_v++;
                        number_predl+=" "+to_string(j+1);
                    }
                }
        }
        
        //����� � ���� � �������� �������
        appearance_sent<<remaining_words[i]<<setw(30-remaining_words[i].length())<<count_v<<setw(30+number_predl.length())<<number_predl<<endl;

        //�������� ��������� �� ����� �����������
        delete[]words_in_sentence;
    }

    delete[] mas_sentence;

    
    appearance_sent.close();

    cout<<"����������������� ����� �������� � ����� split_text.txt"<<endl;
    cout<<"������ ���� ���������� ����� ���������� � ����� true_out.txt"<<endl;
}
}
//������� ��� �������� ������������ ��������
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
        cout << "������� �������� ����� � (.txt): ";
        cin >> file_name;

        // ��������, ��� ��������� ������ ������� - ��� ".txt"
        if (file_name.length() < 4 || file_name.substr(file_name.length() - 4) != ".txt") {
            cout << "���� ������ ����� ���������� .txt." << endl;
            continue; // ���������� �����
        }

        // ������� ������� ���� ��� ������
        ifstream file(file_name);
        if (file.is_open()) {
            file.close(); // ������� ����, ���� �� ��� ������� ������
        } else {
            cout << "���� �� ����������, ������� ������ ��������" << endl;
        }

    } while (file_name.length() < 4 || file_name.substr(file_name.length() - 4) != ".txt" || !ifstream(file_name));

    ifstream input_file(file_name);
    string text;
    string sentence;

    //������ ������ � �������

    while(getline(input_file, sentence))
    {
        text += sentence;
    }

    input_file.close();

    for (int i = 0; i < text.length(); i++) 
    {
            if (text[i] == '.' || text[i] == '?' || text[i] == '!') 
            {
                // ���� ��� ������� ����� �����, ��������������� ��� ���������������� ����� � ������� ��
                while (i + 1 < text.length() && text[i + 1] == ' ') {
                    text.erase(i + 1, 1);
                }
            }
        }
    //���������� ������������ ������� ������� � ����������, ������������ � �.�
    filling_array();
    // ������� ���-�� �����������
    int sentence_count = find_sentence(text);

    form_of_mass_of_sentence(text, sentence_count); 

    //�������� ��������
    destroy_arr();
    system("pause");
    return 0;
}