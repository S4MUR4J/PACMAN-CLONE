#include <iostream>
#include "Game.h"

/**
 * Funkcja main zarządza wywołaniem silnika gry, który, który gdy
 * gra zostanie zakończona kończy działanie programu
 * 
 * @return int zwracane 0 gdy program został wykonany prawidłowo
 */
int main() {
    Game game;

    while(game.executing())
    {
        game.update();
        game.render();
    }

    return 0;
}