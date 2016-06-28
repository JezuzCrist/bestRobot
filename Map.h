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
	Map(void);
	~Map(void);

	Point*** map;

private:
	int width, height;
	vector<unsigned char> image;
};



