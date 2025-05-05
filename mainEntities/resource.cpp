#pragma once
#include<iostream>
#include "school.h"
#include "career.h"
#include "subject.h"
#include "resource.h"

Resource::Resource(int id, std::string n,School* f, Career* c, Subject* s)
        : resourceID(id), name(n),school(f),career(c),subject(s){};
Resource::Resource(){
        resourceID=0;
        name="";
        school=nullptr;
        career=nullptr;
        subject=nullptr;
        Type="";
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