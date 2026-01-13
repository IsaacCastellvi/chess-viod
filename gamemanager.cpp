#include "gamemanager.h"
#include <iostream>
#include "pieces.h"
#include <memory>
// using smart pointers for automatic memory managements

/*LAYOUT
r n b q k b n r
p p p p p p p p
# # # # # # # #
# # # # # # # #
# # # # # # # #
# # # # # # # #
P P P P P P P P
R N B Q K B N R
*/

void initGame(std::vector<std::vector<char>> & table,int lines = 2){
    table.assign(8, std::vector<char>(8, '#'));

    // Black pieces
    char blackBack[] = {'r','n','b','q','k','b','n','r'};
    for (int j = 0; j < 8; j++) {
        table[0][j] = blackBack[j];
        table[1][j] = 'p';
    }

    // White pieces
    char whiteBack[] = {'R','N','B','Q','K','B','N','R'};
    for (int j = 0; j < 8; j++) {
        table[6][j] = 'P';
        table[7][j] = whiteBack[j];
    }
}



void initGameOjects(std::vector<std::vector<std::shared_ptr<piece>>> & board)
{
    board.assign(8, std::vector<std::shared_ptr<piece>>(8, nullptr));

    // empty piece = base piece
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = std::make_shared<piece>(); // default '#' sprite

    // ----------------- Black pieces -----------------
    board[0][0] = std::make_shared<rook>(false);
    board[0][1] = std::make_shared<knight>(false);
    board[0][2] = std::make_shared<bishop>(false);
    board[0][3] = std::make_shared<queen>(false);
    board[0][4] = std::make_shared<king>(false);
    board[0][5] = std::make_shared<bishop>(false);
    board[0][6] = std::make_shared<knight>(false);
    board[0][7] = std::make_shared<rook>(false);

    for (int j = 0; j < 8; j++)
        board[1][j] = std::make_shared<pawn>(false);

    // ----------------- White pieces -----------------
    for (int j = 0; j < 8; j++)
        board[6][j] = std::make_shared<pawn>(true);

    board[7][0] = std::make_shared<rook>(true);
    board[7][1] = std::make_shared<knight>(true);
    board[7][2] = std::make_shared<bishop>(true);
    board[7][3] = std::make_shared<queen>(true);
    board[7][4] = std::make_shared<king>(true);
    board[7][5] = std::make_shared<bishop>(true);
    board[7][6] = std::make_shared<knight>(true);
    board[7][7] = std::make_shared<rook>(true);
}

EndCond GameLoop(){
    int Iwhite,Iblack;
    

    std::cout << "player white select your input ";
    std::cin >> Iwhite;

    std::cout << "player black select your input ";
    std::cin >> Iblack;
    return EndCond::_NULL;
}