
#include<iostream>
#include "school.h"
#include "career.h"
#include "subject.h"

Subject::Subject(int id, std::string n,School* f, Career* c)
        : subjectID(id), name(n),school(f),career(c){};
Subject::Subject(){
        subjectID=0;
        name="";
        school=nullptr;
        career=nullptr;
    };
int Subject::getID() const {    
        return subjectID;
    };
std::string Subject::getName() const {
        return name;
    };


