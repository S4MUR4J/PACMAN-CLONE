#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Fruit {
private:
    sf::CircleShape shape;

    void initShape(const sf::RenderWindow& window);
public:
    Fruit(const sf::RenderWindow& window);
    virtual ~Fruit();

    const sf::CircleShape getShape() const;
    
    void update();
    void render(sf::RenderTarget& target);
};