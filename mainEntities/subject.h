#pragma once
#include<iostream>
#include "school.h"
#include "career.h"

class Subject{
    private: 
    std::string name;
    School* school;
    Career* career;
    int subjectID;
    public:
    Subject(int id, std::string name,School* f, Career* c);
    Subject();
    int getID() const;
    std::string getName() const;
};
