

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
//List all the Schoolss in the Database
vector<unsigned char> readBinaryFile(const string& filePath){
    ifstream file(filePath, ios::binary | ios::ate);
    if(!file){
        cout<<"no leyendo"<<endl;
        throw runtime_error("No se pudo abrir: " + filePath);
    }
    cout<<"leyendo"<<endl;
    streamsize fileSize=file.tellg();
    if(fileSize<=0){
        cout<<"archivo vacio"<<endl;
    };
    cout<<"tamano del archivo"<<fileSize<<endl;
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
        std::cerr << "Database connection failed\n";
        return 1;
    }
    // testing the reading functions
    //School::listAll(db);
    //School SchoolInstance;
    //SchoolInstance.printAll(db);

    //proving the uploadresource function
    //string filePath="C:\\Users\\Usuario\\OneDrive\\Documentos\\Cursos_Steve_Tene\\5. Quinto_semestre\\arqui. de computadores\\ALU_Report_STFQ.pdf";
    //string fileName="ALU_Report_STFQ.pdf";
    //vector<unsigned char> fileData=readBinaryFile(filePath);
    //Resource resource(1,fileName,1,1,1,filePath,fileData);
    //vector<unsigned char> comprobador= resource.getFileData();
    //for(size_t i=0;i<comprobador.size();++i){
    //    cout<<comprobador[i]<<endl;
    //}
    //
    //if(resource.UploadResource(db)){
    //    cout<<"Se subió correctamente"<<endl;
    //}
    
    //Proband la función para descargar
    string outputPath="C:\\Users\\Usuario\\OneDrive\\Escritorio\\xd";
    Resource resource(7);
    resource.downloadResource(db, resource.getID(), outputPath);
    return 0;
}