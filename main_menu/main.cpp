
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include "../mainEntities/Entities.h"
using namespace std;

void showMainMenu(){
    int terminalWidth = 75;
    int option;
    string title= "Resource Exchange Platform";
    cout<<setw(terminalWidth-(title.length()/2))<<title<<endl;
    cout<<"Seleccione presionando el ID respectivo."<<endl;
    cout<<setw(20)<<"1. Ver Escuelas Existentes"<<endl;
    cout<<setw(20)<<"2. Adicionar Escuelas"<<endl;
    cout<<setw(20)<<"2. Eliminar Escuelas"<<endl;
    
    
};
void secondaryMenu(){
    int terminalWidth = 75;
    int option;
    string title= "Resource Exchange Platform";
    cout<<setw(terminalWidth-(title.length()/2))<<title<<endl;
    cout<<setw(20)<<"1. Ver Carreras Existentes"<<endl;
    cout<<setw(20)<<"2. Adicionar Carreras"<<endl;
    cout<<setw(20)<<"2. Eliminar Carreras"<<endl;    
}
void thirdMenu(){
    int terminalWidth = 75;
    int option;
    string title= "Resource Exchange Platform";
    cout<<setw(terminalWidth-(title.length()/2))<<title<<endl;
    cout<<setw(20)<<"1. Ver Carreras Existentes"<<endl;
    cout<<setw(20)<<"2. Adicionar Carreras"<<endl;
    cout<<setw(20)<<"2. Eliminar Carreras"<<endl;    
}

void fourthMenu(){
    int terminalWidth = 75;
    int option;
    string title= "Resource Exchange Platform";
    cout<<setw(terminalWidth-(title.length()/2))<<title<<endl;
    cout<<setw(20)<<"1. Ver Materias Existentes"<<endl;
    cout<<setw(20)<<"2. Adicionar Materias"<<endl;
    cout<<setw(20)<<"2. Eliminar Materias"<<endl;    
}
void fifththMenu(){
    int terminalWidth = 75;
    int option;
    string title= "Resource Exchange Platform";
    cout<<setw(terminalWidth-(title.length()/2))<<title<<endl;
    cout<<setw(20)<<"1. Ver Recursos Existentes"<<endl;
    cout<<setw(20)<<"2. Adicionar Recursos"<<endl;
    cout<<setw(20)<<"2. Eliminar Recursos"<<endl;    
}
int main(){
    const char* path = "../Database/database.db";
    sqlite3* db;
    if (sqlite3_open(path, &db) != SQLITE_OK) {
    cout << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << endl;
    return 1;
    }
    int option;
    showMainMenu();
    cout<<"tu eleccion es: ";
    cin>>option;
    cin.ignore();
    switch (option)
    {
    case 1:
        {
            
            vector<School> schools=School::listAll(db);
            School::printAll(schools);
            
        }
        {   
            
            int id1;
            cout<<"Escribe el ID de la escuela que quieres acceder: ";
            cin>>id1;
            cin.ignore();
            secondaryMenu();
            int option2;
            cin>>option2;
            cin.ignore();
            switch (option2)
            {
            case 1:
                {   
                    vector<Career> careers= Career::fromSchool(db, id1);
                    Career::PrintCareers(careers);
                }
                break;
            case 2:
                {
                    string name;
                    cout<<"Ingresa el nombre de la  nueva materia: ";
                    getline(cin, name);
                    cin.ignore();
                    Career career(name,id1);
                    career.addCareer(db);
                }
            case 3:
                {
                    vector<Career> careers=Career::fromSchool(db,id1);
                    Career::PrintCareers(careers);
                    int careerID;
                    cout<<"Escribe el ID de la carrera que deseas eliminar";
                    cin>>careerID;
                    cin.ignore();
                    Career career(careerID);
                    career.deleteCareer(db);
                }
            
            default:
                break;
            }
        }
        break;
    case 2:
        {
            string name;
            cout<<"Ingrese el nombre de la nueva escuela:";
            getline(cin,name);
            School school(name);
            school.addSchool(db);
        }
        break;
    case 3:
        {
            int id;
            vector<School> schools= School::listAll(db);
            School::printAll(schools);
            cout<<"Escriba el ID de la Escuela que desea eliminar: ";
            cin>>id;
            auto school=School::fromID(db, id);
            School ss;
            if(school.has_value()){
                ss=school.value();
                ss.deleteSchool(db);
            }
        }
        break;
    default:
        break;
    }
    sqlite3_close(db);
    return 0;
};
