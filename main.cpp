#include <iostream>
#include "Headers/Game.h"

int main() {
    Game game;

    while(game.getWindowIsOpen() && !game.getEndGame())
    {
        game.update();
        game.render();
    }

    return 0;
}