#include "game.h"
#include <iostream>
#include <string.h>

int main(void) {
    char *message = strdup("Welcome to 2048!");

    Game game;
    game.update(message);

    free(message);

    return 0;
}