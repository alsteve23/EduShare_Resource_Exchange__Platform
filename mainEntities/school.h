#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include<sqlite3.h>
#include <string>
#include <vector>
#include<optional>
using namespace std;

class School{
    private:
    std::string name;
    int schoolID;
    public:
    //constructors
    School(int id, const std::string n);
    School();
    School(const string name);
    //getters
    int getID() const;
    std::string getName() const;
    //static methods to filter school
    static optional<School> fromID(sqlite3* db, int id);
    static std::vector<School> listAll(sqlite3* db);
    ///print method
    static void printAll(vector<School>& schools); 
    //ADD and DELETE methods
    bool addSchool(sqlite3*db);
    bool deleteSchool(sqlite3* db);
    
};