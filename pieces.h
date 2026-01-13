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
    bool isWhite = true;
    
    // Movement properties
    Vector2 directions[8];
    int numDirections = 0;
    bool isSliding = false;
    
    piece() = default;
    virtual bool isValidMove(Vector2& targetPos, std::vector<std::vector<std::shared_ptr<piece>>>& board);
    virtual void move(bool jump,Vector2& pos,std::vector<std::vector<std::shared_ptr<piece>>> &board);
    virtual ~piece() = default;
};

// Check if a move is valid for this piece
inline bool piece::isValidMove(Vector2& targetPos, std::vector<std::vector<std::shared_ptr<piece>>>& board) {
    // Check bounds
    if (board.empty() || board[0].empty() ||
        targetPos.x < 0 || targetPos.x >= board.size() || 
        targetPos.y < 0 || targetPos.y >= board[0].size()) {
        return false;
    }
    
    // Can't capture own piece
    if (board[targetPos.x][targetPos.y] != nullptr && 
        board[targetPos.x][targetPos.y]->isWhite == this->isWhite) {
        return false;
    }
    
    // Calculate movement vector
    Vector2 delta = {targetPos.x - Pos.x, targetPos.y - Pos.y};
    
    // Check if movement matches any valid direction
    for (int i = 0; i < numDirections; i++) {
        Vector2 dir = directions[i];
        
        if (isSliding) {
            // For sliding pieces (rook, bishop, queen)
            // Check if target is along this direction
            if (delta.x == 0 && delta.y == 0) return false;
            
            // Check if direction matches
            if (dir.x != 0 && dir.y != 0) {
                // Diagonal movement
                if (delta.x * dir.y != delta.y * dir.x) continue; // Not on same diagonal
                if ((delta.x > 0) != (dir.x > 0) || (delta.y > 0) != (dir.y > 0)) continue; // Wrong direction
            } else if (dir.x != 0) {
                // Vertical movement
                if (delta.y != 0) continue;
                if ((delta.x > 0) != (dir.x > 0)) continue;
            } else {
                // Horizontal movement
                if (delta.x != 0) continue;
                if ((delta.y > 0) != (dir.y > 0)) continue;
            }
            
            // Check path is clear
            int steps = std::max(std::abs(delta.x), std::abs(delta.y));
            Vector2 step = {delta.x / steps, delta.y / steps};
            
            for (int s = 1; s < steps; s++) {
                Vector2 checkPos = {Pos.x + step.x * s, Pos.y + step.y * s};
                if (board[checkPos.x][checkPos.y] != nullptr) {
                    return false; // Path blocked
                }
            }
            
            return true; // Valid sliding move
            
        } else {
            // For non-sliding pieces (knight, king)
            if (delta.x == dir.x && delta.y == dir.y) {
                return true; // Exact match
            }
        }
    }
    
    return false; // No valid direction found
}

inline void piece::move(bool jump, Vector2& pos, std::vector<std::vector<std::shared_ptr<piece>>> &board){
    
    Vector2 newPos = this->Pos;  
    newPos.Additive(pos);
    
    // Check if move is valid
    if (!isValidMove(newPos, board)) {
        std::cout << "Invalid move!" << std::endl;
        return;
    }

    Vector2 oldPos = this->Pos;
    
    this->Pos = newPos;
    board[newPos.x][newPos.y] = board[oldPos.x][oldPos.y];  
    board[oldPos.x][oldPos.y] = nullptr;                   
    
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
    bool isValidMove(Vector2& targetPos, std::vector<std::vector<std::shared_ptr<piece>>>& board) override;
    void move(bool jump,Vector2& pos,std::vector<std::vector<std::shared_ptr<piece>>> &board) override;
};

inline pawn::pawn(bool isWhite)
{
    this->isWhite = isWhite;
    Sprite = isWhite ? 'P' : 'p';
    directions[0] = isWhite ? Vector2{-1, 0} : Vector2{1, 0};
    numDirections = 1;
    isSliding = false;
}

inline bool pawn::isValidMove(Vector2& targetPos, std::vector<std::vector<std::shared_ptr<piece>>>& board) {
    // Check bounds
    if (board.empty() || board[0].empty() ||
        targetPos.x < 0 || targetPos.x >= board.size() || 
        targetPos.y < 0 || targetPos.y >= board[0].size()) {
        return false;
    }
    
    Vector2 delta = {targetPos.x - Pos.x, targetPos.y - Pos.y};

    //(porpably temporal)solution for the both players having a diferent axis for forward
    int forward = isWhite ? -1 : 1;
    
    // Forward move (1 or 2 squares if inital movement)
    if (delta.y == 0) {
        if (delta.x == forward && board[targetPos.x][targetPos.y] == nullptr) {
            return true; // Move 1 forward
        }
        if (firstMove && delta.x == forward * 2 && 
            board[targetPos.x][targetPos.y] == nullptr &&
            board[Pos.x + forward][Pos.y] == nullptr) {
            firstMove = false;
            return true; // Move 2 forward on first move
        }
    }
    
    // Diagonal capture
    if (delta.x == forward && std::abs(delta.y) == 1) {
        if (board[targetPos.x][targetPos.y] != nullptr &&
            board[targetPos.x][targetPos.y]->isWhite != this->isWhite) {
            return true; // Capture
        }
    }
    
    return false;
}

inline void pawn::move(bool jump, Vector2& pos, std::vector<std::vector<std::shared_ptr<piece>>>& board) {
    Vector2 newPos = this->Pos;
    newPos.Additive(pos);
    
    if (!isValidMove(newPos, board)) {
        std::cout << "Invalid pawn move!" << std::endl;
        return;
    }
    
    Vector2 oldPos = this->Pos;
    this->Pos = newPos;
    firstMove = false;
    //Replace the std::swap i was using with just normal cahnching + dead nullptr
    board[newPos.x][newPos.y] = board[oldPos.x][oldPos.y];  
    board[oldPos.x][oldPos.y] = nullptr;                    
    std::cout << "Pawn moved from (" << oldPos.x << "," << oldPos.y 
              << ") to (" << newPos.x << "," << newPos.y << ")" << std::endl;
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
    this->isWhite = isWhite;
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
    this->isWhite = isWhite;
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
    this->isWhite = isWhite;
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
    this->isWhite = isWhite;
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
    this->isWhite = isWhite;
    Sprite = isWhite ? 'K' : 'k';
    Vector2 temp[8] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
    std::copy(temp, temp + 8, directions);
    numDirections = 8;
    isSliding = false;
}