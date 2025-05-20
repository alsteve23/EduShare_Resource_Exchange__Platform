#pragma once
#include<iostream>
#include "school.h"
#include "career.h"
#include "subject.h"
#include <optional>

class Resource{
    private:
    std::string name;
    int schoolID;
    int careerID;
    int subjectID;
    int resourceID;
    std::vector<unsigned char> fileData;
    public:
    //constructores
    Resource(int id, std::string n,int f, int c,int s, std::vector<unsigned char> fileData);
    Resource(std::string n,int f, int c,int s, std::vector<unsigned char> fileData);
    Resource();
    Resource(int id, string name);
    //getters
    int getID() const;
    std::string getName() const;
    int getSchool() const;
    int getCareer() const;
    int getSubject() const;
    string getPath() const;
    vector<unsigned char> getFileData();
    //flitros de materia que devuelven un recurso único
    static optional<Resource> fromID(sqlite3* db,const int &ID);
    static optional<Resource> fromName(sqlite3* db,const string& name);
    //filtros de materia que devuelven un vector de los recursos con el ID y el nombre
    static vector<Resource> fromSubject(sqlite3* db,int SubjectID);
    static vector<Resource> fromCareer(sqlite3* db, const int& careerID);    
    static vector<Resource> fromSchool(sqlite3* db,int schoolID);
    //imprime los recursos que ya han sido filtrados por alguno de los métodos pasados.
    static void PrintResources(vector<Resource>& resources);
    bool UploadResource(sqlite3* db);
    bool downloadResource(sqlite3* db, const string& outputPath);
    //DELETE method
    bool deleteResource(sqlite3* db);
};