#include "TerrainRenderer.h"

void draw_map(const std::array<std::array<Cell, mapHeight>, mapWidth> &i_map, sf::RenderWindow &i_window)
{
    sf::Sprite sprite;

	//sf::Texture texture;
	//texture.loadFromFile("Sprites/map.png");

	//sprite.setTexture(texture);
    
    for (unsigned char i = 0; i < mapWidth; i++) {
        for (unsigned char j = 0; j < mapWidth; j++) {
            //sprite.setPosition(static_cast<float>(cellSize * i), static_cast<float>(cellSize * j));
            if(i_map[i][j] == '#') {
                //sprite.setTextureRect(sf::IntRect(2 * cellSize, cellSize, cellSize, cellSize));
                //i_window.draw(sprite);
            }
        }
    }
}