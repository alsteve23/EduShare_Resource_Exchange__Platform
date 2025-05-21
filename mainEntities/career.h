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
    int schoolID;
    int careerID;
    public:
    Career(int id,string n,int f);
    Career();
    Career(int id, string name);
    Career(string name, int schoolID);
    Career(int id);
    int getID()const; 
    string getName()const;
    int getSchoolID()const;
    //static methods that filter careers
    static vector<Career> fromSchool(sqlite3* db,int SchoolID);
    static void PrintCareers(vector<Career>& careers);
    //ADD and DELETE methods
    bool addCareer(sqlite3*db);
    bool deleteCareer(sqlite3* db);

};