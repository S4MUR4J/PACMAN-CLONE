#include<iostream>
#include "Game.h"

int main()
{
    // Initialize srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init Game Engine
    Game game;

    // Loop in which one game must go on
    while(game.getWindowIsOpen() && !game.getEndGame())
    {
        // Update
        game.update();
        
        // Render screen
        game.render();
    }

    // Close this app forever :O
    return 0;
}