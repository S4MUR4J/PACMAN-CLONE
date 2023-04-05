#include "Map.h"

void Map::initShape()
{
    this->texture.loadFromFile("./assets/map.png");
    this->sprite.setTexture(texture);
    sprite.setColor(sf::Color::Cyan);
}

Map::Map()
{
    this->initShape();
}

Map::~Map()
{

}

void Map::render(sf::RenderWindow & target)
{
    for(int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            this->sprite.setPosition(static_cast<float>(cellSize * i), static_cast<float>(cellSize * j));
            if (map[j][i] == 1) {
                this->sprite.setTextureRect(sf::IntRect(cellSize, cellSize, cellSize, cellSize));
                target.draw(this->sprite);
            }
        }
    }
}
