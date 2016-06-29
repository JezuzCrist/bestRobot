#pragma once
#include "pngUtil.h"
#include "lodepng.h"
#include "Cell.h"
#include "ConfigurationManager.h"

using namespace std;

class ImageSize {
public:
	int width;
	int height;

	ImageSize(int pWidth, int pHeight) {
		width = pWidth;
		height = pHeight;
	}
};

class Map
{
public:
	Map(string& mapImageFilePath, 
		float mapResolution, float gridResolution, RobotSize* robotSize);
	~Map();
	void Map::loadFromFile(string& mapImageFilePath);
	void Map::readImageToGrid();
	void Map::blowObstaclesInImage(vector<unsigned char> image);
	bool Map::inBound(int x, int y);
	int Map::min(int num, int num1);
	int getWidth();
	int getHeight();
	bool Map::isObstacleFound(std::vector<unsigned char> image, 
							  int imgRow, int imgCol, ImageSize* gridChunk);

	Cell*** map;

private:
	float mapResolution, robotSizeInCells, gridResolution;
	RobotSize* robotSize;
	unsigned width, height;
	vector<unsigned char> image;
	ImageSize* imgSize;
	ImageSize* mapSize;
};
