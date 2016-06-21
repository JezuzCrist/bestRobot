#pragma once
#include "iostream"
#include "fstream"
#include "sstream"

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

	void ConfigurationManager::parse(string);
	RobotPosition ConfigurationManager::getRobotPositionFromString(string);
	RobotSize ConfigurationManager::getRobotSizeFromString(string);
	MapPoint ConfigurationManager::getMapPointFromString(string);

	string mapFileLocation;
	RobotPosition startPosition;
	MapPoint goal;
	RobotSize size;
	double mapResolutionInCm;
	double gridResolutionInCm;
};

