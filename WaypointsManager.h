#pragma once
#include "Cell.h"
#include <vector>
#include <math.h>

using namespace std;

class WaypointsManager
{
public:
	WaypointsManager(vector<Position*> robotPath);
	~WaypointsManager(void);

	void update(Position* currentPosition);
	bool isRobotInEndGoal();
	Position* getActiveWaypoint();

private:
	const int static distanceThreshold = 10;
	const int static numberOfCellsToSkipInPath = 5;

	vector<Position*> _robotPath;
	vector<Position*> _wayPoints;
	unsigned wayPointIndex;
	bool _isRobotInWayPoint(Position* currentPosition);
	void _setNextWayPoint();
	void _buildWayPoints();
};

