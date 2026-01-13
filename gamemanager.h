#pragma once
#include <vector>
#include "memory"
#include "pieces.h"

// Header file (.h)
enum EndCond{
    _NULL, WHITEWIN, BLACKWIN, DRAW, EXEPTION
};

EndCond GameLoop();
void initGame(std::vector<std::vector<char>> & table,int lines);
void initGameOjects(std::vector<std::vector<std::shared_ptr<piece>>> & board);
//CALLED WHEN GAME START EUQAL TO STARTING A NEW GAME
