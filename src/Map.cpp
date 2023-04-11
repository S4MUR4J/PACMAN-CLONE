#include "Map.h"

/**
*   Funkcja inicjuje podstawowe parametry obiektu tj. rozmiar,
*   kolor oraz pozycja
*
*   @param x pozycja x na którą ustawimy obiekt
*   @param y pozycja y na którą ustawimy obiekt
*
*/
void Map::initShape(float x, float y)
{
    this->shape.setSize(sf::Vector2f(cellSize, cellSize));
    this->shape.setFillColor(sf::Color::Blue);
    this->shape.setPosition(x, y);
}

/**
*   Konstruktor obiektu odpowiadający za wywołanie obiektu a z nim
*   inicjację kształtu

*   @param window okno na którym jest inicjowany obiekt
*   @param x pozycja x na którym będzie znajdować się obiekt
*   @param y pozycja y na którym będzie znajdować się obiekt
*/
Map::Map(const sf::RenderWindow& window, float x, float y)
{
    this->initShape(x, y);
}

/**
* Destruktor obiektu
*/
Map::~Map()
{

}

/**
*   funkcja rysuje pojedyncze obiekty mapy na oknie

*   @param target okno na którym ma być rysowany obiekt 
*/
void Map::render(sf::RenderWindow & target)
{
    target.draw(this->shape);         
}
