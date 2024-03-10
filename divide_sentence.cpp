#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

const std::string file_name="splitted_text.txt";

enum Word_type{
   podlej, skaz, opred, dopol, obst, another, NA
};


struct Words_info{
    std::string actual_word;
    Word_type word_info;
};

std::vector <Words_info> New_word;

void finding_words(){
    std::ifstream file_to_read(file_name);
    std::string actual_sentence=" ";
    while(file_to_read.eof()==false){
        getline(file_to_read,actual_sentence);
        int space_point=1;
        int len = actual_sentence.length();
        for(int i = 0; i < actual_sentence.length(); i++){
           
            if(actual_sentence[i]==' ' ){
                Words_info temp_typed;
                Words_info temp_another;
                std::string another_word="";
                std::string typed_word="";
                if(actual_sentence[i-1]==',' || actual_sentence[i-1]==':' || actual_sentence[i-1]==';'){
                    typed_word=actual_sentence.substr(space_point+1,i-space_point-2);
                    another_word=actual_sentence.substr(i-1,1);

                    temp_typed.actual_word=typed_word;
                    temp_typed.word_info=NA;
                    New_word.push_back(temp_typed);

                    temp_another.actual_word=another_word;
                    temp_another.word_info=another;
                    New_word.push_back(temp_another);
                }
                else{
                    typed_word=actual_sentence.substr(space_point+1,i-space_point);

                    temp_typed.actual_word=typed_word;
                    temp_typed.word_info=NA;
                    New_word.push_back(temp_typed);

                }

               
                
                space_point=i;
            }
            if(i==len-1){
                Words_info temp_typed;
                Words_info temp_another;
                std::string another_word="";
                std::string typed_word="";
                
                typed_word=actual_sentence.substr(space_point+1,i-space_point-1);
                another_word=actual_sentence.substr(i);

                temp_typed.actual_word=typed_word;
                temp_typed.word_info=NA;
                New_word.push_back(temp_typed);

                temp_another.actual_word=another_word;
                temp_another.word_info=another;
                New_word.push_back(temp_another);


            }
        }
    }
}

int main(){
     SetConsoleCP(1251);//задание русского языка в консоль
     SetConsoleOutputCP(1251);
     setlocale(LC_ALL,"rus");

    finding_words();
    for(int i=0;i<New_word.size();i++){
        std::cout<<"word:"<<New_word[i].actual_word<<" type:"<<New_word[i].word_info<<std::endl;
    }
    system("pause");
}