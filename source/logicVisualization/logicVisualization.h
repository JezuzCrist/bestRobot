
#ifndef LOGICVISUALIZATION_H_
#define LOGICVISUALIZATION_H_
#include "../common/Position.h"
#include "../common/PositionConveter.h"
#include "../map/Map.h"
#include "../managers/localization/LocalizationManager.h"
#include "../managers/localization/Particle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../robot/Robot.h"

#define robotPositionsFileName "robot_positions.json"

class logicVisualization {
public:
	logicVisualization(LocalizationManager* _localizationManager,
					   vector<MapPosition2D*> pathToGoal, Map* map,
		               ConfigurationManager* configurationManager,
		               vector<MapPosition2D*> waypoints, Robot* robot);
	void printToPicture();
	void writeRobotPosition();
	virtual ~logicVisualization();

private:
	void _printObsticalsAndMap(PositionConveter* positionConverter, Map* map,
	 vector<unsigned char>* image,ImageSize* imgSize);
	void _printPath(PositionConveter* positionConverter,vector<MapPosition2D*> pathToGoal,
			vector<unsigned char>* image,ImageSize* imgSize);
	void _printWayPoints(PositionConveter* positionConverter,vector<MapPosition2D*> waypoints,
			vector<unsigned char>* image,ImageSize* imgSize);
	void particals( vector<unsigned char>* image,ImageSize* imgSize);
	LocalizationManager* _localizationManager;
	vector<MapPosition2D*> _pathToGoal;
	Map* _map;
    ConfigurationManager* _configurationManager;
	vector<MapPosition2D*> _waypoints;
	ofstream robotPositionFile;
	Robot* robot;
};

#endif /* LOGICVISUALIZATION_H_ */
