#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Constants.h"

class SpecialFruit {
private:
    sf::CircleShape shape;

    void initShape(const sf::RenderWindow& window, float x, float y);
public:
    SpecialFruit(const sf::RenderWindow& window, float x, float y);
    virtual ~SpecialFruit();

    const sf::CircleShape getShape() const;
    
    void update();
    void render(sf::RenderTarget& target);
};