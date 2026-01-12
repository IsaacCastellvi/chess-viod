#include <iostream>
#include "Board.h"
#include "gamemanager.h"
std::string hola = "hola";

int main(){
    setupUTF8();
    initGame(table,2);
    DrawTable(table);
    std::cout << "\n";
    DrawCell('a',3,3,1);
    DrawCell('a',3,3,1);    
    

    std::cout << "╭─────────╮\n";
    std::cout << "│ Hello!  │\n";
    std::cout << "╰─────────╯\n";
    return 0;
}