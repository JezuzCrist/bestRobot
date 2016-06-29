#include "stdafx.h"
#include "WaypointsManager.h"




WaypointsManager::WaypointsManager(vector<Position*> robotPath)
{
	this->_robotPath = robotPath;
	this->wayPointIndex = 0;
}
bool WaypointsManager::_isRobotInWayPoint(Position* currentPosition){
	Position* activeWaypoint = this->getActiveWaypoint();
	
	double distanceFromWaypoint = sqrt( pow( activeWaypoint->x - currentPosition->x, 2) + pow(activeWaypoint->y - currentPosition->y , 2));
	bool isOnWayPoint = (distanceFromWaypoint <= this->distanceThreshold);

	return isOnWayPoint;
}
void WaypointsManager::update(Position* currentRobotPos)
{
	if(this->_isRobotInWayPoint(currentRobotPos)){
		this->_setNextWayPoint();
	}
}
void WaypointsManager::_buildWayPoints(){
	for (int i = 0; i < this->_robotPath.size(); i+= this->numberOfCellsToSkipInPath)
	{
		this->_wayPoints.push_back(this->_robotPath[i]);
	}
	int lastWaypointIndex = this->_robotPath.size()-1;
	this->_wayPoints.push_back(this->_robotPath[lastWaypointIndex]);
}
void WaypointsManager::_setNextWayPoint(){
	this->wayPointIndex++;
}
bool WaypointsManager::isRobotInEndGoal(){
	return (this->_wayPoints.size() < this->wayPointIndex);
}
Position* WaypointsManager::getActiveWaypoint(){
	return (this->_wayPoints[this->wayPointIndex]);
}
WaypointsManager::~WaypointsManager(void)
{
}
