#include "fstream"
#include "sstream"
#include <iostream>
#include <stdlib.h>

using namespace std;

struct MapPoint
{
	int x, y;
};
struct RobotSize
{
	double width, height;
};
struct RobotPosition
{
	MapPoint point;
	double angle;
};

class ConfigurationManager
{
public:
	ConfigurationManager(void);
	~ConfigurationManager(void);

	void parse(string);
	RobotPosition getRobotPositionFromString(string);
	RobotSize getRobotSizeFromString(string);
	MapPoint getMapPointFromString(string);

	string mapFileLocation;
	RobotPosition startPosition;
	MapPoint goal;
	RobotSize size;
	double mapResolutionInCm;
	double gridResolutionInCm;
};

