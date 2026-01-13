#include <iostream>
#include "Board.h"
#include "gamemanager.h"
#include "mainmenu.h"
#include "vector"
#include "pieces.h"
#include "memory"

std::string hola = "hola";
Vector2 movement = {1,0};
std::vector<std::vector<std::shared_ptr<piece>>> objectTable;
int main() {
    std::cout << "=== CHESS GAME ===\n";
    std::cout << "Instructions:\n";
    std::cout << "- Enter moves using chess notation (e.g., select 'E2', then 'E4')\n";
    std::cout << "- White pieces are uppercase, Black pieces are lowercase\n";
    std::cout << "- Type 'resign' to resign\n";
    std::cout << "- Type 'draw' to offer a draw\n";
    std::cout << "- Type 'help' to show help\n";
    std::cout << "- Type 'cancel' during move selection to choose different piece\n\n";
    
    objectTable = InitializeBoard();

    EndCond result = GameLoop(objectTable);
    
    std::cout << "\n=== GAME OVER ===\n";
    switch(result) {
        case EndCond::WHITEWIN:
            std::cout << "White wins! Congrats (;\n";
            break;
        case EndCond::BLACKWIN:
            std::cout << "Black wins! Congrats (;\n";
            break;
        case EndCond::DRAW:
            std::cout << "Game ended in a draw =|\n";
            break;
        case EndCond::EXCEPTION:
            std::cout << "Game terminated.\n";
            break;
        default:
            std::cout << "Unknown result or undefined .\n";
    }
    
    // Show final objectTable
    std::cout << "\nFinal objectTable position:\n";
    DrawTableObjects(objectTable);
    
    return 0;
}