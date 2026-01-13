Unicode characters 
╭ (top-left) - U+256D
╮ (top-right) - U+256E
╰ (bottom-left) - U+2570
╯ (bottom-right) - U+256F
─ (horizontal line) - U+2500
│ (vertical line) - U+2502


- TECNICAL NOTES

THE TABLE IS DEFINED AS A VECTOR OF PIECES,THAT MEANS THAT
ON EMPTY SPACES IT WILL HAVE A PIECE OBJECT THAT MEANS ITS EMPTY AND ON OTHER SPACES WILL HAVE THE REQUIRED PIECE ON MOVEMNT WILL JUST INTERCHANCHE BOTH PIECE EVEN EMPTY ON THEIR POSITION

THE DRAW WILL BE EXECUTED AFTER THE LOGIC


#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "globals.h"

// Base class
class piece
{
public:
    Vector2 Pos{4, 4};
    char Sprite{'#'};
    
    // Movement properties
    Vector2 directions[8];
    int numDirections = 0;
    bool isSliding = false;
    
    piece() = default;
    virtual void move(bool jump,Vector2& pos,std::vector<std::vector<std::shared_ptr<piece>>> &board);
    virtual ~piece() = default;
};

inline void piece::move(bool jump, Vector2& pos, std::vector<std::vector<std::shared_ptr<piece>>> &board){
    
    Vector2 newPos = this->Pos;  
    newPos.Additive(pos);         

    // Check bounds
    if (board.empty() || board[0].empty() ||
        newPos.x < 0 || newPos.x >= board.size() || 
        newPos.y < 0 || newPos.y >= board[0].size()) {
        return;
    }

    Vector2 oldPos = this->Pos;
    
    this->Pos = newPos;
    std::swap(board[oldPos.x][oldPos.y], board[newPos.x][newPos.y]);
    
    std::cout << "Moved from (" << oldPos.x << "," << oldPos.y 
              << ") to (" << newPos.x << "," << newPos.y << ")" << std::endl;
}

// ----------------- Pawn -----------------
class pawn : public piece
{
public:
    bool firstMove = true;
    pawn(bool isWhite);
    ~pawn() override = default;
    void move(bool jump,Vector2& pos,std::vector<std::vector<std::shared_ptr<piece>>> &board) override{ 
        bool firstMove = false;
        piece::move(jump,pos,board);
        std::cout << "aaaa";
    };
};

inline pawn::pawn(bool isWhite)
{

    Sprite = isWhite ? 'P' : 'p';
    directions[0] = isWhite ? Vector2{-1, 0} : Vector2{1, 0};
    numDirections = 1;
    isSliding = false;
}

// ----------------- Rook -----------------
class rook : public piece
{
public:
    rook(bool isWhite);
    ~rook() override = default;
};

inline rook::rook(bool isWhite) : piece()
{
    Sprite = isWhite ? 'R' : 'r';
    Vector2 temp[4] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    std::copy(temp, temp + 4, directions);
    numDirections = 4;
    isSliding = true;
}

// ----------------- Knight -----------------
class knight : public piece
{
public:
    knight(bool isWhite);
    ~knight() override = default;
};

inline knight::knight(bool isWhite) : piece()
{
    Sprite = isWhite ? 'N' : 'n';
    Vector2 temp[8] = {{2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2}};
    std::copy(temp, temp + 8, directions);
    numDirections = 8;
    isSliding = false;
}

// ----------------- Bishop -----------------
class bishop : public piece
{
public:
    bishop(bool isWhite);
    ~bishop() override = default;
};

inline bishop::bishop(bool isWhite) : piece()
{
    Sprite = isWhite ? 'B' : 'b';
    Vector2 temp[4] = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};
    std::copy(temp, temp + 4, directions);
    numDirections = 4;
    isSliding = true;
}

// ----------------- Queen -----------------
class queen : public piece
{
public:
    queen(bool isWhite);
    ~queen() override = default;
};

inline queen::queen(bool isWhite) : piece()
{
    Sprite = isWhite ? 'Q' : 'q';
    Vector2 temp[8] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
    std::copy(temp, temp + 8, directions);
    numDirections = 8;
    isSliding = true;
}

// ----------------- King -----------------
class king : public piece
{
public:
    king(bool isWhite);
    ~king() override = default;
};

inline king::king(bool isWhite) : piece()
{
    Sprite = isWhite ? 'K' : 'k';
    Vector2 temp[8] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
    std::copy(temp, temp + 8, directions);
    numDirections = 8;
    isSliding = false;
}