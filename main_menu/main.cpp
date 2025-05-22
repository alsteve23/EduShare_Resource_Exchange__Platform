
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<chrono>
#include<thread>

#include "../mainEntities/Entities.h"
#include "../systemFunctions/ResourceSystem.h"
using namespace std;

void fourthMenu(sqlite3* db, int schoolID, int careerID, int subjectID){
    while(true){
    int option;
    titulo();
    cout<<"1. Descargar un Recurso Existentes"<<endl;
    cout<<"2. Adicionar Recursos"<<endl;
    cout<<"3. Eliminar Recursos"<<endl;    
    cout<<"4. Volver"<<endl;
    cout<<"Ingrese el numero respectivo: ";
    cin>>option;cin.ignore();
    switch (option)
    {
    case 1:
    {
        titulo();
        int id3;
        vector<Resource> resources= Resource::fromSubject(db, subjectID);
        Resource::PrintResources(resources);
        cout<<"Ingrese el ID del recurso a descargar o [-1] para regresar: ";
        cin>>id3; cin.ignore();
        if (id3==-1){
            terminalClear();
            cout<<"Volviendo..."<<endl;
            this_thread::sleep_for(chrono::seconds(1));
            break;
        }else{
            string filepath;
            cout<<"Ingrese el path donde quiere que se guarde el recurso: ";
            getline(cin, filepath);
            Resource resource(id3);
            resource.downloadResource(db,filepath);
            this_thread::sleep_for(chrono::seconds(3));

        }
    }
    break;
    case 2:
    {
        titulo();
        string name, filepath;
        cout<<"Ingrese el nombre del recurso a adicionar (incluya el la extension, ejemplo: .pdf ) "<< endl;
        cout<<"o ingresa [-1] para regresaar";
        getline(cin, name);
        if(name=="-1"){
            terminalClear();
            cout<<"Volviendo..."<<endl;
            this_thread::sleep_for(chrono::seconds(1));
            break;
        }
        cout<<"Ingrese el path hacia el archivo ";
        getline(cin,filepath);
        Resource resource(name, schoolID, careerID, subjectID,readBinaryFile(filepath));
        if(resource.UploadResource(db)){
            cout<<"Recurso añadido con exito"<<endl;
        }else{
            cout<<"No se pudo adicionar el recurso"<<endl;
        }
    }
    break;
    case 3:
    {
        titulo();
        int id2;
        vector<Resource> resources= Resource::fromSubject(db, subjectID);
        Resource::PrintResources(resources);
        cout<<"Ingrese el ID del recurso a eliminar o ingresa [-1] para regresar";
        cin>>id2;cin.ignore();
        if(id2==-1){
            terminalClear();
            cout<<"Volviendo"<<endl;
            this_thread::sleep_for(chrono::seconds(1));
            break;
        }
        Resource resource(id2);
        resource.deleteResource(db);
        this_thread::sleep_for(chrono::seconds(2));
    }
    break;
    case 4: 
        return;  
    default:
        terminalClear();
        cout<<"Opcion incorrecta"<<endl;
        this_thread::sleep_for(chrono::seconds(1));
        cin.clear(); // Limpia el estado de error de cin
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
}}
void thirdMenu(sqlite3*db, int careerID,int schoolID){
    while(true){
    titulo();
    int option;
    cout<<"1. Ver materias Existentes"<<endl;
    cout<<"2. Adicionar materias"<<endl;
    cout<<"3. Eliminar materias"<<endl;
    cout<<"4. Volver"<<endl;
    cout<<"Seleccione el numero respecto: ";
    cin>>option;cin.ignore();
    switch (option)
    {
    case 1:
        {   
            titulo();
            void terminalClear();
            int subjectID;
            vector<Subject> subjects= Subject::fromCareer(db, careerID);
            Subject::PrintSubjects(subjects);
            cout<<"Escoja una materia o ingresa [-1] para regresar: ";
            cin>>subjectID;cin.ignore();
            if(subjectID==-1){
                terminalClear();
                cout<<"Volviendo..."<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                break;
            }
            fourthMenu(db,schoolID,careerID,subjectID);
        }
    break;   
    case 2:
        {
            titulo();
            string name;
            cout<<"Ingrese el nombre de la nueva materia o ingresa [-1] para regresar:  ";
            if(name=="-1"){
                terminalClear();
                cout<<"Volviendo..."<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                break;
            }
            getline(cin,name);
            Subject subject(name, careerID, schoolID);
            subject.addSubject(db);
            this_thread::sleep_for(chrono::seconds(2));
        }
    break;
    case 3:
        {
            titulo();
            int subjectID;
            vector<Subject> subjects= Subject::fromCareer(db, careerID);
            Subject::PrintSubjects(subjects);
            cout<<"Ingrese el ID de la materia que desea eliminar o ingresa [-1] para regresar :";
            if(subjectID==-1){
                terminalClear();
                cout<<"Volviendo.."<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                break;
            }
            cin>>subjectID;cin.ignore();
            Subject subject(subjectID);
            subject.deleteSubject(db);
            this_thread::sleep_for(chrono::seconds(2));

        }
    break;
    case 4:
        return;
    default:
        terminalClear();
        cout<<"Opcion incorrecta"<<endl;
        this_thread::sleep_for(chrono::seconds(1));
        cin.clear(); // Limpia el estado de error de cin
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
}  
}  

void secondaryMenu(sqlite3* db, int schoolID){
    while(true){
    int option;
    titulo();
    cout<<"1. Ver Carreras Existentes"<<endl;
    cout<<"2. Adicionar Carreras"<<endl;
    cout<<"3. Eliminar Carreras"<<endl;
    cout<<"4. Volver"<<endl;
    cout<<"Ingrese el numero respectivo: ";
    cin>>option; cin.ignore();
    
    switch (option)
    {
    case 1:
        {   
            titulo();
            int careerID;
            vector<Career> careers= Career::fromSchool(db, schoolID);
            Career::PrintCareers(careers);
            cout<<"Escoja una carrera o ingresa [-1] para regresar: "<<endl;
            cin>>careerID;cin.ignore();
            if(careerID==-1){
                terminalClear();
                cout<<"Volviendo"<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                return;
            }
            thirdMenu(db,careerID,schoolID);
        }
    break;
    case 2:
        {
            titulo();
            string name;
            cout<<"Ingresa el nombre de la  nueva carrera o ingresa [-1] para regresar: ";
            getline(cin, name);
            if (name=="-1"){
                terminalClear();
                cout<<"Volviendo..."<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                break;
            }
            Career career(name,schoolID);
            career.addCareer(db);
            this_thread::sleep_for(chrono::seconds(2));
        }
    break;
    case 3:
        {   
            titulo();
            vector<Career> careers=Career::fromSchool(db,schoolID);
            Career::PrintCareers(careers);
            int careerID;
            cout<<"Escribe el ID de la carrera que deseas eliminar o ingresa [-1] para regresar";
            cin>>careerID;
            cin.ignore();
            if(careerID==-1){
                terminalClear();
                cout<<"Volviendo..."<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                break;
            }
            Career career(careerID);
            career.deleteCareer(db);
            this_thread::sleep_for(chrono::seconds(2));
        }
    break;
    case 4:
        return;
    default:
        terminalClear();
        cout<<"Opcion incorrecta"<<endl;
        this_thread::sleep_for(chrono::seconds(1));
        cin.clear(); // Limpia el estado de error de cin
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
}}

void showMainMenu(sqlite3* db){
    while(true){
    int option;
    titulo();
    cout<<"Seleccione presionando el ID respectivo."<<endl;
    cout<<"1. Ver Escuelas Existentes"<<endl;
    cout<<"2. Adicionar Escuelas"<<endl;
    cout<<"3. Eliminar Escuelas"<<endl;
    cout<<"4. Cerrar el programa"<<endl;
    cout<<"Ingrese el numero respectivo: "; 
    cin>>option;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        
        switch (option)
        {
        case 1:
            {
                titulo();
                int schoolID;
                vector<School> schools= School::listAll(db);
                School::printAll(schools);
                cout<<"Escoja una escuela o ingresa [-1] para regresar: ";          
                cin>>schoolID;cin.ignore();
                if(schoolID==-1){
                    terminalClear();
                    cout<<"Volviendo..."<<endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    break;
                }
                secondaryMenu(db, schoolID);
            }
        break;    
        case 2:
            {
                string name;
                titulo();
                cout<<"Ingresa el nombre de la  nueva Escuela o ingresa[-1] para volver: ";
                getline(cin, name);
                if(name=="-1"){
                    terminalClear();
                    cout<<"Volviendo..."<<endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    break;
                }
                School school(name);
                if(school.addSchool(db)){
                    cout<<"Escuela adicionada con exito"<<endl;
                    this_thread::sleep_for(chrono::seconds(2));
                }
                
            }
        break;
        case 3: 
        {
            int id1;
            titulo();
            vector<School> schools= School::listAll(db);
            School::printAll(schools);
            cout<<"Escriba el ID de la Escuela que desea eliminar o ingresa [-1] para volver: ";
            cin>>id1;
            if(id1==-1){
                terminalClear();
                cout<<"Volviendo..."<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                break;
            }
            auto school=School::fromID(db, id1);
            School ss;
            if(school.has_value()){
                ss=school.value();
            
                if(ss.deleteSchool(db)){
                    cout<<"Escuela borrada correctamente"<<endl;
                    this_thread::sleep_for(chrono::seconds(2));
                }else{
                    cout<<"No se pudo borrar la escuela correctamente";
                }
            }else{
                cout<<"No se encontro la escuela con ese ID"<<endl;
            }
            break;
        }
        break;
        case 4: 
            return;
        default:
            terminalClear();
            cout<<"Opcion incorrecta"<<endl;
            this_thread::sleep_for(chrono::seconds(1));
            cin.clear(); // Limpia el estado de error de cin
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
            
        }
    }
    
}
  


int main(){
    const char* path = "../Database/database.db";
    sqlite3* db;
    if (sqlite3_open(path, &db) != SQLITE_OK) {
    cout << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << endl;
    return 1;
    }
    showMainMenu(db);
    sqlite3_close(db);
    return 0;
};
