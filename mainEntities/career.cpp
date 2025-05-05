#pragma once
#include<iostream>
#include "school.h"
#include "career.h"

Career::Career(int id, std::string n,School* f)
        : careerID(id), name(n),school(f){};
Career::Career(){
        careerID=0;
        name="";
        school=nullptr;
    };
int Career::getID(){    
        return careerID;
    };
std::string Career::getName(){
        return name;
    };
