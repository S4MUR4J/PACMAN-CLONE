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
        float movementSpeed;
        bool feared;

        void initVariables();
        void initShapes(float x, float y);
    public:
        Ghost(const sf::RenderWindow& window, float x, float y);
        virtual ~Ghost();

        sf::RectangleShape getShape();

        bool isFeared();
        void Fear(bool isOff);
        void moveGhost(float x, float y);
        void updateTeleportOnEdge(const sf::RenderTarget *target);
        void update(const sf::RenderTarget * target, float x, float y);
        void render(sf::RenderTarget *target);
};