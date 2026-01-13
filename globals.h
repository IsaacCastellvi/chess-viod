#pragma once
#include "iostream"
struct Vector2
{
    int x,y;
    void Additive(Vector2 add){
        this->x += add.x;
        this->y += add.y;
        std::cout << "updated" << add.x << add.y;
    }
    void Subtractive(Vector2 sub){
        this->x -= sub.x;
        this->y -= sub.y;
        std::cout << "updated " << sub.x << " " << sub.y;
    }
    //CUSTOM COMPARISON OPERATORS
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }
};
