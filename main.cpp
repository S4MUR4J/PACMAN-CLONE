#include<iostream>
#include "Game.h"

int main()
{
    //Init Game Engine
    Game game;

    // Loop in which one game must go on
    while (game.getWindowIsOpen())
    {
        // Update
        game.update();
        
        // Render screen
        game.render();
    } 

    // Close this app forever :O
    return 0;
}