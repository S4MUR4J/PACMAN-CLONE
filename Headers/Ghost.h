#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Constants.h"

class Ghost {
    private:
        sf::RectangleShape shape;
        int movementSpeed;

        void initVariables();
        void initShapes(float x, float y);
    public:
        Ghost(const sf::RenderWindow& window, float x, float y);
        virtual ~Ghost();

        sf::RectangleShape getShape();

        void moveGhost();
        void update();
        void render(sf::RenderTarget *target);
};