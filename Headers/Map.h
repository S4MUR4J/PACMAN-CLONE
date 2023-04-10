#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Constants.h"

/**
 * @class Map
 * 
 * Klasa odpowiadająca za inicjację wyglądu bloku mapy, ustawienie jego pozycji oraz
 * ich renderowania, gdzie jest niezależna od budowy struktury mapy
 * 
 */
class Map {
private:
    sf::RectangleShape shape;

    void initShape(float x, float y);
public:
    Map(const sf::RenderWindow& window, float x, float y);
    virtual ~Map();

    void render(sf::RenderWindow& target);
};