#include <iostream>
#include <vector>

//GLobal table
extern std::vector<std::vector<char>> table;

void CreateTable(std::vector<std::vector<char>>& table,int size,char ch);
void DrawTable(std::vector<std::vector<char>>);
// 1 draw utf char 2 normal characters
void DrawCell(char ch,int size = 3,bool _UTF);
//UTF suport multiplatform
void setupUTF8();