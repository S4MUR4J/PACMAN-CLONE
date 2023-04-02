#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Fruit {
private:
    sf::CircleShape shape;

    void initShape();
public:
    Fruit(float x = 1000.f, float y = 1000.f);
    virtual ~Fruit();

    const sf::CircleShape getShape() const;
    
    void update();
    void render(sf::RenderTarget& target);
};