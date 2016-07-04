#include "Map.h"


Map::Map(string& mapImageFilePath, float mapResolution,
         float gridResolution, RobotSize* robotSize)
{
	this->mapResolution = mapResolution;
	this->robotSize = robotSize;
	this->gridResolution = gridResolution;

	loadFromFile(mapImageFilePath);
}

Map::~Map()
{
	for(int i = 0; i < mapSize->height; ++i)
	{
		delete [] map[i];
	}
	delete [] map;
}

void Map::loadFromFile(string& mapImageFilePath)
{
	// Read image and save image size to member;
	unsigned height, width;
	lodepng::decode(this->image, width, height, mapImageFilePath);
	this->imgSize = new ImageSize(width, height);

	// Calc and save the grid size to member;
	int gridHeight = (int)(this->height *
						   this->mapResolution / this->gridResolution);
	int gridWidth = (int)(this->width *
						  this->mapResolution / this->gridResolution);
	this->mapSize = new ImageSize(gridWidth, gridHeight);

	blowObstaclesInImage(this->image);
	readImageToGrid();
}

void Map::readImageToGrid()
{
	bool isWalkable;
	int mapRow, mapCol, color;
	int resolutionRelation = (int)(this->gridResolution / this->mapResolution);

	// Define grid 2D array.
	this->map = new Cell**[mapSize->height];
	for(int i = 0; i < mapSize->height; i++)
		this->map[i] = new Cell*[mapSize->width];

	// Initialize grid 2D array.
	int imgRow = 0, imgCol = 0;
	for (imgRow = 0; imgRow < imgSize->height; imgRow += resolutionRelation)
	{
		for (imgCol = 0; imgCol < imgSize->width; imgCol += resolutionRelation)
		{
			mapRow = imgRow / resolutionRelation;
			mapCol = imgCol / resolutionRelation;
			color = this->image[imgRow * this->width * 4 + imgCol * 4];
			bool isWalkable = false;
			if (color == WHITE)
			{
				isWalkable = true;
			}
			this->map[mapRow][mapCol] = new Cell(mapRow, mapCol, isWalkable);
		}
	}
}

// Blow obstacles accroding to robot size.
void Map::blowObstaclesInImage(vector<unsigned char> image)
{
	bool isBlack;
	unsigned int color;
	ImageSize* radiusToSearchObstacle = new ImageSize(
						(int)(robotSize->width / 2.0 / this->mapResolution),
						(int)(robotSize->height / 2.0 / this->mapResolution));

	for (int imgRow = 0; imgRow < imgSize->height; imgRow++)
	{
		for (int imgCol = 0; imgCol < imgSize->width; imgCol++)
		{
			isBlack = isObstacleFound(image, imgRow, imgCol,
									  radiusToSearchObstacle);
			color = (isBlack == true) ? BLACK : WHITE;
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 0] = color;
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 1] = color;
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 2] = color;
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 3] = 255;
		}
	}
}

bool Map::isObstacleFound(std::vector<unsigned char> image, int imgRow,
						  int imgCol, ImageSize* radiusToSearchObstacle)
{
	int verticalRadius = min(imgRow + radiusToSearchObstacle->height,
							 imgSize->height);
	int horizontalRadius = min(imgCol + radiusToSearchObstacle->width,
							   imgSize->width);
	for (int i = imgRow; i < verticalRadius; i++)
	{
		for (int j = imgCol; j < horizontalRadius; j++)
		{
			if (image[i * imgSize->width * 4 + j * 4 + 0] != WHITE ||
				image[i * imgSize->width * 4 + j * 4 + 1] != WHITE ||
				image[i * imgSize->width * 4 + j * 4 + 2] != WHITE)
			{
				return true;
			}
		}
	}

	return false;
}

bool Map::inBound(int x, int y)
{
	bool inBound = (x > -1 &&  x < this-> mapSize->height &&
					y > -1 && y < this->  mapSize->width);
	return inBound;
}


int Map::min(int num, int num1)
{
	if (num < num1)
	{
		return num;
	}
	return num1;
}
