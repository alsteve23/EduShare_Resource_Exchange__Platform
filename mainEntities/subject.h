#pragma once
#include<iostream>
#include "school.h"
#include "career.h"
#include <string>
#include <sqlite3.h>
#include <vector>
using namespace std;

class Subject{
    private: 
    string name;
    School* school;
    Career* career;
    int subjectID;
    public:
    Subject(int id,string name,School* f, Career* c);
    Subject();
    Subject(int id, string name);
    int getID() const;
    std::string getName() const;
    School* getSchool() const;
    Career* getCareer() const;
    static std::vector<Subject> listByCareer(sqlite3* db,int CareerID);
    void PrintSubjectsByCareer(sqlite3* db);
    void PrintSubjectsBySchool(sqlite3* db);    
};
