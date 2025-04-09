#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include "school.h"

School::School(std::string id, std::string n)
        : schoolID(id), name(n){};
School::School(){
        schoolID="";
        name="";
    };
std::string School::getID(){    
        return schoolID;
    };
std::string School::getName(){
        return name;
    };
void School::saveInFile(std::string& id){
        std::string filePath="Schools/" +id+ ".txt";
        std::ofstream file(filePath);       
        file<<schoolID<<'\n';
        file<<name<<'\n';
        file.close();      
    };
bool School::isSchoolIDExists(std::string id){
        std::string path= "Schools/"+id+".txt";
        if(std::filesystem::exists(path)){
            return true;
        }else{
            return false;
        };
    };
    