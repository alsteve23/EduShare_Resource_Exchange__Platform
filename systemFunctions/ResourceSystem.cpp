

#include<iostream>
#include "../mainEntities/Entities.h"
#include <string>
#include <sqlite3.h>
using namespace std;
/*
here i am going to implement the main functions of the platform
*/
//List all the Schoolss in the Database
void listSchools(sqlite3* db,const char* path) {
    sqlite3_stmt* stmt;
    string sql="SELECT SchoolID,SchoolName FROM Schools;";
    try
    {
        int exit = sqlite3_open(path, &db);
        if (exit != SQLITE_OK) {
            cerr << "Error opening database" << sqlite3_errmsg(db)<< endl;
            return;
        }

        // Prepare the query
        exit = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            cerr << "Error preparing statement" << sqlite3_errmsg(db)<< endl;
            sqlite3_close(db);
            return;
        }

        // Execute the query
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Accede a la primera columna (SchoolID)
            const unsigned char* schoolID = sqlite3_column_text(stmt, 0);
            // Accede a la segunda columna (SchoolName)
            const unsigned char* schoolName = sqlite3_column_text(stmt, 1);
        
            // print both columns
            cout
                 << (schoolID ? reinterpret_cast<const char*>(schoolID) : "NULL") << ". " 
                 << (schoolName ? reinterpret_cast<const char*>(schoolName) : "NULL") << endl;
        }

        // Finalize the statement
        sqlite3_finalize(stmt);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
};

//List the careers based on the SchoolID
void listCareersBasedOnSchool(sqlite3* db, const char* path, string schoolID) {
    sqlite3_stmt* stmt;
    string sql="SELECT CareerID,CareerName FROM Careers WHERE SchoolID = ?;";
    try
    {
        int exit = sqlite3_open(path, &db);
        if (exit != SQLITE_OK) {
            cerr << "Error opening database" << sqlite3_errmsg(db)<< endl;
            return;
        }

        // Prepare the query
        exit = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            cerr << "Error preparing statement" << sqlite3_errmsg(db)<< endl;
            sqlite3_close(db);
            return;
        }

        // link parameters
        sqlite3_bind_text(stmt, 1, schoolID.c_str(), -1, SQLITE_STATIC);

        // Execute the query
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* CareerID = sqlite3_column_text(stmt, 0);
            // Accede a la segunda columna (SchoolName)
            const unsigned char* CareerName = sqlite3_column_text(stmt, 1);
        
            // Print both columns
            cout
                 << (CareerID ? reinterpret_cast<const char*>(CareerID) : "NULL") << ". " 
                 << (CareerName ? reinterpret_cast<const char*>(CareerName) : "NULL") << endl;
        }

        // finalize the stateent
        sqlite3_finalize(stmt);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
};
//List the subjects based on the CareerID
void listSubjectsBasedOnCareer(sqlite3* db,const char* path, string CareerID) {
    sqlite3_stmt* stmt;
    string sql="SELECT SubjectID,SubjectName FROM Subjects WHERE CareerID = ?;";
    try
    {
        int exit = sqlite3_open(path, &db);
        if (exit != SQLITE_OK) {
            cerr << "Error opening database" << sqlite3_errmsg(db)<< endl;
            return;
        }

        
        exit = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            cerr << "Error preparing statement" << sqlite3_errmsg(db)<< endl;
            sqlite3_close(db);
            return;
        }

        
        sqlite3_bind_text(stmt, 1, CareerID.c_str(), -1, SQLITE_STATIC);

        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* SubjectID = sqlite3_column_text(stmt, 0);           
            const unsigned char* SubjectName = sqlite3_column_text(stmt, 1);
        
            cout
                 << (SubjectID ? reinterpret_cast<const char*>(SubjectID) : "NULL") << ". " 
                 << (SubjectName ? reinterpret_cast<const char*>(SubjectName) : "NULL") << endl;
        }

        sqlite3_finalize(stmt);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
};

void listResourcesBasedOnSubject(sqlite3* db,const char* path, string SubjectID) {
    sqlite3_stmt* stmt;
    string sql="SELECT ResourceID,ResourceName FROM Resources WHERE SubjectID = ?;";
    try
    {
        int exit = sqlite3_open(path, &db);
        if (exit != SQLITE_OK) {
            cerr << "Error opening database" << sqlite3_errmsg(db)<< endl;
            return;
        }
       
        exit = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (exit != SQLITE_OK) {
            cerr << "Error preparing statement" << sqlite3_errmsg(db)<< endl;
            sqlite3_close(db);
            return;
        }
        
        sqlite3_bind_text(stmt, 1, SubjectID.c_str(), -1, SQLITE_STATIC);
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* ResourceID = sqlite3_column_text(stmt, 0);           
            const unsigned char* ResourceName = sqlite3_column_text(stmt, 1);
        
            cout
                 << (ResourceID ? reinterpret_cast<const char*>(ResourceID) : "NULL") << ". " 
                 << (ResourceName ? reinterpret_cast<const char*>(ResourceName) : "NULL") << endl;
        }
        
        sqlite3_finalize(stmt);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
};
void uploadResource(){
    
};
void downloadResource(){
    
};

int main() {
    //opnening database
    const char* path = "../Database/database.db";
    sqlite3* db;
    if (sqlite3_open("database.db", &db) != SQLITE_OK) {
        std::cerr << "Database connection failed\n";
        return 1;
    }
    // testing the reading functions
    listSchools(db,path);
    listCareersBasedOnSchool(db,path,"3");
    listSubjectsBasedOnCareer(db,path,"1");
    listResourcesBasedOnSubject(db,path,"1");
    sqlite3_close(db);
    return 0;
}