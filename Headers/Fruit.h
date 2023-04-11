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

/**
 * Szablon ten jest getterem różnych typów zmiennych
 * 
 * @param data zmienna ktory chcemy przekazać
 * 
 * @return zwracamy zmienna obiektu
*/
template <typename T>
T getShapeTemplate(T data) {
    T result = data;
    return result;
}

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