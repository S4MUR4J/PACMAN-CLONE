#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Constants.h"

/**
 * @class Fruit
 * 
 * Klasa przechowyjąca informacje na temat mniejszych owoców. Odpowiada za ustawienie
 * parametów tego obiektu, aktualizacje ich oraz rysowanie na ekranie.
 */
class Fruit {
private:
    sf::RectangleShape shape;

    void initShape(const sf::RenderWindow& window, float x, float y);
public:   
    Fruit(const sf::RenderWindow& window, float x, float y);
    virtual ~Fruit();

    const sf::RectangleShape getShape() const;
    
    virtual void render(sf::RenderTarget& target);
};