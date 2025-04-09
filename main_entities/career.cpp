#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include "school.h"
#include "career.h"

Career::Career(std::string id, std::string n)
        : careerID(id), name(n){};
Career::Career(){
        careerID="";
        name="";
    };
std::string Career::getID(){    
        return careerID;
    };
std::string Career::getName(){
        return name;
    };
