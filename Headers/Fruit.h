#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Constants.h"

class Fruit {
private:
    sf::RectangleShape shape;

    void initShape(const sf::RenderWindow& window, float x, float y);
public:
    Fruit(const sf::RenderWindow& window, float x, float y);
    virtual ~Fruit();

    const sf::RectangleShape getShape() const;
    
    void update();
    void render(sf::RenderTarget& target);
};