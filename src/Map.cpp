#include "Map.h"

void Map::initShape(float x, float y)
{
    this->shape.setSize(sf::Vector2f(cellSize, cellSize));
    this->shape.setFillColor(sf::Color::Blue);
    this->shape.setPosition(x, y);
}

Map::Map(const sf::RenderWindow& window, float x, float y)
{
    this->initShape(x, y);
}

Map::~Map()
{

}

void Map::render(sf::RenderWindow & target)
{
    target.draw(this->shape);         
}
