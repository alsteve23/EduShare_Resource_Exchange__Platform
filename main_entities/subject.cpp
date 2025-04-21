#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include "school.h"
#include "career.h"
#include "subject.h"

Subject::Subject(int id, std::string n)
        : subjectID(id), name(n){};
Subject::Subject(){
        subjectID=0;
        name="";
    };
int Subject::getID() const {    
        return subjectID;
    };
std::string Subject::getName() const {
        return name;
    };