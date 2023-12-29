#ifndef GRID_H
#define GRID_H

#include <cstdlib>

class Grid
{
private:
    int data[16];

    void set(size_t index, int value);
public:
    Grid();
    Grid(int initData[16]);
    void print() const;
    int moveUp();
    int moveDown();
    int moveLeft();
    int moveRight();
    bool canMove() const;
    bool canMoveUp() const;
    bool canMoveDown() const;
    bool canMoveLeft() const;
    bool canMoveRight() const;
    void spawn(size_t count = 1);
};

#endif