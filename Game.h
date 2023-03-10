#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// moze byc samo pragma once i mozna rozszerzenie hpp
/**
 * Class that acts like game engine.
 * Class Wrapper
*/

class Game
{
    private:
        // Variables
        // Window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;

        // Game objects
        sf::RectangleShape enemy;

        // Private functions
        void initVariables();
        void initWindow();
        void initEnemies();
    public:
        // Constructors / Destructors
        Game();
        virtual ~Game();

        // Accessors
        const bool getWindowIsOpen() const;

        // Functions
        void pollEvents();
        void update();
        void render();
};