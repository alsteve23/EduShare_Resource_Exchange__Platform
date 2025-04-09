#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>

class School{
    private:
    std::string schoolID, name;
    public:
    School(std::string id, std::string n);
    School();
    std::string getID();
    std::string getName();
    void saveInFile(std::string& id);
    bool isSchoolIDExists(std::string id);
};