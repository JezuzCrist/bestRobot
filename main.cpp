// robot_nir_omer.cpp : Defines the entry point for the console application.
#include "source/map/Map.h"
#include "source/managers/pathPlanner/PathPlanner.h"
#include "source/managers/waypoint/WaypointsManager.h"
#include "source/robot/Robot.h"
#include "source/common/PositionConveter.h"
#include "source/logicVisualization/logicVisualization.h"
#include "source/managers/localization/LocalizationManager.h"

int main()
{
	ConfigurationManager configs = ConfigurationManager();
	configs.parse("parameters.txt");
	PositionConveter* _positionConverter = new PositionConveter(&configs);

	Map* map = new Map(configs.mapFileLocation,
					   configs.mapResolutionInCm,
					   configs.gridResolutionInCm,
					   configs.robotSize);

	PathPlanner* pathPlanner = new PathPlanner(map);
	WorldPosition3D startPosition = configs.startPosition;
	int resolutionRelation = (int)(configs.gridResolutionInCm /
								   configs.mapResolutionInCm);
	MapPosition2D* mapStartPosition = new MapPosition2D(configs.startPosition.x / resolutionRelation,
													    configs.startPosition.y / resolutionRelation);
	MapPosition2D* mapGoalPosition = _positionConverter->getMapPosition2D(&(configs.goal));

	//convert the positions to CELL   worldPosition -> Map pos
	vector<MapPosition2D*> pathToGoal = pathPlanner->getPath(*mapStartPosition, *mapGoalPosition);

	// create waypoint manager
	WaypointsManager* waypoints = new WaypointsManager(pathToGoal);

	Robot* robot = new Robot("localhost",6665,&(configs.startPosition),
			configs.robotSize->width,configs.robotSize->height, configs.mapResolutionInCm);

	LocalizationManager* localizationManager = new LocalizationManager(startPosition,robot,map);

	logicVisualization* logic = new logicVisualization(localizationManager,pathToGoal, map,
												       &configs, waypoints->getWaypoints(),
												       robot);
	logic->printToPicture();

	while(!waypoints->isRobotInEndGoal()){
		MapPosition2D* currentWaypoint = waypoints->getActiveWaypoint();
		WorldPosition3D* convertedPos = _positionConverter->getWorldPosition3DFrom2DMap(currentWaypoint);
		logic->writeRobotPosition();
		logic->printToPicture();
		sleep(0.5);
		robot->goTo( convertedPos );
		waypoints->nextWaypoint();
	}

	return 0;
}
