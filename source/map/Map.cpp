#include "Map.h"


Map::Map(string& mapImageFilePath, float mapResolution,
         float gridResolution, RobotSize* robotSize)
{
	this->imageFileName = mapImageFilePath;
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

	for(int i = 0; i < mapSize->height; ++i)
	{
		delete [] this->blurryMap[i];
	}
	delete [] this->blurryMap;
}

void Map::loadFromFile(string& mapImageFilePath)
{
	// Read original image and save image size to member;
	unsigned height, width;
	lodepng::decode(this->originalImage, width, height, "/home/user/Desktop/roboticLabMap.png");
	vector<unsigned char> copiedImage(this->originalImage);
	this->blownImage = copiedImage;
	vector<unsigned char> copiedImage1(this->originalImage);
	this->blurryImage = copiedImage1;
	cout << "width  "<< width << endl;
	this->imgSize = new ImageSize(width, height);

	// Calc and save the grid size to member;
	int gridHeight = (int)(this->imgSize->height *
						   this->mapResolution / this->gridResolution);
	int gridWidth = (int)(this->imgSize->width *
						  this->mapResolution / this->gridResolution);
	this->mapSize = new ImageSize(gridWidth, gridHeight);

	blowObstaclesInImage();
	this->map = readImageToGrid(this->blownImage);
	blurImage();
	this->blurryMap = readImageToGrid(this->blurryImage);
	ConfigurationManager configs = ConfigurationManager();
	configs.parse("parameters.txt");
	PositionConveter* positionConverter = new PositionConveter(&configs);
	printObsticalsAndMap(positionConverter, this, this->imgSize);
}

Cell*** Map::readImageToGrid(vector<unsigned char> image)
{
	int mapRow, mapCol, red, green, blue;
	int resolutionRelation = (int)(this->gridResolution / this->mapResolution);

	// Define grid 2D array.
	Cell*** map = new Cell**[mapSize->height];
	for(int i = 0; i < mapSize->height; i++)
		map[i] = new Cell*[mapSize->width];

	// Initialize grid 2D array.
	int imgRow = 0, imgCol = 0;
	for (imgRow = 0; imgRow < imgSize->height; imgRow += resolutionRelation)
	{
		for (imgCol = 0; imgCol < imgSize->width; imgCol += resolutionRelation)
		{
			mapRow = imgRow / resolutionRelation;
			mapCol = imgCol / resolutionRelation;
			red = image[imgRow * imgSize->width * 4 + imgCol * 4];
			green = image[imgRow * imgSize->width * 4 + imgCol * 4 +1];
			blue = image[imgRow * imgSize->width * 4 + imgCol * 4 + 2];
			bool isWalkable = false;
			if (red == 255 && green == 255 && blue == 255)
			{
				isWalkable = true;
			}
			cout << "mapRow " << mapRow << " mapCol " << mapCol <<endl;
			map[mapRow][mapCol] = new Cell(mapCol, mapRow, isWalkable);
		}
	}
	return map;
}

void Map::printObsticalsAndMap(PositionConveter* positionConverter,
							   Map* map, ImageSize* imgSize)
{
	WorldPosition2D* worldPosition;

	vector<unsigned char> image(map->originalImage);
	encodeOneStep("/home/user/Desktop/dsafsasfdg.png", this->originalImage, imgSize->width, imgSize->height);
	Cell*** grid = map->getBlurryMap();
	ImageSize* mapSize = map->getMapSize();

	for (int row=0; row < mapSize->height; row++)
	{
		for (int col=0; col<mapSize->width; col++)
		{
			int x = grid[row][col]->x;
			int y = grid[row][col]->y;
			MapPosition2D* mapPosition = new MapPosition2D(x, y);
			worldPosition = positionConverter->getWorldPosition2D(mapPosition);
			int imgRow = worldPosition->y;
			int imgCol = worldPosition->x;
			int color;
			if (grid[row][col]->walkable)
			{
				color = 255;
			}
			else
			{
				color = 0;
			}
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 0] = color;
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 1] = 255;
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 2] = 255;
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 3] = 255;
		}
	}
	encodeOneStep("/home/user/Desktop/afterBlurryMap.png", image, imgSize->width, imgSize->height);
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

void Map::blurImage()
{
	double r = 5.0;
	double rs = ceil(r * 1.5);     // significant radius
	int height = this->imgSize->height;
	int width = this->imgSize->width;
	for(int i = 0; i < this->imgSize->height; i++)
	{
		for(int j = 0; j < this->imgSize->width; j++)
		{
			double val = 0, wsum = 0;
			for(double iy = i - rs; iy < i + rs + 1; iy++)
			{
				for(double ix = j - rs; ix < j + rs + 1; ix++)
				{
					double x = min((double)width - 1, max(0.0, ix));
					double y = min((double)height-1, max(0.0, iy));
					double dsq = (ix - j) * (ix - j) + (iy - i) * (iy - i);
					double wght = exp(-dsq / ( 2 * r * r)) /
					              (M_PI * 2 * r * r);
					val += this->blownImage[4 * y * width + 4 * x] * wght;
					wsum += wght;
				}
			}
			this->blurryImage[4 * i * width + 4 * j + 0] = round(val/wsum);
			this->blurryImage[4 * i * width + 4 * j + 1] = round(val/wsum);
			this->blurryImage[4 * i * width + 4 * j + 2] = round(val/wsum);
			this->blurryImage[4 * i * width + 4 * j + 3] = 255;
		}
	}
	encodeOneStep("/home/user/Desktop/afterBlurry.png", this->blurryImage, (unsigned)width, (unsigned)height);
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

Cell*** Map::getBlurryMap()
{
	return blurryMap;
}
