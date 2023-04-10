#include <iostream>
#include "Game.h"

/*
* Funkcja main zarządza wywołaniem silnika gry, który, który gdy
*  gra zostanie zakończona kończy działanie programu
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