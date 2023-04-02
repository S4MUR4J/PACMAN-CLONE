#include "MapConventer.h"

std::array<std::array<Cell, mapHeight>, mapWidth> convert_sketch(const std::array<std::string, mapHeight> &i_map_sketch)
{
    std::array<std::array<Cell, mapHeight>, mapWidth> output_map{};

	for (unsigned char i = 0; i < mapHeight; i++)
	{
		for (unsigned char j = 0; j < mapWidth; j++)
		{
			//By default, every cell is empty.
			output_map[j][i] = Cell::Else;

            if(i_map_sketch[i][j] == '#') {
                output_map[j][i] = Cell::Wall;
            }
		}
	}

    return output_map;
}