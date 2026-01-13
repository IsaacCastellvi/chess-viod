#pragma once
#include <vector>
#include "string"
#define SKIP_CHAR = "$n"

extern std::vector<std::string> MainLayout;
extern std::vector<std::string> OptionsLayout;
extern std::vector<std::string> GameLayout;
extern std::vector<std::string>* Current;

extern int Selected;



enum Input {
    NONE,DOWN,UP,RIGTH,LEFT,ENTER,EXIT
};

// the character $n will represent line skip

void ToggleMenu();
void displayMenu();
void OnStart(); // set the current to a default before starting to aviod errors
void InitLayouts();
void ChancheCurrent(std::vector<std::string>& newM);
Input Getinput();
