#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include<sqlite3.h>
#include <string>
#include <vector>
using namespace std;

class School{
    private:
    std::string name;
    int schoolID;
    public:
    
    School(int id, const std::string n);
    School();
    int getID() const;
    std::string getName() const;
    static std::vector<School> listAll(sqlite3* db);
    void printAll(sqlite3* db); 
    
};