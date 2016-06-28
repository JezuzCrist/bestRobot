#include "stdafx.h"
#include "Map.h"


Map::Map(string& mapImageFilePath)
{
	lodepng::decode(image, width, height, mapImageFilePath);
	map = new Cell**[height];
	for(int i = 0; i < (int)height; ++i)
		map[i] = new Cell*[width];

	int red, green, blue;
	float alpha;

	for (int i = 0; i < (int)height; i++)
	{
		for (int j = 0; j < (int)width; j++)
		{
			red = image[i * width * 4 + j * 4];
			green = image[i * width * 4 + j * 4 + 1];
			blue = image[i * width * 4 + j * 4 + 2];
			alpha = image[i * width * 4 + j * 4 + 3];
			Color *color = new Color(red, green, blue, alpha);
			bool is_walkable;
			if (red == 255 && green == 255 && blue == 255)
			{
				is_walkable = true;
			}
			else
			{
				is_walkable = false;
			}
			map[i][j] = new Cell(i, j, is_walkable, color);
		}
	}
}

Map::~Map()
{
	for(int i = 0; i < getHeight(); ++i) {
			delete [] map[i];
		}
		delete [] map;
}

bool Map::inBound(int x, int y)
{
	bool inBound = (x > -1 &&  x < this-> getHeight()  && 
					y > -1 && y < this-> getWidth());
	return inBound;
}

int Map::getWidth()
{
	return (int)width;
}

int Map::getHeight()
{
	return (int)height;
}

int Map::checkIfObstacle(std::vector<unsigned char> image, ImageSize* imgSize, int x, int y, ImageSize* gridChunk)
{
	for (int i = x; i < min(x + gridChunk->height, imgSize->height); i++)
	{
		for (int j = y; j < min(y + gridChunk->width, imgSize->width); j++)
		{
			if (image[i * imgSize->width * 4 + j * 4 + 0] != 255 ||
				image[i * imgSize->width * 4 + j * 4 + 1] != 255 ||
				image[i * imgSize->width * 4 + j * 4 + 2] != 255)
			{
				return 0;
			}
		}
	}
	return 255;
}

int Map::min(int num, int num1)
{
	if (num < num1)
	{
		return num;
	}
	return num1;
}
