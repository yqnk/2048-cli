#include "grid.h"
#include <cstdlib>
#include <iostream>

Grid::Grid() {
    srand(time(nullptr));

    for (size_t i = 0; i < 16; ++i) {
        data[i] = 0;
    }

    spawn(2);
}

Grid::Grid(int initData[16]) {
    for (size_t i = 0; i < 16; ++i) {
        data[i] = initData[i];
    }
}

void Grid::spawn(size_t count) {
    srand(time(nullptr));

    for (size_t i = 0; i < count; ++i) {
        size_t index = rand() % 16;
        while (data[index] != 0) {
            index = rand() % 16;
        }
        data[index] = (rand() % 2 + 1) * 2;
    }
}

size_t countDigits(int value) {
    if (value == 0) {
        return 1;
    }

    size_t digits = 0;
    while (value != 0) {
        value /= 10;
        ++digits;
    }
    return digits;
}

char *buildCell(size_t length, int value) {
    char *line = new char[length + 1];
    std::string str;

    if (value != 0) {
        str = std::to_string(value);
        size_t padding = (length - str.length()) / 2;

        for (size_t i = 0; i < length; ++i) {
            if (i >= padding && i < padding + str.length()) {
                line[i] = str[i - padding];
            } else {
                line[i] = ' ';
            }
        }
    } else {
        for (size_t i = 0; i < length; ++i) {
            line[i] = ' ';
        }
    }

    line[length] = '\0';
    return line;
}

void Grid::print() const {
    // Get max column length
    size_t maxColumnLength = 1;
    for (size_t i = 0; i < 16; ++i) {
        size_t digits = countDigits(data[i]);
        if (digits > maxColumnLength) {
            maxColumnLength = digits;
        }
    }

    // Build correct separator
    size_t totalLength = (maxColumnLength + 2) * 4 + 5 + 1;
    char *separator = new char[totalLength];
    for (size_t i = 0; i < totalLength - 1; ++i) {
        separator[i] = (i % ((maxColumnLength + 2) + 1) == 0) ? '+' : '-';
    }
    separator[totalLength - 1] = '\0';
    std::cout << separator << std::endl;

    // Print the grid correctly
    for (size_t i = 0; i < 16; ++i) {
        std::cout << "| ";
        char *cell = buildCell(maxColumnLength, data[i]);

        // Switch statement for text color
        switch (data[i]) {
        case 2:
            std::cout << "\033[37m" << cell << "\033[0m"; // Gray text
            break;
        case 4:
            std::cout << "\033[93m" << cell << "\033[0m"; // Light yellow text
            break;
        case 8:
            std::cout << "\033[33m" << cell << "\033[0m"; // Dark yellow text
            break;
        case 16:
            std::cout << "\033[91m" << cell << "\033[0m"; // Red text
            break;
        case 32:
            std::cout << "\033[91;1m" << cell << "\033[0m"; // Brighter red text
            break;
        case 64:
            std::cout << "\033[91m" << cell << "\033[0m"; // Bright red text
            break;
        case 128:
            std::cout << "\033[91;2m" << cell << "\033[0m"; // Darker red text
            break;
        case 256:
            std::cout << "\033[32m" << cell << "\033[0m"; // Green text (light)
            break;
        case 512:
            std::cout << "\033[32;1m" << cell << "\033[0m"; // Bright green text
            break;
        case 1024:
            std::cout << "\033[32;2m" << cell << "\033[0m"; // Dark green text
            break;
        case 2048:
            std::cout << "\033[32;3m" << cell << "\033[0m"; // Another shade of green
            break;
        case 4096:
            std::cout << "\033[32;4m" << cell << "\033[0m"; // Another shade of green
            break;
        case 8192:
            std::cout << "\033[32;5m" << cell << "\033[0m"; // Another shade of green
            break;
        case 16384:
            std::cout << "\033[32;7m" << cell << "\033[0m"; // Another shade of green
            break;
        default:
            std::cout << cell;
        }

        std::cout << ' ';

        if (i % 4 == 3) {
            std::cout << '|' << std::endl;
            std::cout << separator << std::endl;
        }

        delete[] cell;
    }

    // Clean up
    delete[] separator;
}

void Grid::set(size_t index, int value) {
    if (index < 16) {
        data[index] = value;
    }
}

int Grid::moveUp() {
    int score{0};
    for (size_t i = 4; i < 16; ++i) {
        if (data[i] != 0) {
            size_t j = i;
            while (j >= 4 && data[j - 4] == 0) {
                set(j - 4, data[j]);
                set(j, 0);
                j -= 4;
            }

            if (j >= 4 && data[j - 4] == data[j]) {
                set(j - 4, data[j] * 2);
                set(j, 0);
                score += data[j - 4];
            }
        }
    }
    return score;
}

int Grid::moveDown() {
    int score{0};
    for (size_t i = 12; i > 0; --i) {
        if (data[i - 1] != 0) {
            size_t j = i - 1;
            while (j <= 11 && data[j + 4] == 0) {
                set(j + 4, data[j]);
                set(j, 0);
                j += 4;
            }

            if (j <= 11 && data[j + 4] == data[j]) {
                set(j + 4, data[j] * 2);
                set(j, 0);
                score += data[j + 4];
            }
        }
    }
    return score;
}

int Grid::moveLeft() {
    int score{0};
    for (size_t i = 0; i < 16; ++i) {
        if (data[i] != 0 && i % 4 != 0) {
            size_t j = i;
            while (j % 4 != 0 && data[j - 1] == 0) {
                set(j - 1, data[j]);
                set(j, 0);
                j -= 1;
            }

            if (j % 4 != 0 && data[j - 1] == data[j]) {
                set(j - 1, data[j] * 2);
                set(j, 0);
                score += data[j - 1];
            }
        }
    }
    return score;
}

int Grid::moveRight() {
    int score{0};
    for (size_t i = 16; i > 0; --i) {
        if (data[i - 1] != 0 && (i - 1) % 4 != 3) {
            size_t j = i - 1;
            while (j % 4 != 3 && data[j + 1] == 0) {
                set(j + 1, data[j]);
                set(j, 0);
                j += 1;
            }

            if (j % 4 != 3 && data[j + 1] == data[j]) {
                set(j + 1, data[j] * 2);
                set(j, 0);
                score += data[j + 1];
            }
        }
    }
    return score;
}

bool Grid::canMoveUp() const {
    for (size_t i = 4; i < 16; ++i) {
        if (data[i] != 0 && data[i - 4] == 0) {
            return true;
        }

        if (data[i] != 0 && data[i - 4] == data[i]) {
            return true;
        }
    }
    return false;
}

bool Grid::canMoveDown() const {
    for (size_t i = 12; i > 0; --i) {
        if (data[i - 1] != 0 && data[i + 4] == 0) {
            return true;
        }

        if (data[i - 1] != 0 && data[i + 4] == data[i]) {
            return true;
        }
    }
    return false;
}

bool Grid::canMoveLeft() const {
    for (size_t i = 0; i < 16; ++i) {
        if (data[i] != 0 && i % 4 != 0 && data[i - 1] == 0) {
            return true;
        }

        if (data[i] != 0 && i % 4 != 0 && data[i - 1] == data[i]) {
            return true;
        }
    }
    return false;
}

bool Grid::canMoveRight() const {
    for (size_t i = 16; i > 0; --i) {
        if (data[i - 1] != 0 && (i - 1) % 4 != 3 && data[i] == 0) {
            return true;
        }

        if (data[i - 1] != 0 && (i - 1) % 4 != 3 && data[i] == data[i - 1]) {
            return true;
        }
    }
    return false;
}

bool Grid::canMove() const {
    return canMoveUp() || canMoveDown() || canMoveLeft() || canMoveRight();
}