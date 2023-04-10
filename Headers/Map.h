#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Constants.h"

/*
*   Klasa odpowiadająca za zainicjowanie wyglądu bloku mapy, ustawienie jego pozycji
*   oraz renderowanie każdego z nich szczegóły przy funkcjach w .cpp
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