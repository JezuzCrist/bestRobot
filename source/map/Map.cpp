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
	// Read original image and save image size to member;
	unsigned height, width;
	lodepng::decode(this->originalImage, width, height, mapImageFilePath);
	vector<unsigned char> copiedImage(this->originalImage);
	this->blownImage = copiedImage;
	cout << width << endl;
	this->imgSize = new ImageSize(width, height);

	// Calc and save the grid size to member;
	int gridHeight = (int)(this->imgSize->height *
						   this->mapResolution / this->gridResolution);
	int gridWidth = (int)(this->imgSize->width *
						  this->mapResolution / this->gridResolution);
	this->mapSize = new ImageSize(gridWidth, gridHeight);

	blowObstaclesInImage();
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
			color = this->blownImage[imgRow * imgSize->width * 4 + imgCol * 4];
			bool isWalkable = false;
			if (color == WHITE)
			{
				isWalkable = true;
			}
			cout << "mapRow " << mapRow << " mapCol " << mapCol <<endl;
			this->map[mapRow][mapCol] = new Cell(mapCol, mapRow, isWalkable);
		}
	}
}

// Blow obstacles accroding to robot size.
void Map::blowObstaclesInImage()
{
	bool isBlack;
	unsigned int color;
	ImageSize* radiusToSearchObstacle = new ImageSize(
						(int)(robotSize->width / this->mapResolution),
						(int)(robotSize->height / this->mapResolution));

	for (int imgRow = 0; imgRow < imgSize->height; imgRow++)
	{
		for (int imgCol = 0; imgCol < imgSize->width; imgCol++)
		{
			isBlack = isObstacleFound(imgRow, imgCol,
									  radiusToSearchObstacle);
			color = (isBlack == true) ? BLACK : WHITE;
			this->blownImage[imgRow * imgSize->width * 4 + imgCol * 4 + 0] = color;
			this->blownImage[imgRow * imgSize->width * 4 + imgCol * 4 + 1] = color;
			this->blownImage[imgRow * imgSize->width * 4 + imgCol * 4 + 2] = color;
			this->blownImage[imgRow * imgSize->width * 4 + imgCol * 4 + 3] = 255;
		}
	}
}

bool Map::isObstacleFound(int imgRow, int imgCol,
		                  ImageSize* radiusToSearchObstacle)
{
	int verticalRadius = min(imgRow + radiusToSearchObstacle->height / 2,
							 imgSize->height);
	int horizontalRadius = min(imgCol + radiusToSearchObstacle->width / 2,
							   imgSize->width);
	int startRowToSearch = max(radiusToSearchObstacle->height / 2 * -1 + imgRow, 0);
	int startColToSearch = max(radiusToSearchObstacle->width / 2 * -1 + imgCol, 0);
	for (int i = startRowToSearch; i < verticalRadius; i++)
	{
		for (int j = startColToSearch; j < horizontalRadius; j++)
		{
			if (this->originalImage[i * imgSize->width * 4 + j * 4 + 0] != WHITE ||
				this->originalImage[i * imgSize->width * 4 + j * 4 + 1] != WHITE ||
				this->originalImage[i * imgSize->width * 4 + j * 4 + 2] != WHITE)
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


int Map::min(int num1, int num2)
{
	return num1 < num2 ? num1 : num2;
}

int Map::max(int num1, int num2)
{
	return num1 < num2 ? num2 : num1;
}

vector<unsigned char> Map::getBlownImage()
{
	return this->blownImage;
}

ImageSize* Map::getImgSize()
{
	return this->imgSize;
}

Cell*** Map::getMap()
{
	return this->map;
}

ImageSize* Map::getMapSize()
{
	return this->mapSize;
}
