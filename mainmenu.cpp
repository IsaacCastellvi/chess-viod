#include "mainmenu.h"
#include "iostream"
int Selected = 0;
std::vector<std::string> MainLayout = {"Start","$n","Options","$n","Exit"};
std::vector<std::string> OptionsLayout = {"...","$n"};
std::vector<std::string> GameLayout;
std::vector<std::string>* Current = nullptr;

void displayMenu(){
    if (Current == nullptr) return;
    for (size_t i = 0; i < Current->size(); i++)
    {
        if ((*Current)[i] == "$n")std::cout << "\n" ;
        else if (Selected == i) std::cout << "-> " << (*Current)[i] << "\n";
        else std::cout << (*Current)[i] << "\n";
    }
    std::cout << std::endl;
    
}

void OnStart(){
    Current = &MainLayout;
    //debug std::cout << (*Current)[0];
}

void ChancheCurrent(std::vector<std::string>& newM){
    Current = &newM;
    Selected = 0;
}
