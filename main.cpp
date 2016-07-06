// robot_nir_omer.cpp : Defines the entry point for the console application.
#include "source/map/Map.h"
#include "source/managers/pathPlanner/PathPlanner.h"
#include "source/managers/waypoint/WaypointsManager.h"
#include "source/robot/Robot.h"
#include "source/common/PositionConveter.h"
#include "source/logicVisualization/logicVisualization.h"

int main()
{
	ConfigurationManager configs = ConfigurationManager();
	cout << "Cpnfig Created"<< endl;
	configs.parse("parameters.txt");
	PositionConveter* _positionConverter = new PositionConveter(&configs);
	cout << "PositionConveter Created" << endl;
	cout << "Config Loaded"<< endl;
	cout << configs.mapFileLocation << endl;
	Map* map = new Map(configs.mapFileLocation,
					   configs.mapResolutionInCm,
					   configs.gridResolutionInCm,
					   configs.robotSize);
	cout << "Map Created"<< endl;
	PathPlanner* pathPlanner = new PathPlanner(map);
	WorldPosition3D startPosition = configs.startPosition;
	int resolutionRelation = (int)(configs.gridResolutionInCm /
								   configs.mapResolutionInCm);
	MapPosition2D* mapStartPosition = new MapPosition2D(configs.startPosition.x / resolutionRelation,
													    configs.startPosition.y / resolutionRelation);
	MapPosition2D* mapGoalPosition = _positionConverter->getMapPosition2D(&(configs.goal));
	cout << "convert positions"<<endl;
	//convert the positions to CELL   worldPO -> MAp pos
	vector<MapPosition2D*> pathToGoal = pathPlanner->getPath(*mapStartPosition, *mapGoalPosition);


	cout << "path created" << endl;
	// create waypoint manager
	WaypointsManager* waypoints = new WaypointsManager(pathToGoal);
	cout << "WapointManager Created" << endl;

	logicVisualization* logic = new logicVisualization();
	logic->printToPicture(pathToGoal, map, &configs, waypoints->getWaypoints());

	Robot* robot = new Robot("localhost",6665,&(configs.startPosition),
			configs.robotSize->width,configs.robotSize->height, configs.mapResolutionInCm);
	cout << "Robot Created" << endl;
	while(!waypoints->isRobotInEndGoal()){
		MapPosition2D* currentWaypoint = waypoints->getActiveWaypoint();
		cout<<" ======================== next waypoint x:"<< currentWaypoint->x<< "  y:"<< currentWaypoint->y<<endl;
		WorldPosition3D* convertedPos = _positionConverter->getWorldPosition3DFrom2DMap(currentWaypoint);
		cout<<"converted waypoint x:"<< convertedPos->x<< "  y:"<< convertedPos->y<<endl;
		sleep(0.5);
		robot->goTo( convertedPos );
		waypoints->nextWaypoint();
	}
	cout << "Done waypoints: " << endl;
	return 0;
}
