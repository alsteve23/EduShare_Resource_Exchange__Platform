

#include<iostream>
#include "../mainEntities/Entities.h"
#include <string>
#include <sqlite3.h>
#include<vector>
#include<fstream>
#include<FileSystem>
using namespace std;
/*
here i am going to implement the main functions of the platform
*/
//reads the files
vector<unsigned char> readBinaryFile(const string& filePath){
    ifstream file(filePath, ios::binary | ios::ate);
    if(!file){
        throw runtime_error("No se pudo abrir: " + filePath);
    }
    streamsize fileSize=file.tellg();
    if(fileSize<=0){
        cout<<"archivo vacio"<<endl;
    };
    file.seekg(0,ios::beg);
    vector<unsigned char > buffer(fileSize);
    if (!file.read(reinterpret_cast<char*>(buffer.data()),fileSize)){
        throw runtime_error("No se pudo leer:"+filePath);       
    }
    return buffer;
};

int main() {
    //opnening database
    const char* path = "../Database/database.db";
    sqlite3* db;
    if (sqlite3_open(path, &db) != SQLITE_OK) {
    cout << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << endl;
    return 1;
    }
    //subir un recurso
    // string name= "Computer_Report STFQ.pdf";
    // string filePath= "C:\\Users\\Usuario\\OneDrive\\Documentos\\Cursos_Steve_Tene\\5. Quinto_semestre\\arqui. de computadores\\Computer_Report STFQ.pdf";
    // vector<unsigned char> file= readBinaryFile(filePath);
    // Resource resource(name,5, 8,1, file);
    // bool flag=resource.UploadResource(db);
    // cout<<flag<<endl;
    
    
    //mostrar archivos filtrados
    
    vector<Resource> resources=Resource::fromSchool(db,1);
    Resource::PrintResources(resources);
   
   
   
    //descargar el archivo

    // string destinyPath= "C:\\Users\\Usuario\\OneDrive\\Escritorio\\xd";
    // auto resource1= Resource::fromID(db,1);
    // if(resource1.has_value()){
    //     Resource resource2= resource1.value();
    //     resource2.downloadResource(db,destinyPath);
    //     cout<<"recurso encontrado"<<endl;
    // }else{
    //     cout<<"recurso no encontrado"<<endl;
    // };
    
    sqlite3_close(db);
    return 0;
}