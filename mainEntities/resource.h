#pragma once
#include<iostream>
#include "school.h"
#include "career.h"
#include "subject.h"

class Resource{
    private:
    std::string name;
    School* school;
    Career* career;
    Subject* subject;
    int resourceID;
    std::string Type;
    public:
    Resource(int id, std::string n,School* f, Career* c, Subject* s );
    Resource();
    int getID() const;
    std::string getName() const;
    std::string getType() const;
};