#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Constants.h"

std::array<std::array<Cell, mapHeight>, mapWidth> convert_sketch(const std::array<std::string, mapHeight>& i_map_sketch);
