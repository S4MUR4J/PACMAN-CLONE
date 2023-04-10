#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Pacman.h"
#include "Fruit.h"
#include "Map.h"
#include "SpecialFruit.h"
#include "Ghost.h"
#include <array>

class Game
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Event event;

    bool endGame;

    int sketch[mapHeight][mapWidth] = {
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4},
        {4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4},
        {4, 1, 3, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 3, 1, 4},
        {4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4},
        {4, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 4},
        {4, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 4},
        {4, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 4},
        {4, 4, 4, 4, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 4, 4, 4, 4},
        {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 4, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
        {4, 4, 4, 4, 4, 0, 0, 0, 1, 4, 7, 4, 1, 0, 0, 0, 4, 4, 4, 4, 4},
        {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
        {4, 4, 4, 4, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 4, 4, 4, 4},
        {4, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 4},
        {4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4},
        {4, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 4},
        {4, 1, 3, 0, 1, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 3, 1, 4},
        {4, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 4},
        {4, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 4},
        {4, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 4},
        {4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4}
    };

    Pacman pacman;

    int points;

    std::vector<Fruit> fruits;
    std::vector<Map> mapTiles;
    std::vector<SpecialFruit> specialFruits;
    std::vector<Ghost> ghosts;
    float spawnTimerMax;
    float spawnTimer;
    int maxFruits;

    void initVariables();
    void initMapTiles();
    void initFruits();
    void initWindow();
    void manageEndGame();
public:
    Game();
    virtual ~Game();

    const bool getEndGame() const;
    const bool executing() const;
    void pollEvents();

    void updateCollision();
    
    void update();
    void render();
};