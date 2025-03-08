#include<iostream>
#include<sstream>
#include<fstream>
#include<filesystem>

class User{
    private:
    std::string userName,password,email;
    public:
    User(std::string name, std::string pwd,std::string e_mail)
        : userName(name), password(pwd), email(e_mail){};
    std::string getName(){    
        return userName;
    };
    std::string getPassword(){
        return password;
    } 
    void saveInFile(std::string& name){
        std::string filePath="Users/" +name+ ".txt";
        std::ofstream file(filePath);       
        file<<userName<<'\n';
        file<<password<<'\n';
        file<<email<<'\n';
        file.close();      
    };

};

bool SignUp(){
    std::string name, password,email;
    std::string pw;//comparison purpose
    std::cout<<"Please, enter your Username: "<<'\n';
    std::getline(std::cin, name);
    std::cout<<"Please, enter your email: "<<'\n';
    std::getline(std::cin, email);
    std::cout<<"Please, enter your password: "<<'\n';
    std::getline(std::cin,password); 
    std::cout<<"Please, reenter your password: " <<'\n';
    std::getline(std::cin,pw);
    if(password==pw){
        User user(name,password,email);
        user.saveInFile(name);
        return true;
    }else{
        return false;
    };
};
bool isLogedIn(){
    std::string name, pwd;
    std::cout<<"Please, enter your Username: "<<'\n';
    std::getline(std::cin, name);
    std::cout<<"Please, enter your password: ";
    std::getline(std::cin,pwd);
    std::string path= "Users/"+name+"txt";
    if(std::filesystem::exists(path)){
        std::string compName, compPwd, compEmail;
        std::ifstream file(path);
        std::getline(file,compName);
        std::getline(file,compPwd);
        std::getline(file,compEmail);
        if(compName==name && compPwd==pwd){
            return true;
        }
        else{
            return false;
        };
    }else{
        return false;
    };
};