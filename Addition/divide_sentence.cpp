#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <iomanip>
const std::string file_name="splitted_text.txt";
const std::string outfile_name= "analyzed.txt";

enum Word_type{
   podlej, skaz, opred, dopol, obst, another, NA
};


struct Words_info{
    std::string data;
    Word_type type;
    int frequency;
    std::string sentences_included;
};
std::vector <Words_info> New_word;
std::vector<std::vector<Words_info>> Text;


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
                if(actual_sentence[i-1]==',' || actual_sentence[i-1]==':' || actual_sentence[i-1]==';' || actual_sentence[i-1]=='-'){
                    typed_word=actual_sentence.substr(space_point+1,i-space_point-2);
                    another_word=actual_sentence.substr(i-1,1);

                    temp_typed.data=typed_word;
                    temp_typed.type=NA;
                    New_word.push_back(temp_typed);

                    temp_another.data=another_word;
                    temp_another.type=another;
                    New_word.push_back(temp_another);
                }
                else{
                    typed_word=actual_sentence.substr(space_point+1,i-space_point);

                    temp_typed.data=typed_word;
                    temp_typed.type=NA;
                    New_word.push_back(temp_typed);

                }

               
                
                space_point=i;
            }
            if(i==len-1){//РєРѕРЅРµС† РїСЂРµРґР»РѕР¶РµРЅРёСЏ
                Words_info temp_typed;
                Words_info temp_another;
                std::string another_word="";
                std::string typed_word="";
                
                typed_word=actual_sentence.substr(space_point+1,i-space_point-1);
                another_word=actual_sentence.substr(i);

                temp_typed.data=typed_word;
                temp_typed.type=NA;
                New_word.push_back(temp_typed);

                temp_another.data=another_word;
                temp_another.type=another;
                New_word.push_back(temp_another);
                Text.push_back(New_word);
                New_word.clear();
                ///////


            }
        }
    }
}

std::string wordtype_to_word(int need_i, int need_j){
    switch(Text[need_i][need_j].type){
        case 0:return "Подлежащее";
        case 1:return "Сказуемое";
        case 2:return "Определение";
        case 3:return "Дополнение";
        case 4:return "Обстоятельство";
        case 5:return "Иное";
        case 6:return "НД";
        default:return "N/A";
    }
}

void word_with_same_name_and_type(int need_i, int need_j){
    int count = 0;
    std::vector<int> members={0};
    std::string list_of_members;
     for(int i=0;i<Text.size();i++){
       
        for(int j=0;j<Text[i].size();j++){
            if(i <= need_i  && Text[i][j].data==Text[need_i][need_j].data && Text[i][j].type==Text[need_i][need_j].type){
            count++; 
            members.push_back(i);
            list_of_members+=" "+std::to_string(i+1);
            }
        }
    }
    for(int k=0;k<members.size();k++){

        for(int i=0;i<Text.size();i++){
       
            for(int j=0;j<Text[i].size();j++){
                if(i==k && Text[i][j].data==Text[need_i][need_j].data && Text[i][j].type==Text[need_i][need_j].type ){
                    Text[i][j].frequency=count;
                    
                    for(int g=0;g<members.size();g++){
                        Text[i][j].sentences_included=list_of_members;
                         
                    }
                }
            }
        }
    }
    Text[need_i][need_j].frequency=count;
    for(int g=0;g<members.size();g++){
                        
        Text[need_i][need_j].sentences_included=list_of_members;  
    }
}

void analysis(){
    std::ofstream analyzed_info(outfile_name); 
    
     for(int i=0;i<Text.size();i++){
       
        for(int j=0;j<Text[i].size();j++){
            
            
            if(Text[i][j].type!=another){
            word_with_same_name_and_type(i, j);}
        
        }
    }
    for(int i=0;i<Text.size();i++){
       
        for(int j=0;j<Text[i].size();j++){
            analyzed_info<<"data: "<<Text[i][j].data<<std::setw(30-Text[i][j].data.length())<<" type: "<<wordtype_to_word(i,j)<<std::setw(32-wordtype_to_word(i,j).length())<<" frequency: "<<Text[i][j].frequency<<std::setw(30)<<" sentences_included: "<<Text[i][j].sentences_included<<std::endl;
        
        }
    }
}

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL,"rus");

    finding_words();
    /*
    for(int i=0;i<New_word.size();i++){
        std::cout<<"word:"<<New_word[i].data<<" type:"<<New_word[i].type<<std::endl;
    }*/
    Text[0][0].type=podlej;
    Text[0][1].type=skaz;
    Text[0][2].type=another;
    Text[0][3].type=dopol;
    Text[0][4].type=another;
    Text[0][5].type=obst;
    Text[0][6].type=another;
    Text[0][7].type=another;
    Text[0][8].type=obst;
    Text[0][9].type=skaz;
    Text[0][10].type=opred;
    Text[0][11].type=opred;
    Text[0][12].type=dopol;

    Text[1][0].type=opred;
    Text[1][1].type=opred;
    Text[1][2].type=opred;
    Text[1][3].type=opred;
    Text[1][4].type=opred;
    Text[1][5].type=another;
    Text[1][6].type=podlej;
    Text[1][7].type=skaz;
    Text[1][8].type=opred;
    Text[1][9].type=dopol;

    Text[2][0].type=another;
    Text[2][1].type=obst;
    Text[2][2].type=another;
    Text[2][3].type=another;
    Text[2][4].type=another;
    Text[2][5].type=skaz;
    Text[2][6].type=another;
    Text[2][7].type=dopol;
    Text[2][8].type=another;
    Text[2][9].type=dopol;
    Text[2][10].type=another;
    Text[2][11].type=dopol;
    Text[2][12].type=another;
    Text[2][13].type=dopol;
    Text[2][14].type=another;

    Text[3][0].type=podlej;
    Text[3][1].type=skaz;
    Text[3][2].type=another;
    Text[3][3].type=dopol;
    Text[3][4].type=another;
    Text[3][5].type=obst;
    Text[3][6].type=another;
    Text[3][7].type=opred;
    Text[3][8].type=opred;
    Text[3][9].type=dopol;
    Text[3][10].type=another;
    Text[3][11].type=obst;
    Text[3][12].type=obst;
    Text[3][13].type=skaz;
    Text[3][14].type=skaz;
    Text[3][15].type=dopol;

    for(int i=0;i<Text.size();i++){
       
        for(int j=0;j<Text[i].size();j++){
            
            if(Text[i][j].data[0]>=-64 &&Text[i][j].data[0]<=-33){
                Text[i][j].data[0]+=32;
            }
        
        }
    }
    for(int i=0;i<Text.size();i++){
        std::cout<<"sentence "<<i+1<<std::endl;
        for(int j=0;j<Text[i].size();j++){
        
        std::cout<<"word:"<<Text[i][j].data<<" type:"<<Text[i][j].type<<std::endl;
        }
    }

    analysis();

    //system("pause");
}