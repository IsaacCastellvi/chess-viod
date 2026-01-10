#include <iostream>
#include "Board.h"

std::string hola = "hola";

int main(){
    setupUTF8();
    std::cout << hola;
    CreateTable(table,6,'#');
    DrawTable(table);
    std::cout << "\n";
    DrawCell('a');
    std::cout << "\u256D";
    std::cout << "╭─────────╮\n";
    std::cout << "│ Hello! │\n";
    std::cout << "╰─────────╯\n";
    return 0;
}