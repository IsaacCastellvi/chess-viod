#include "Board.h"
#include <vector>
#include <iostream>

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
    //vector constructors instead of iteration
    table = std::vector<std::vector<char>>(size,std::vector<char>(size,ch));
    return;
}
void DrawCell(char ch,int size){
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; i++)
        {
            if (i == 0 && j == 0) std::cout << "\u256D";
            if ((i == 0 && j != 0) || (i == 0 && j != size)) std::cout << "─";
            std::cout << "\u256D";
        }
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
