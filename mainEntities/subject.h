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
    int subjectID;
    int careerID,schoolID;
    public:
    //constructors
    Subject(int id,string name,int careerID, int schoolID);
    Subject();
    Subject(int id, string name);
    //getters
    int getID() const;
    std::string getName() const;
    int getcareerID()const;
    int getschoolID()const;
    static std::vector<Subject>fromCareer(sqlite3* db, int careerID);
    static std::vector<Subject> fromSchool(sqlite3* db,int schoolID);
    static void PrintSubjects(std::vector<Subject>& subjects);  
    //ADD and DELETE methods
    bool addSubject(sqlite3* db);
    bool deleteSubject(sqlite3* db);

};
