#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

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

        // Mouse positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        // Resources
        sf::Font font;

        //Text
        sf::Text uiText;

        // Game logic
        unsigned points;
        int health;
        bool endGame;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        bool mouseHeld;

        // Game objects
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        // Private functions
        void initVariables();
        void initWindow();
        void initFonts();
        void initText();
        void initEnemies();
    public:
        // Constructors / Destructors
        Game();
        virtual ~Game();

        // Accessors
        const bool getWindowIsOpen() const;
        const bool getEndGame() const;

        // Functions
        void spawnEnemy();

        void pollEvents();
        void updateMousePositions();
        void updateText();
        void updateEnemies();
        void update();

        void renderText(sf::RenderTarget& target);
        void renderEnemies(sf::RenderTarget& target);
        void render();
};