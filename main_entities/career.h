#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include "school.h"

class Career{
    private:
    std::string name;
    School* school;
    int careerID;
    public:
    Career(int id, std::string n);
    Career();
    int getID();
    std::string getName();
    Career(School* f) : school(f) {}
    Career(int id) : careerID(id) {}
};