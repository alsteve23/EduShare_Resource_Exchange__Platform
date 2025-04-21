#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include "school.h"
#include "career.h"

Career::Career(int id, std::string n)
        : careerID(id), name(n){};
Career::Career(){
        careerID=0;
        name="";
    };
int Career::getID(){    
        return careerID;
    };
std::string Career::getName(){
        return name;
    };
