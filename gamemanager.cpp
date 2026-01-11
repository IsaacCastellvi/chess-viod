#include "gamemanager.h"
#include "iostream"
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