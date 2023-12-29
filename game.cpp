#include "game.h"

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>

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

        while (getchar() != '\n');

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
            if (!grid.canMoveUp()) {
                free(message);
                message = strdup("Cannot move down!");
                continue;
            }
            score += grid.moveDown();
            break;
        case 'd':
            if (!grid.canMoveLeft()) {
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

    std::ifstream file("highscores.txt", std::ios::app);
    std::vector<int> scores;
    std::string line;

    while (std::getline(file, line)) {
        scores.push_back(std::stoi(line));
    }

    scores.push_back(score);
    std::sort(scores.begin(), scores.end());   

    std::ofstream file2("highscores.txt");
    for (auto it = scores.begin(); it != scores.end(); ++it) {
        file2 << *it << std::endl;
    }
    file.close();
    file2.close();

    grid.print();
    std::cout << "Moves: " << moves << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "Game over after " << moves << " moves!\n"
              << "Final score: " << score;
    if (scores.back() == score) {
        std::cout << " (New high score!)" << std::endl;
    } else {
        int i = 1;
        while (scores.back() != score) {
            scores.pop_back();
            ++i;
        }
        std::cout << "(#" << i << "/" << scores.size() << ")" << std::endl;
    }
}