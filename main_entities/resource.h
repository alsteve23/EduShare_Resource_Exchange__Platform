#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
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
    Resource(int id, std::string n);
    Resource();
    int getID() const;
    std::string getName() const;
    std::string getType() const;
    Resource(School* f) : school(f) {};
    Resource(Career* f) : career(f) {};
    Resource(Subject* f) : subject(f) {};

};