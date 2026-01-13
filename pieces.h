#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "globals.h"

// Base class
class piece
{
public:
    //Vector2 Movements[] = {{0,0}};
    Vector2 Pos{4, 4};
    char Sprite{'#'};
    piece() = default;
    virtual void move(bool jump,Vector2& pos,std::vector<std::vector<std::shared_ptr<piece>>> &board);
    virtual ~piece() = default; // virtual destructor for polymorphism
};

inline void piece::move(bool jump, Vector2& pos, std::vector<std::vector<std::shared_ptr<piece>>> &board){
    
    Vector2 newPos = this->Pos;  
    newPos.Additive(pos);         

    // Check bounds
    if (board.empty() || board[0].empty() ||
        newPos.x < 0 || newPos.x >= board.size() || 
        newPos.y < 0 || newPos.y >= board[0].size()) {
        return; // Invalid move
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
    pawn(bool isWhite);
    ~pawn() override = default;
    void move(bool jump,Vector2& pos,std::vector<std::vector<std::shared_ptr<piece>>> &board) override{ 
        piece::move(jump,pos,board);
        std::cout << "aaaa";
    };
};

inline pawn::pawn(bool isWhite)
{
    Sprite = isWhite ? 'P' : 'p';
}

// ----------------- Rook -----------------
class rook : public piece
{
public:
    rook(bool isWhite);
    ~rook() override = default;
};

inline rook::rook(bool isWhite)
{
    Sprite = isWhite ? 'R' : 'r';
}

// ----------------- Knight -----------------
class knight : public piece
{
public:
    knight(bool isWhite);
    ~knight() override = default;
};

inline knight::knight(bool isWhite)
{
    Sprite = isWhite ? 'N' : 'n';
}

// ----------------- Bishop -----------------
class bishop : public piece
{
public:
    bishop(bool isWhite);
    ~bishop() override = default;
};

inline bishop::bishop(bool isWhite)
{
    Sprite = isWhite ? 'B' : 'b';
}

// ----------------- Queen -----------------
class queen : public piece
{
public:
    queen(bool isWhite);
    ~queen() override = default;
};

inline queen::queen(bool isWhite)
{
    Sprite = isWhite ? 'Q' : 'q';
}

// ----------------- King -----------------
class king : public piece
{
public:
    king(bool isWhite);
    ~king() override = default;
};

inline king::king(bool isWhite)
{
    Sprite = isWhite ? 'K' : 'k';
}






/*class piece
{
private:
    
public:

    char sprite = '#';
    piece();
    ~piece();
};

piece::piece()
{
}

//default deconstructor
piece::~piece()
{
}

// ####QUEEN
class queen : piece
{
private:
public:
    queen();
    ~queen();
};

queen::queen()
{
    sprite = '1';
}

queen::~queen()
{
}

class bishop : piece
{
private:
    
public:
    bishop();
    ~bishop();
};

bishop::bishop()
{
}

bishop::~bishop()
{
}

class horse : piece
{
private:
    
public:
    horse();
    ~horse();
};

horse::horse()
{
}

horse::~horse()
{
}

class rook
{
private:
    
public:
    rook();
    ~rook();
};

rook::rook()
{
}

rook::~rook()
{
}

class pawn
{
private:
    
public:
    pawn();
    ~pawn();
};

pawn::pawn()
{
}

pawn::~pawn()
{
}

*/