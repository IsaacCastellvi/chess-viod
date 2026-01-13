#include "mainmenu.h"
#include "iostream"
int Selected = 0;
std::vector<std::string> MainLayout = {"Whallahi im finised","$n","We are so back","HELL YEAHHHH"};
std::vector<std::string> OptionsLayout = {"HOLA BONES","$n"};
std::vector<std::string> GameLayout;
std::vector<std::string>* Current = nullptr;

void displayMenu(){
    if (Current == nullptr) return;
    for (size_t i = 0; i < Current->size(); i++)
    {
        if ((*Current)[i] == "$n")std::cout << "\n\n" ;
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
