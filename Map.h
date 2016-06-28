#pragma once
#include "pngUtil.h"
#include "lodepng.h"
#include "Cell.h"

using namespace std;

class ImageSize {
public:
	unsigned int width;
	unsigned int height;

	ImageSize(int pWidth, int pHeight) {
		width = pWidth;
		height = pHeight;
	}
};

class Map
{
public:
	Map(string& mapImageFilePath);
	~Map();
	void Map::loadFromFile(string& mapImageFilePath);
	bool Map::inBound(int x, int y);
	int Map::min(int num, int num1);
	int getWidth();
	int getHeight();
	int Map::checkIfObstacle(std::vector<unsigned char> image, 
							 ImageSize* imgSize, int x, int y, 
							 ImageSize* gridChunk);

	Cell*** map;

private:
	unsigned width, height;
	vector<unsigned char> image;
};
