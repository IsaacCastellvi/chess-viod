#include "Board.h"
#include <vector>
#include <iostream>
#include <memory>
#include "pieces.h"
#ifdef _WIN32
#include <windows.h>
#endif

void setupUTF8() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#else // linux,mac not implemented )=
    std::locale::global(std::locale("en_US.UTF-8"));
    std::cout.imbue(std::locale());
#endif
}

std::vector<std::vector<char>> table;

void CreateTable(std::vector<std::vector<char>>& table,int size,char ch){
    return;
}

void DrawCell(char ch, int size, int _UTF,int line)
{
    if (size < 1) return;

    char middleChar = ch;
    int width = size;

    switch (_UTF)
    {
    case 1:
        // UTF-8 box drawing
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < width + 2; col++) {
                if (row == 0) {
                    if (col == 0)
                        std::cout << u8"╭";
                    else if (col == width + 1)
                        std::cout << u8"╮";
                    else
                        std::cout << u8"─";
                }
                else if (row == 1) {
                    if (col == 0 || col == width + 1)
                        std::cout << u8"│";
                    else if (col == width / 2 + 1)
                        std::cout << middleChar;
                    else
                        std::cout << ' ';
                }
                else {
                    if (col == 0)
                        std::cout << u8"╰";
                    else if (col == width + 1)
                        std::cout << u8"╯";
                    else
                        std::cout << u8"─";
                }
            }
            //std::cout << '\n';
        }
        break;

    case 0:
        // ASCII box
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < width + 2; col++) {
                if (row == 0) {
                    if (col == 0 || col == width + 1)
                        std::cout << '+';
                    else
                        std::cout << '-';
                }
                else if (row == 1) {
                    if (col == 0 || col == width + 1)
                        std::cout << '|';
                    else if (col == width / 2 + 1)
                        std::cout << middleChar;
                    else
                        std::cout << ' ';
                }
                else {
                    if (col == 0 || col == width + 1)
                        std::cout << '+';
                    else
                        std::cout << '-';
                }
            }
            std::cout << '\n';
        }
        break;

    default:
        break;
    }
}


void DrawTable(std::vector<std::vector<char>> table) {
    for (size_t i = 0; i < table.size(); ++i) {
        for (size_t j = 0; j < table[i].size(); ++j) {
            std::cout << table[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void DrawTableObjects(std::vector<std::vector<std::shared_ptr<piece>>> & board) {
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[i].size(); ++j) {
            if (board[i][j]) {
                std::cout << board[i][j]->Sprite << " ";
            }
        }
        std::cout << std::endl; 
    }
}