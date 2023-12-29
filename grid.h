#ifndef GRID_H
#define GRID_H

#include <cstdlib>

class Grid
{
private:
    int data[16];

    void set(size_t index, int value);
    void setData(int newData[16]);
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
    bool canMoveLeft() const;
    void spawn(size_t count = 1);
    void rotate(int numTurns);
};

#endif