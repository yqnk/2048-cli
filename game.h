#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include <cstdlib>

class Game {
private:
    Grid grid;
    int moves;
    int score;
public:
    Game();
    void update(char*& message);
};

#endif