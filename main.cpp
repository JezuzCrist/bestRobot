// robot_nir_omer.cpp : Defines the entry point for the console application.
#include "source/map/Map.h"
#include "source/managers/pathPlanner/PathPlanner.h"
#include "source/managers/waypoint/WaypointsManager.h"
#include "source/robot/Robot.h"
#include "source/common/PositionConveter.h"

int main()
{
	/*
	ConfigurationManager p = ConfigurationManager();
	p.parse("parameters.txt");

	cout << p.mapFileLocation<< endl;
	cout << p.startPosition.x<<","<<p.startPosition.y<<","<<p.startPosition.yaw<< endl;
	cout<<p.goal.x<<","<<p.goal.y<<endl;
	cout<<p.robotSize->width<<","<<p.robotSize->height<<endl;
	cout<<p.mapResolutionInCm<<endl;
	cout<<p.gridResolutionInCm<<endl;
	cout<<"compiling and building is working in linux !"<<endl;
	*/

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

	Robot* robot = new Robot("localhost",6665,&(configs.startPosition),
			configs.robotSize->width,configs.robotSize->height, configs.mapResolutionInCm);
	cout << "Robot Created" << endl;
	while(!waypoints->isRobotInEndGoal()){
		MapPosition2D* currentWaypoint = waypoints->getActiveWaypoint();

		robot->goTo( _positionConverter->getWorldPosition3D(currentWaypoint) );
		waypoints->nextWaypoint();
	}
	cout << "Done waypoints: " << endl;
	return 0;
}
