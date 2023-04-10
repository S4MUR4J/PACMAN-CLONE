#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Constants.h"

/**
 * @class Ghost
 * 
 * Klasa ta przechowuje dane oraz całą logikę działania przeciwników (tzw. duchów). Zmienia dane
 * na temat obiektu, rysuje go oraz odpowiada za poruszanie się.
 */
class Ghost {
    private:
        sf::RectangleShape shape;
        float movementSpeed;
        bool feared;
        sf::Vector2f playerOrigin;
        bool collisionTbl[4];

        MoveDirection moveDir;
        void initVariables();
        void initShapes(float x, float y);
    public:
        Ghost(const sf::RenderWindow& window, float x, float y);
        virtual ~Ghost();

        sf::RectangleShape getShape();
        
        void changeDir();
        sf::Vector2f getPlayerOrigin();
        sf::Vector2f setPlayerOrigin();
        bool isFeared();
        void Fear(bool isOff);
        bool collision(float posX, float posY);
        void moveGhost(float x, float y);
        void updateTeleportOnEdge(const sf::RenderTarget *target);
        void update(const sf::RenderTarget * target, float x, float y);
        void render(sf::RenderTarget *target);
};