
#include<iostream>
#include "school.h"
#include "career.h"
#include <string>
#include <sqlite3.h>
#include <vector>
using namespace std;

Career::Career(int id, std::string n,int f)
        : careerID(id), name(n),schoolID(f){};
Career::Career(){
        careerID=0;
        name="";
        schoolID=0;
    };
Career::Career(int id, string name)
        : careerID(id), name(name), schoolID(0){};
Career::Career(string name,int schoolID)
        : careerID(0), name(name),schoolID(schoolID){};
Career::Career(int id)
        : careerID(id), name(""),schoolID(0){};
int Career::getID()const{    
        return careerID;
    };

std::string Career::getName()const{
        return name;
    };
int Career::getSchoolID()const{
        return schoolID;
    };
vector<Career> Career::fromSchool(sqlite3* db,int SchoolID){
        vector<Career> careers;
        string sql="SELECT CareerID,CareerName FROM Careers WHERE SchoolID = ?;";
        sqlite3_stmt* stmt;
        if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
            cerr << "Error preparing statement" << sqlite3_errmsg(db)<< endl;
            return careers;
        }
        if (sqlite3_bind_int(stmt, 1, SchoolID) != SQLITE_OK) {
            cerr << "Error binding SchoolID: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            return careers;
        }
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            careers.emplace_back(id, name);
        }
        sqlite3_finalize(stmt);
        return careers;
};

void Career::PrintCareers(vector<Career>& careers) {
    if(!careers.empty()){
        for(const auto&career: careers){
            cout<<career.getID()<<". "<<career.getName()<<endl;
        }
    }else{
        cout<<"No se encontraron carreras relacionadas a la escuela. "<<endl;
    }
};
bool Career::addCareer(sqlite3* db){
    sqlite3_stmt* stmt;
    string query="INSERT INTO Careers(CareerName, SchoolID) VALUES(?,?);";
    if(sqlite3_prepare_v2(db, query.c_str(), -1,&stmt, nullptr)!=SQLITE_OK){
        cerr<<"Error preparando la consulta: "<<sqlite3_errmsg(db)<<"\n";
        return false;
    }
    sqlite3_bind_text(stmt,1, getName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2, getSchoolID());
    if(sqlite3_step(stmt)!=SQLITE_DONE){
        cerr<<"Error insertando el recurso"<<sqlite3_errmsg(db)<<"\n";
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
};
bool Career::deleteCareer(sqlite3* db){
    sqlite3_stmt* stmt;
    string query= "DELETE FROM Careers WHERE CareerID=?;";
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
        cerr<<"No se pudo eliminar la carrera"<<sqlite3_errmsg(db)<<"\n";
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
};
