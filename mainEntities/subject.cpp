
#include<iostream>
#include "school.h"
#include "career.h"
#include "subject.h"
using namespace std;

Subject::Subject(int id,string n,int cID, int sID)
        : subjectID(id), name(n),careerID(cID),schoolID(sID){};
Subject::Subject(){
        subjectID=0;
        name="";
        careerID=0;
        schoolID=0;
    };
Subject::Subject(int id, string name)
        : subjectID(id), name(name), careerID(0), schoolID(0){};
int Subject::getID() const {    
        return subjectID;
    };
std::string Subject::getName() const {
        return name;
    };
int Subject::getcareerID()const{
    return careerID;
}  
int Subject::getschoolID()const{
    return schoolID;
}  
vector<Subject> Subject::fromCareer(sqlite3* db,int CareerID){
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
vector<Subject> Subject::fromSchool(sqlite3* db,int schoolID){
    vector<Subject> subjects;
    string sql="SELECT SubjectID,SubjectName FROM Subjects WHERE SchoolID = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        cerr << "Error preparing statement" << sqlite3_errmsg(db)<< endl;
        return subjects;
    }
    if (sqlite3_bind_int(stmt, 1, schoolID) != SQLITE_OK) {
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
void Subject::PrintSubjects(vector<Subject>& subjects) {
    if (!subjects.empty()) {
        for (const auto& subject : subjects) {
        cout << subject.getID() << ". " << subject.getName() << endl;
        }   
    }else{
        cout<<"No se encontraron materias relacionadas."<<endl;
    }
    
};
bool Subject::addSubject(sqlite3* db){
    sqlite3_stmt* stmt;
    string query="INSERT INTO Subjects(SubjectName, SchoolID,CareerID) VALUES(?,?,?);";
    if(sqlite3_prepare_v2(db, query.c_str(), -1,&stmt, nullptr)!=SQLITE_OK){
        cerr<<"Error preparando la consulta: "<<sqlite3_errmsg(db)<<"\n";
        return false;
    }
    sqlite3_bind_text(stmt,1, getName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2, getschoolID());
    sqlite3_bind_int(stmt,3, getcareerID());
    if(sqlite3_step(stmt)!=SQLITE_DONE){
        cerr<<"Error insertando el recurso"<<sqlite3_errmsg(db)<<"\n";
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
};
bool Subject::deleteSubject(sqlite3* db){
    sqlite3_stmt* stmt;
    string query= "DELETE FROM Subjects WHERE SubjectID=?;";
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
        cerr<<"No se pudo eliminar la materia"<<sqlite3_errmsg(db)<<"\n";
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
};

