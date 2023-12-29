#include "game.h"

#include <iostream>
#include <string.h>

Game::Game() {
    grid = Grid();
    moves = 0;
    score = 0;
}

void Game::update(char *&message) {
    while (grid.canMove()) {
        // Clear screen
        std::cout << "\033[2J\033[1;1H";
        std::cout << message << std::endl;

        grid.print();
        std::cout << "Moves: " << moves << std::endl;
        std::cout << "Score: " << score << std::endl;
        std::cout << "Enter a move (z, q, s, d): ";

        char move = getchar();

        while (getchar() != '\n')
            ;

        switch (move) {
        case 'z':
            if (!grid.canMoveUp()) {
                free(message);
                message = strdup("Cannot move up!");
                continue;
            }
            score += grid.moveUp();
            break;
        case 'q':
            if (!grid.canMoveLeft()) {
                free(message);
                message = strdup("Cannot move left!");
                continue;
            }
            score += grid.moveLeft();
            break;
        case 's':
            if (!grid.canMoveDown()) {
                free(message);
                message = strdup("Cannot move down!");
                continue;
            }
            score += grid.moveDown();
            break;
        case 'd':
            if (!grid.canMoveRight()) {
                free(message);
                message = strdup("Cannot move right!");
                continue;
            }
            score += grid.moveRight();
            break;
        case 'x':
            std::cout << "Exiting..." << std::endl;
            return;
        default:
            std::cout << "Invalid move" << std::endl;
            continue;
        }

        free(message);
        message = strdup("");
        grid.spawn(1);
        ++moves;
    }

    // Clear screen
    std::cout << "\033[2J\033[1;1H";
    std::cout << message << std::endl;

    grid.print();
    std::cout << "Moves: " << moves << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "Game over after " << moves << " moves!\n"
              << "Final score: " << score << std::endl;
}