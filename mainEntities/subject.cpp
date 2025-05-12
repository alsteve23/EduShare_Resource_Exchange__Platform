
#include<iostream>
#include "school.h"
#include "career.h"
#include "subject.h"

Subject::Subject(int id, std::string n,School* f, Career* c)
        : subjectID(id), name(n),school(f),career(c){};
Subject::Subject(){
        subjectID=0;
        name="";
        school=nullptr;
        career=nullptr;
    };
Subject::Subject(int id, string name)
        : subjectID(id), name(name), school(nullptr), career(nullptr){};
int Subject::getID() const {    
        return subjectID;
    };
std::string Subject::getName() const {
        return name;
    };
School* Subject::getSchool() const {
        return school;
    };
Career* Subject::getCareer() const {
        return career;
    };
vector<Subject> Subject::listByCareer(sqlite3* db,int CareerID){
    vector<Subject> subjects;
    string sql="SELECT SubjectID,SubjectName FROM Subjects WHERE CareerID = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        cerr << "Error preparing statement" << sqlite3_errmsg(db)<< endl;
        return subjects;
    }
    if (sqlite3_bind_int(stmt, 1, CareerID) != SQLITE_OK) {
        cerr << "Error binding SchoolID: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return subjects;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        subjects.emplace_back(id, name);
    }
    sqlite3_finalize(stmt);
    return subjects;
};
void Subject::PrintSubjectsByCareer(sqlite3* db) {
    if (career == nullptr) {
        cerr << "Error: El puntero 'career' es nulo. No se puede listar las materias." << endl;
        return;
    }
    vector<Subject> subjects = listByCareer(db, career->getID());
    for (const auto& subject : subjects) {
        cout << subject.getID() << ". " << subject.getName() << endl;
    }
}

