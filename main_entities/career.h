#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include "school.h"

class Career{
    private:
    std::string careerID, name;
    public:
    Career(std::string id, std::string n);
    Career();
    std::string getID();
    std::string getName();
    void saveInFile(std::string& id);
    bool isCareerIDExists(std::string id);
};