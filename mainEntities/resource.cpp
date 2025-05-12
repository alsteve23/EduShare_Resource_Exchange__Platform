
#include<iostream>
#include "school.h"
#include "career.h"
#include "subject.h"
#include "resource.h"
#include <string>
#include <sqlite3.h>
#include <vector>
using namespace std;

Resource::Resource(int id, string n,int f, int c, int s,string p, vector<unsigned char> fileData)
        : resourceID(id), name(n),schoolID(f),careerID(c),subjectID(s),fileData(fileData),path(p){};
Resource::Resource(){
        resourceID=0;
        name="";
        schoolID=0;
        careerID=0;
        subjectID=0;
        path="";
        fileData.clear();
    };
Resource::Resource(int id, string name)
        : resourceID(id), name(name), schoolID(0), careerID(0), subjectID(0), path(""){};
Resource::Resource(int id)
        : resourceID(id), name(""), schoolID(0), careerID(0), subjectID(0), path(""){};
int Resource::getID() const {    
        return resourceID;
    };
std::string Resource::getName() const {
        return name;
    };

int Resource::getSchool() const {
        return schoolID;
    };
int Resource::getCareer() const {
        return careerID;
    };
int Resource::getSubject() const {
        return subjectID;
    };
string Resource::getPath() const {
        return path;
    };
vector<unsigned char> Resource::getFileData(){
    return fileData;
}

vector<Resource> Resource::listBySubject(sqlite3* db,int SubjectID){
    vector<Resource> resources;
    string sql="SELECT ResourceID,ResourceName FROM Resources WHERE SubjectID = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        cerr << "Error preparing statement" << sqlite3_errmsg(db)<< endl;
        return resources;
    }
    if (sqlite3_bind_int(stmt, 1, SubjectID) != SQLITE_OK) {
        cerr << "Error binding SchoolID: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return resources;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        resources.emplace_back(id, name);
    }
    sqlite3_finalize(stmt);
    return resources;
};
void Resource::PrintResourcesBySubject(sqlite3* db) {
    if (subjectID == 0) {
        cerr << "Error: El ID del la materia es nulo" << endl;
        return;
    }
    vector<Resource> resources = listBySubject(db, subjectID);
    for (const auto& resource : resources) {
        cout << resource.getID() << ". " << resource.getName() << endl;
    }
};
bool Resource::UploadResource(sqlite3* db) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO resources (ResourceName, SchoolID, CareerID, SubjectID, FileData) VALUES (?, ?, ?, ?,?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparando consulta: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, schoolID);
    sqlite3_bind_int(stmt, 3, careerID);
    sqlite3_bind_int(stmt, 4, subjectID);
    sqlite3_bind_int(stmt, 4, subjectID);

    // Vincular el BLOB (fileData)
    sqlite3_bind_blob(stmt, 5, fileData.data(), fileData.size(), SQLITE_TRANSIENT);

    bool success = true;
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error insertando recurso: " << sqlite3_errmsg(db) << "\n";
        success = false;
    }

    sqlite3_finalize(stmt);
    return success;
};
bool Resource::downloadResource(sqlite3* db, int rID, const string& outputPath){
    sqlite3_stmt* stmt;
    string query="SELECT ResourceName, FileData FROM Resources WHERE ResourceID=?";
    if(sqlite3_prepare_v2(db, query.c_str(),-1,&stmt, nullptr)!=SQLITE_OK){
        std::cerr<<"No se hizo bien la fking consulta";
        return false;
    };
    sqlite3_bind_int(stmt,1,rID);
    int rc=sqlite3_step(stmt);
    if(rc==SQLITE_ROW){
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const void* blob = sqlite3_column_blob(stmt, 1);
        int blobSize = sqlite3_column_bytes(stmt, 1);

        std::string fullPath = outputPath + "/" + name;

        std::ofstream outFile(fullPath, std::ios::binary);
        if (!outFile) {
            std::cerr << "No se pudo crear el archivo en " << fullPath << "\n";
            sqlite3_finalize(stmt);
            return false;
        }
        outFile.write(reinterpret_cast<const char*>(blob), blobSize);
        outFile.close();

        std::cout << "Recurso guardado exitosamente en: " << fullPath << "\n";
        sqlite3_finalize(stmt);
        return true;
    } else {
        std::cout << "No se encontró el recurso con ID: " << rID<< "\n";
        sqlite3_finalize(stmt);
        return false;
    };
};
    