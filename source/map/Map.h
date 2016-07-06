#pragma once
#include "../libs/pngUtil.h"
#include "../libs/lodepng.h"
#include "Cell.h"
#include "../managers/configuration/ConfigurationManager.h"

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
	Map(string& mapImageFilePath, float mapResolution,
		float gridResolution, RobotSize* robotSize);
	~Map();
	vector<unsigned char> getBlownImage();
	ImageSize* getImgSize();
	Cell*** getMap();
	ImageSize* getMapSize();
	void loadFromFile(string& mapImageFilePath);
	void readImageToGrid();
	void blowObstaclesInImage();
	void drawBlowedObstacle(ImageSize* radiusToDraw, int imgRow, int imgCol);
	bool inBound(int x, int y);
	int min(int num1, int num2);
	int max(int num1, int num2);
	bool isObstacleFound(int imgRow, int imgCol, ImageSize* gridChunk);

	Cell*** map;

private:
	float mapResolution, robotSizeInCells, gridResolution;
	RobotSize* robotSize;
	unsigned width, height;
	vector<unsigned char> originalImage;
	vector<unsigned char> blownImage;
	ImageSize* imgSize;
	ImageSize* mapSize;
};
