#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>

class User{
    private:
    std::string userName,password,email;
    public:
    User(std::string name, std::string pwd,std::string e_mail);
    User();
    std::string getName(){    
        return userName;
    };
    std::string getPassword(){
        return password;
    } 
    void saveInFile(std::string& name);
};
bool isLogedIn();
bool SignUp();