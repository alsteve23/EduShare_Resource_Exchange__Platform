#pragma once
#include<iostream>
#include<string>
#include<fstream>

class NewResource{
    private:
    std::string name,description;
    public:
    NewResource(std::string n, std::string d)
        : name(n), description(d){};
    std::string getName(){
        return name;
    };
    std::string getDescription(){
        return description;
    };
    void saveInFile(std::string& name){
        std::string filePath="Resources/" +name+ ".txt";
        std::ofstream file(filePath);       
        file<<name<<'\n';
        file<<description<<'\n';
        file.close();      
    };

};
