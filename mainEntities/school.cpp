
#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include<string>
#include<sqlite3.h>
#include <vector>
#include<optional>
#include "school.h"
using namespace std;
School::School(int id, std::string n)
        : schoolID(id), name(n){};
School::School(){
        schoolID=0;
        name="";
    };
    
School::School(const string name)
    :schoolID(0),name(name){};
int School::getID()const {    
        return schoolID;
    };
string School::getName() const {
        return name;
    };

optional<School> School::fromID(sqlite3* db, int id){
    sqlite3_stmt* stmt;
    const char* query="SELECT * FROM Schools WHERE SchoolID=?;";
    if(sqlite3_prepare_v2(db,query, -1,&stmt,nullptr)!=SQLITE_OK){
        cerr<<"Error preparando la consulta"<<sqlite3_errmsg(db)<<endl;
        return nullopt;
    }
    if(sqlite3_bind_int(stmt, 1, id) != SQLITE_OK){
    cerr << "Error uniendo el ID: " << sqlite3_errmsg(db) << endl;
    sqlite3_finalize(stmt);
    return std::nullopt;
    }
    std::optional<School> result = std::nullopt;
    if(sqlite3_step(stmt) == SQLITE_ROW){
        int d = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        std::string nameStr = name ? reinterpret_cast<const char*>(name) : "";
        result = School(d, nameStr);
    }
    sqlite3_finalize(stmt);
    return result;
};
    //devuelve un vector de los objectos School, con los datos de la base de datos
vector<School> School::listAll(sqlite3* db){
    vector<School> schools;
    const char* sql="Select SchoolID,SchoolName from Schools;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return schools;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        std::string nameStr = name ? reinterpret_cast<const char*>(name) : "";
        schools.emplace_back(School(id, nameStr));
    }
    sqlite3_finalize(stmt); 
    return schools;
}
//imprime en pantalla las escuelas dispnibles en la base de datos
void School::printAll(vector<School>& schools){
    for (const School& s : schools) {
        std::cout << s.getID() << ". " << s.getName() << "\n";
    }
}
//add and delete methods
bool School::addSchool(sqlite3* db){
    sqlite3_stmt* stmt;
    string query="INSERT INTO Schools(SchoolName) VALUES(?);";
    if(sqlite3_prepare_v2(db, query.c_str(), -1,&stmt, nullptr)!=SQLITE_OK){
        cerr<<"Error preparando la consulta: "<<sqlite3_errmsg(db)<<"\n";
        return false;
    }
    sqlite3_bind_text(stmt,1, getName().c_str(),-1,SQLITE_TRANSIENT);
    if(sqlite3_step(stmt)!=SQLITE_DONE){
        cerr<<"Error insertando el recurso"<<sqlite3_errmsg(db)<<"\n";
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
};
bool School::deleteSchool(sqlite3* db){
    sqlite3_stmt* stmt;
    string query= "DELETE FROM Schools WHERE SchoolID=?;";
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
        cerr<<"No se pudo eliminar la escuela"<<sqlite3_errmsg(db)<<"\n";
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
};
    

    