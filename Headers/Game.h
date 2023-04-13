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
#include "Constants.h"
#include <array>

/**
 * @class Game
 * 
 * Klasa ta jest silnikiem gry składa w całość wszystkie inne klasy i interakcje między nimi.
 * Jako jedyna jest bezpośrednio wywołana w mainie. Odpowiada za zebranie rysowania obiektów na ekranie,
 * aktualizacje wszystkich obiektów oraz interakcje między nimi. Przechowuje również okno, które jest
 * w niej wywoływane i przepuszczane jako parametr do innych klas.
 */
class Game
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Event event;

    bool endGame;

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