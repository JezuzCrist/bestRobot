#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager(void)
{
}

WorldPosition2D ConfigurationManager::getMapPointFromString(string mapPointString)
{
	WorldPosition2D returnPoint;
	string strX = "", strY = "";
	unsigned index = 0;
	char spaceIndecator = ' ';
	while (index < mapPointString.length() &&
		   mapPointString[index] != spaceIndecator)
	{
		strX += mapPointString[index];
		index++;
	}
	index++;
	returnPoint.x = atoi(strX.c_str());
	while (index < mapPointString.length() &&
		   mapPointString[index] != spaceIndecator)
	{
		strY += mapPointString[index];
		index++;
	}
	returnPoint.y = atoi(strY.c_str());
	return returnPoint;
}

RobotSize* ConfigurationManager::getRobotSizeFromString(string robotSizeString)
{
	RobotSize* returnRobotSize = new RobotSize();
	string strW = "", strH = "";
	unsigned index = 0;
	char spaceIndecator = ' ';
	while (index < robotSizeString.length() &&
		   robotSizeString[index] != spaceIndecator)
	{
		strW += robotSizeString[index];
		index++;
	}
	index++;
	returnRobotSize->width = atoi(strW.c_str());
	while (index < robotSizeString.length() &&
		   robotSizeString[index] != spaceIndecator) {
		strH += robotSizeString[index];
		index++;
	}
	returnRobotSize->height = atoi(strH.c_str());
	return returnRobotSize;
}

WorldPosition3D ConfigurationManager::getRobotPositionFromString(string robotPosString)
{
	WorldPosition3D returnRobotPosition;
	string mapPointStr = "",angleStr="";
	unsigned index = 0;
	char spaceIndecator = ' ';
	for(;index < robotPosString.length() &&
		robotPosString[index] != spaceIndecator; index++){
		mapPointStr += robotPosString[index];
	}
	mapPointStr += robotPosString[index++];
	for(;index < robotPosString.length() &&
		robotPosString[index] != spaceIndecator; index++){
		mapPointStr += robotPosString[index];
	}
	index++;
	for(;index < robotPosString.length() &&
		robotPosString[index] != spaceIndecator; index++){
		angleStr += robotPosString[index];
	}

	WorldPosition2D worldPosition = getMapPointFromString(mapPointStr);
	returnRobotPosition = WorldPosition3D(worldPosition, atof(angleStr.c_str()));
	return returnRobotPosition;
}

void ConfigurationManager::parse(string fileLocation)
{
	string mapLocation = "", startLocation = "", goal = "", MapResolutionCM = "",
		   GridResolutionCM = "", robotSize = "";
	ifstream infile;
	string line;
	const char* fileLocationInChar = fileLocation.c_str();
	infile.open(fileLocationInChar);

	getline(infile,line);
	for(unsigned index = 5; index < line.length(); index++){
		mapLocation += line[index];
	}
	getline(infile,line);
	for(unsigned index = 15; index < line.length(); index++){
		startLocation += line[index];
	}
	getline(infile,line);
	for(unsigned index = 6; index < line.length(); index++){
		goal += line[index];
	}
	getline(infile,line);
	for(unsigned index = 11; index < line.length(); index++){
		robotSize += line[index];
	}
	getline(infile,line);
	for(unsigned index = 17; index < line.length(); index++){
		MapResolutionCM += line[index];
	}
	getline(infile,line);
	for(unsigned index = 18; index < line.length(); index++){
		GridResolutionCM += line[index];
	}

	// make sure we close the file and clean up the buffer when we're
	// finished
	infile.close();

	this-> goal = getMapPointFromString(goal);
	this-> mapResolutionInCm = atof(MapResolutionCM.c_str());
	this-> gridResolutionInCm = atof(GridResolutionCM.c_str());
	this-> startPosition = getRobotPositionFromString(startLocation);
	this-> mapFileLocation = mapLocation;
	this-> robotSize = getRobotSizeFromString(robotSize);
}

ConfigurationManager::~ConfigurationManager(void)
{
}
