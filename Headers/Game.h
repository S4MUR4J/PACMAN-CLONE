#pragma once

#include <iostream>
#include "Pacman.h"
#include "Fruit.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;

    bool endGame;

    Pacman pacman;
    Fruit fruit;

    void initVariables();
    void initWindow();
public:
    Game();
    virtual ~Game();

    const bool getWindowIsOpen() const;
    const bool getEndGame() const;

    void pollEvents();
    void update();
    void render();
};