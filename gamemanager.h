#pragma once
#include <vector>
#include "memory"
#include "pieces.h"

enum EndCond {
    _NULL, WHITEWIN, BLACKWIN, DRAW, EXCEPTION  
};
EndCond GameLoop(std::vector<std::vector<std::shared_ptr<piece>>> &board);
//CALLED WHEN GAME START EUQAL TO STARTING A NEW GAME

void initGame(std::vector<std::vector<char>> & table,int lines);
std::vector<std::vector<std::shared_ptr<piece>>> InitializeBoard();

