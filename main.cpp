// robot_nir_omer.cpp : Defines the entry point for the console application.
#include "source/map/Map.h"
#include "source/managers/pathPlanner/PathPlanner.h"


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

	ConfigurationManager paramParser = ConfigurationManager();
	paramParser.parse("parameters.txt");
	Map* map = new Map(paramParser.mapFileLocation,
					   paramParser.mapResolutionInCm,
					   paramParser.gridResolutionInCm,
					   paramParser.robotSize);
	cout << "sds"<< endl;
	PathPlanner* pathPlanner = new PathPlanner(map);
	MapPosition2D goal, startPosition;
	goal.x = 20;
	goal.y = 0;
	startPosition.x = 0;
	startPosition.y = 0;
	cout << "ds"<< endl;
	vector<MapPosition2D*> pathToGoal = pathPlanner->getPath(startPosition,goal);
	cout << "HUE" << endl;
	return 0;
}
