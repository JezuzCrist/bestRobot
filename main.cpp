// robot_nir_omer.cpp : Defines the entry point for the console application.
#include "source/map/Map.h"
#include "source/managers/pathPlanner/PathPlanner.h"
#include "source/managers/waypoint/WaypointsManager.h"
#include "source/robot/Robot.h"
#include "source/common/PositionConveter.h"

void printToPicture(vector<MapPosition2D*> pathToGoal, Map* map,
		            ConfigurationManager* configurationManager);

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

	printToPicture(pathToGoal, map, &configs);

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

void printToPicture(vector<MapPosition2D*> pathToGoal, Map* map,
		            ConfigurationManager* configurationManager)
{
	WorldPosition2D* worldPosition;
	PositionConveter* positionConverter = new PositionConveter(configurationManager);

	int resolutionRelation = (int)(configurationManager->gridResolutionInCm /
								   configurationManager->mapResolutionInCm);

	ImageSize* imgSize = map->getImgSize();
	vector<unsigned char> image = map->getImage();
	Cell*** grid = map->getMap();
	ImageSize* mapSize = map->getMapSize();

	for (int row=0; row < mapSize->height; row++)
	{
		for (int col=0; col<mapSize->width; col++)
		{
			int x = grid[row][col]->x;
			int y = grid[row][col]->y;
			cout << "row " << row << " col " << col << endl;
			cout << "X: " << x << " Y: " <<y<< endl;
			MapPosition2D* mapPosition = new MapPosition2D(x, y);
			cout << "before "<< mapPosition->y <<endl;
			worldPosition = positionConverter->getWorldPosition2D(mapPosition);
			cout << "after "<< worldPosition->y <<endl;
			int imgRow = worldPosition->y;
			int imgCol = worldPosition->x;
			int color;
			if (grid[row][col]->walkable)
			{
				color = 255;
			}
			else
			{
				color = 0;
			}
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 0] = color;
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 1] = 255;
			image[imgRow * imgSize->width * 4 + imgCol * 4 + 2] = 255;
		}
	}
	vector<MapPosition2D*>::iterator i;
	for (i = pathToGoal.begin(); i != pathToGoal.end(); ++ i)
	{
		worldPosition = positionConverter->getWorldPosition2D((*i));
		int imgRow = worldPosition->y;
		int imgCol = worldPosition->x;
		image[imgRow * imgSize->width * 4 + imgCol * 4 + 0] = 255;
		image[imgRow * imgSize->width * 4 + imgCol * 4 + 1] = 0;
		image[imgRow * imgSize->width * 4 + imgCol * 4 + 2] = 0;
	}

	unsigned height = (unsigned)imgSize->height, width = (unsigned)imgSize->width;
	encodeOneStep("/home/user/Desktop/afterAstar1.png", image, width, height);
}
