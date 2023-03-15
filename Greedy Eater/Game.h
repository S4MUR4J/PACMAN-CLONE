#pragma once

#include <iostream>
#include <ctime>

#include "Player.h"

class Game
{
    private:
        sf::VideoMode videoMode;
        sf::RenderWindow* window;
        bool endGame;
        sf::Event sfmlEvent;

        Player player;

        void initVariables();
        void initWindow();

    public:
        // Constructors and Destructors
        Game();
        ~Game();

        // Accessors - get variables from this class

        // Modifiers - modify variables from this class

        // Functions - all that u can do with variables
        const bool running() const;
        void pollEvents();

        void update();
        void render();
};