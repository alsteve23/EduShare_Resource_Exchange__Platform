#include<iostream>
#include<string>
#include<fstream>
#include"newUser.cpp"

int main(){
    std::cout<<"Welcome to the User Management System"<<'\n';
    std::cout<<"Please, choose an option: "<<'\n';
    std::cout<<"1. Sign Up"<<'\n';
    std::cout<<"2. Log In"<<'\n';
    std::cout<<"3. Exit"<<'\n';
    int option;
    std::cin>>option;
    std::cin.ignore();
    switch(option){
        case 1:
            if(SignUp()){
                std::cout<<"You have successfully signed up!"<<'\n';
            }else{
                std::cout<<"Passwords do not match!"<<'\n';
            };
            break;
        case 2:
            if(isLogedIn()){
                std::cout<<"You have successfully logged in!"<<'\n';
            }else{
                std::cout<<"Username or password is incorrect!"<<'\n';
            };
            break;
        case 3:
            std::cout<<"Goodbye!"<<'\n';
            break;
        default:
            std::cout<<"Invalid option!"<<'\n';
            break;
    };
    return 0;
};
