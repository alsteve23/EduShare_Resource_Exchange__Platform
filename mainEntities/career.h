#pragma once
#include<iostream>
#include "school.h"
#include <string>
#include <sqlite3.h>
#include <vector>
using namespace std;  
class Career{
    private:
    string name;
    School* school;
    int careerID;
    public:
    Career(int id,string n,School* f);
    Career();
    Career(int id, string name);
    int getID()const;
    string getName()const;
    School* getSchool()const;
    static vector<Career> listBySchool(sqlite3* db,int SchoolID);
    void PrintCareersBySchool(sqlite3* db);
};