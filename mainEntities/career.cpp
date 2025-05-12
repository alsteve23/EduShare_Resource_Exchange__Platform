
#include<iostream>
#include "school.h"
#include "career.h"
#include <string>
#include <sqlite3.h>
#include <vector>
using namespace std;

Career::Career(int id, std::string n,School* f)
        : careerID(id), name(n),school(f){};
Career::Career(){
        careerID=0;
        name="";
        school=nullptr;
    };
Career::Career(int id, string name)
        : careerID(id), name(name), school(nullptr){};
int Career::getID()const{    
        return careerID;
    };
std::string Career::getName()const{
        return name;
    };
School* Career::getSchool()const{
        return school;
    };
vector<Career> Career::listBySchool(sqlite3* db,int SchoolID){
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
void Career::PrintCareersBySchool(sqlite3* db) {
    if (school == nullptr) {
        cerr << "Error: El puntero 'school' es nulo. No se puede listar las carreras." << endl;
        return;
    }
    vector<Career> careers = listBySchool(db, school->getID());
    for (const auto& career : careers) {
        cout << career.getID() << ". " << career.getName() << endl;
    }
}
