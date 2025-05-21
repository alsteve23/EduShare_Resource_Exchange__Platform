

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
void terminalClear() {
    std::cout << "\033[2J\033[1;1H"; // Limpia la pantalla y mueve el cursor al inicio
};
void titulo(){
    terminalClear();
    int terminalWidth1 = 75;
    int option;
    string title= "Resource Exchange Platform";
    cout<<setw(terminalWidth1-(title.length()/2))<<title<<endl;
    int terminalWidth2 = 119;
    char fillChar = '_';
    cout<<setfill(fillChar)<<setw(terminalWidth2)<<"_"<<endl;
    cout << std::resetiosflags(std::ios::adjustfield) << std::setfill(' ');
}

