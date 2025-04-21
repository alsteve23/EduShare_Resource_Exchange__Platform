#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include "school.h"
#include "career.h"

class Subject{
    private: 
    std::string name;
    School* school;
    Career* career;
    int subjectID;
    public:
    Subject(int id, std::string name);
    Subject();
    int getID() const;
    std::string getName() const;
    Subject(School* f) : school(f) {};
    Subject(Career* f) : career(f) {};
};
