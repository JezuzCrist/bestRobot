#include "../../common/Position.h"
#include "fstream"
#include "sstream"
#include <iostream>
#include <stdlib.h>

using namespace std;

struct RobotSize
{
	double width, height;
};

class ConfigurationManager
{
public:
	ConfigurationManager(void);
	~ConfigurationManager(void);

	void parse(string);
	WorldPosition3D getRobotPositionFromString(string);
	RobotSize* getRobotSizeFromString(string);
	WorldPosition2D getMapPointFromString(string);

	string mapFileLocation;
	WorldPosition3D startPosition;
	WorldPosition2D goal;
	RobotSize* robotSize;
	double mapResolutionInCm;
	double gridResolutionInCm;
};

