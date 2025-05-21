
#include<iostream>
#include "school.h"
#include "career.h"
#include "subject.h"
#include "resource.h"
#include <string>
#include <sqlite3.h>
#include <vector>
#include <optional>
using namespace std;

//constructores
Resource::Resource(int id, string n,int f, int c, int s, vector<unsigned char> fileData)
        : resourceID(id), name(n),schoolID(f),careerID(c),subjectID(s),fileData(fileData){};
Resource::Resource(string n,int f, int c, int s, vector<unsigned char> fileData)
        : resourceID(0), name(n),schoolID(f),careerID(c),subjectID(s),fileData(fileData){};
Resource::Resource(){
        resourceID=0;
        name="";
        schoolID=0;
        careerID=0;
        subjectID=0;
        fileData.clear();
    };
Resource::Resource(int id, string name)
        : resourceID(id), name(name), schoolID(0), careerID(0), subjectID(0){};
Resource::Resource(int id)
        : resourceID(id),name(""),schoolID(0),careerID(0),subjectID(0){};
//getters
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
vector<unsigned char> Resource::getFileData(){
    return fileData;
}
//metodos estáticos para filtrar en base a distintos parametros
optional<Resource> Resource::fromID(sqlite3* db, const int& ID){ //filtra por ID
    sqlite3_stmt* stmt;
    string query= "SELECT * FROM Resources WHERE ResourceID=?";
    if(sqlite3_prepare_v2(db, query.c_str(),-1, &stmt, nullptr)!=SQLITE_OK){
        cerr<<"Error generando la consulta"<<sqlite3_errmsg(db)<<endl;
    }
    if(sqlite3_bind_int(stmt,1, ID)!=SQLITE_OK){
        cerr<<"Error uniendo el ID"<<sqlite3_errmsg(db)<<endl;
    }
    optional<Resource> resource= nullopt;
        if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int schoolID = sqlite3_column_int(stmt, 2);
        int careerID = sqlite3_column_int(stmt, 3);
        int subjectID = sqlite3_column_int(stmt, 4);
        const void* blob = sqlite3_column_blob(stmt, 5);
        int blobSize = sqlite3_column_bytes(stmt, 5);
        vector<unsigned char> fileData;
        if (blob && blobSize > 0) {
            fileData.assign(static_cast<const unsigned char*>(blob), static_cast<const unsigned char*>(blob) + blobSize);
        }
        resource = Resource(id, name, schoolID, careerID, subjectID, fileData);
    }
    sqlite3_finalize(stmt);
    return resource;
};

optional<Resource> fromName(sqlite3* db,const string& name){ //filtra por nombre
    sqlite3_stmt* stmt;
    string query= "SELECT * FROM Resources WHERE ResourceName=?";
    if(sqlite3_prepare_v2(db, query.c_str(),-1, &stmt, nullptr)!=SQLITE_OK){
        cerr<<"Error generando la consulta"<<sqlite3_errmsg(db)<<endl;
        return nullopt;
    }
    if(sqlite3_bind_text(stmt,1, name.c_str(),-1, SQLITE_TRANSIENT)!=SQLITE_OK){
        cerr<<"Error uniendo el Nombre"<<sqlite3_errmsg(db)<<endl;
        sqlite3_finalize(stmt);
        return nullopt;
    }
    optional<Resource> resource= nullopt;
        if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int schoolID = sqlite3_column_int(stmt, 2);
        int careerID = sqlite3_column_int(stmt, 3);
        int subjectID = sqlite3_column_int(stmt, 4);
        const void* blob = sqlite3_column_blob(stmt, 5);
        int blobSize = sqlite3_column_bytes(stmt, 5);
        vector<unsigned char> fileData;
        if (blob && blobSize > 0) {
            fileData.assign(static_cast<const unsigned char*>(blob), static_cast<const unsigned char*>(blob) + blobSize);
        }
        resource = Resource(id, name, schoolID, careerID, subjectID, fileData);
    }
    sqlite3_finalize(stmt);
    return resource;
};

//metodos que filtran los recursos en base a ID externos
vector<Resource> Resource::fromCareer(sqlite3* db, const int& careerID){        //filtra por carreras
    vector<Resource> resources;
    sqlite3_stmt* stmt;
    string query= "SELECT ResourceID, ResourceName FROM Resources WHERE CareerID=?";
    if(sqlite3_prepare_v2(db, query.c_str(),-1, &stmt, nullptr)!=SQLITE_OK){
        cerr<<"Error generando la consulta"<<sqlite3_errmsg(db)<<endl;
    };
    if(sqlite3_bind_int(stmt,1, careerID)!=SQLITE_OK){
        cerr<<"Error uniendo el ID"<<sqlite3_errmsg(db)<<endl;
    };
    while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    resources.emplace_back(id, name);
    };
    return resources;
}
vector<Resource> Resource::fromSubject(sqlite3* db,int SubjectID){          //filtra por materias
    vector<Resource> resources;
    string sql="SELECT ResourceID,ResourceName FROM Resources WHERE SubjectID = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        cerr << "Error generando la consulta" << sqlite3_errmsg(db)<< endl;
        return resources;
    }
    if (sqlite3_bind_int(stmt, 1, SubjectID) != SQLITE_OK) {
        cerr << "Error uniendo el ID: " << sqlite3_errmsg(db) << endl;
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
vector<Resource> Resource::fromSchool(sqlite3* db,int schoolID){            //filtra por Escuelas
    vector<Resource> resources;
    string sql="SELECT ResourceID,ResourceName FROM Resources WHERE SchoolID = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        cerr << "Error generando la consulta" << sqlite3_errmsg(db)<< endl;
        return resources;
    }
    if (sqlite3_bind_int(stmt, 1, schoolID) != SQLITE_OK) {
        cerr << "Error uniendo el ID: " << sqlite3_errmsg(db) << endl;
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

void Resource::PrintResources(vector<Resource>& resources) {                //imprime los recursos filtrados previamente
    if(!resources.empty()){
        for (const auto& resource : resources) {
        cout << resource.getID() << ". " << resource.getName() << endl;
        }
    }else{
        cout<<"No se encontraron recursos relacionados."<<endl;
    }
};
bool Resource::UploadResource(sqlite3* db) {                                //sube recursos a la base de datos
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
bool Resource::downloadResource(sqlite3* db, const string& outputPath){     //decarga recursos de la base de datos
    sqlite3_stmt* stmt;
    string query="SELECT ResourceName, FileData FROM Resources WHERE ResourceID=?";
    if(sqlite3_prepare_v2(db, query.c_str(),-1,&stmt, nullptr)!=SQLITE_OK){
        std::cerr<<"No se ejecuto consulta"<<sqlite3_errmsg(db)<<endl;
        return false;
    };
    sqlite3_bind_int(stmt,1,getID());
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
        std::cout << "No se encontró el recurso con ID: " << getID()<< "\n";
        sqlite3_finalize(stmt);
        return false;
    };
};

bool Resource::deleteResource(sqlite3* db){
    sqlite3_stmt* stmt;
    string query= "DELETE FROM Resources WHERE ResourceID=?;";
    if(sqlite3_prepare_v2(db,query.c_str(),-1,&stmt, nullptr)!=SQLITE_OK){
        cerr<<"No se ejecuto la consulta"<<sqlite3_errmsg(db)<<"\n";
        return false;
    }
    if(sqlite3_bind_int(stmt,1,getID())){
        cerr<<"No se pudo enlazar el ID: "<<sqlite3_errmsg(db)<<"\n";
        sqlite3_finalize(stmt);
        return false;
    }
    if(sqlite3_step(stmt)!=SQLITE_DONE){
        cerr<<"No se pudo eliminar el recurso"<<sqlite3_errmsg(db)<<"\n";
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
};
    