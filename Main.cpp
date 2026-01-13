#include <iostream>
#include "Board.h"
#include "gamemanager.h"
#include "mainmenu.h"
#include "vector"
#include "pieces.h"
#include "memory"

std::string hola = "hola";
Vector2 movement = {2,0};
std::vector<std::vector<std::shared_ptr<piece>>> objectTable;
int main(){
    initGameOjects(objectTable);
    //setupUTF8();
    //initGame(table,2);
    //DrawTable(table);
    std::cout << "\n";
    //DrawCell('squeare',3,3,1);
    //DrawCell('squeare',3,3,1);    
    
    DrawTableObjects(objectTable);
    std::cout << "╭─────────╮\n";
    std::cout << "│ Hello!  │\n";
    std::cout << "╰─────────╯\n";
    OnStart();
    //FIX CHANCHING MENU
    displayMenu();
    ChancheCurrent(OptionsLayout);
    displayMenu();
    GameLoop();
    auto& square = objectTable[6][0]; // white pawn at a2



    std::cout << square->Sprite << square->Pos.x << square->Pos.y << std::endl ;
    square->move(false,movement,objectTable);
    std::cout << "updated Piece: " << square->Pos.x << square->Pos.y << std::endl ;
    DrawTableObjects(objectTable);
    return 0;
}