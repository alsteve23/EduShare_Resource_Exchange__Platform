#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>

class School{
    private:
    std::string name;
    int schoolID;
    public:
    School(int id, const std::string n);
    School();
    int getID() const;
    std::string getName() const;
    
};