#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum MoveDirection{
    STOP,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

class Pacman{
private:
    sf::CircleShape shape;

    float movementSpeed;
    MoveDirection moveDirection;

    void initVariables();
    void initShapes();
public:
    Pacman(float x = 0.f, float y = 0.f);
    virtual ~Pacman();

    void railMoveHelper();
    void updateInput();
    void updateWindowBoundsCollision(const sf::RenderTarget* target);

    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};