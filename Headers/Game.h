#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Pacman.h"
#include "Fruit.h"
#include "Map.h"
#include <array>

class Game
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Event event;

    bool endGame;

    Pacman pacman;
    Map map;

    int points;

    std::vector<Fruit> fruits;
    float spawnTimerMax;
    float spawnTimer;
    int maxFruits;

    void initVariables();
    void initWindow();
public:
    Game();
    virtual ~Game();

    const bool getEndGame() const;
    const bool executing() const;
    void pollEvents();

    void generateMap();
    void spawnFruits();
    void updateCollision();
    
    void update();
    void render();
};