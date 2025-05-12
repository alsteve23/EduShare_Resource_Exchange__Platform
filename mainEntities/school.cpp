
#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include<string>
#include<sqlite3.h>
#include <vector>
#include "school.h"
using namespace std;
School::School(int id, std::string n)
        : schoolID(id), name(n){};
School::School(){
        schoolID=0;
        name="";
    };
int School::getID()const {    
        return schoolID;
    };
string School::getName() const {
        return name;
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
void School::printAll(sqlite3* db){
    std::vector<School> schools = listAll(db);
    std::cout << "Available Schools:\n";
    for (const School& s : schools) {
        std::cout << s.getID() << ". " << s.getName() << "\n";
    }
}
    

    