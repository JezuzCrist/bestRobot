#pragma once
#include "../../common/Position.h"
#include <vector>
#include <math.h>

using namespace std;

class WaypointsManager
{
public:
	WaypointsManager(vector<MapPosition2D*> robotPath);
	~WaypointsManager(void);

	void nextWaypoint();
	bool isRobotInEndGoal();
	MapPosition2D* getActiveWaypoint();

private:
	const int static distanceThreshold = 10;
	const int static numberOfCellsToSkipInPath = 2;

	vector<MapPosition2D*> _robotPath;
	vector<MapPosition2D*> _wayPoints;
	unsigned wayPointIndex;
	bool _isRobotInWayPoint(MapPosition2D* currentPosition);
	void _setNextWayPoint();
	void _buildWayPoints();
};

