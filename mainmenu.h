#pragma once
#include <vector>
#include "string"

std::vector<std::string> MainLayout;
std::vector<std::string> OptionsLayout;
std::vector<std::string> GameLayout;

std::vector<std::string>* Current;

enum Input {
    NONE,DOWN,UP,RIGTH,LEFT,ENTER,EXIT
};


void displayMenu(std::vector<std::string> ActiveDisplay);
void OnStart(std::vector<std::string>); // set the current to a default before starting to aviod errors
void InitLayouts();
void ChancheCurrent();
Input Getinput();
