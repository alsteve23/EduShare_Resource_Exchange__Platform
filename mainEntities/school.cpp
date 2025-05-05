#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include "school.h"

School::School(int id, std::string n)
        : schoolID(id), name(n){};
School::School(){
        schoolID=0;
        name="";
    };
int School::getID()const {    
        return schoolID;
    };
std::string School::getName() const {
        return name;
    };
    
    

    