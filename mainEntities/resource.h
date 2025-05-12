#pragma once
#include<iostream>
#include "school.h"
#include "career.h"
#include "subject.h"

class Resource{
    private:
    std::string name;
    int schoolID;
    int careerID;
    int subjectID;
    int resourceID;
    string path;
    std::vector<unsigned char> fileData;
    public:
    Resource(int id, std::string n,int f, int c,int s,string p, std::vector<unsigned char> fileData);
    Resource();
    Resource(int id, string name);
    Resource(int id);
    int getID() const;
    std::string getName() const;
    int getSchool() const;
    int getCareer() const;
    int getSubject() const;
    string getPath() const;
    vector<unsigned char> getFileData();
    static std::vector<Resource> listBySubject(sqlite3* db,int SubjectID);
    void PrintResourcesBySubject(sqlite3* db);
    bool UploadResource(sqlite3* db);
    bool downloadResource(sqlite3* db, int rID, const string& outputPath);
};