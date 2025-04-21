#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>
#include "school.h"
#include "career.h"
#include "subject.h"
#include "resource.h"

Resource::Resource(int id, std::string n)
        : resourceID(id), name(n){};
Resource::Resource(){
        resourceID=0;
        name="";
    };
int Resource::getID() const {    
        return resourceID;
    };
std::string Resource::getName() const {
        return name;
    };
std::string Resource::getType() const {
        return Type;
    };