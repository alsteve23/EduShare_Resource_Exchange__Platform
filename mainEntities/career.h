#pragma once
#include<iostream>
#include "school.h"

class Career{
    private:
    std::string name;
    School* school;
    int careerID;
    public:
    Career(int id, std::string n,School* f);
    Career();
    int getID();
    std::string getName();
};