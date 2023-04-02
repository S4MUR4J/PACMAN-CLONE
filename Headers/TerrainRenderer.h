#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Constants.h"

void draw_map(const std::array<std::array<Cell, mapHeight>, mapWidth>& i_map, sf::RenderWindow& i_window);
