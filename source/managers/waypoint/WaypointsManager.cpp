#include "WaypointsManager.h"


WaypointsManager::WaypointsManager(vector<MapPosition2D*> robotPath)
{
	this->_robotPath = robotPath;
	this-> wayPointIndex = 0;
	this->_buildWayPoints();
}

bool WaypointsManager::_isRobotInWayPoint(MapPosition2D* currentPosition)
{
	MapPosition2D* activeWaypoint = this->getActiveWaypoint();

	double distanceFromWaypoint =
				sqrt( pow(activeWaypoint->x - currentPosition->x, 2) +
					  pow(activeWaypoint->y - currentPosition->y , 2));
	bool isOnWayPoint = (distanceFromWaypoint <= this->distanceThreshold);

	return isOnWayPoint;
}

void WaypointsManager::nextWaypoint()
{
	this->_setNextWayPoint();
}

void WaypointsManager::_buildWayPoints()
{
	for (int i = 0; i < this->_robotPath.size(); i += this->numberOfCellsToSkipInPath)
	{
		this->_wayPoints.push_back(this->_robotPath[i]);
	}
	int lastWaypointIndex = this->_robotPath.size() - 1;
	this->_wayPoints.push_back(this->_robotPath[lastWaypointIndex]);
}

void WaypointsManager::_setNextWayPoint()
{
	this->wayPointIndex++;
}

bool WaypointsManager::isRobotInEndGoal()
{
	return (this->_wayPoints.size() < this->wayPointIndex);
}

MapPosition2D* WaypointsManager::getActiveWaypoint()
{
	return (this->_wayPoints[this->wayPointIndex]);
}

vector<MapPosition2D*> WaypointsManager::getWaypoints(){
	return this->_wayPoints;
}

WaypointsManager::~WaypointsManager(void)
{
}
