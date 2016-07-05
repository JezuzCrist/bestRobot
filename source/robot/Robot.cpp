#include "Robot.h"
#include <libplayerc++/playerc++.h>

using namespace std;

Robot::Robot(char* ip, int port,WorldPosition3D* startingPosition,int width,int height)
{
	this->_playerClient = new PlayerCc::PlayerClient(ip,port);
	this->_playerPsition = new PlayerCc::Position2dProxy(this->_playerClient);
	this->_lasers = new PlayerCc::LaserProxy(this->_playerClient);

	this->_position = startingPosition;

	this->_height = height;
	this->_width = width;



	this->_playerPsition->SetOdometry(
		startingPosition->x,startingPosition->y,startingPosition->yaw);
	this->_playerPsition->SetMotorEnable(true);

}
int Robot::getWidth(){
	return this->_width;
}
int Robot::getHeight(){
	return this->_height;
}
void Robot::_setSpeed(float speed, float angularSpeed){
	this->_playerPsition->SetSpeed(speed,angularSpeed);
}
WorldPosition3D* Robot::getPosition(){
	return this->_position;
}
float Robot::getLaserDistance(int laserIndex){
	float laserValue = (*this->_lasers)[laserIndex];
	return laserValue;
}

Robot::~Robot(void)
{
}

void Robot::_setYaw(double wantedYaw){

}
bool isRobotTolaratedAtLocation(WorldPosition3D* robot, WorldPosition3D* wanted){
	bool isTolarated = false;
	double 	deltaX = robot->x - wanted->x,
			deltaY = robot->y - wanted->y;
	double distance = sqrt( pow(deltaX,2) + pow(deltaY ,2) );

	return isTolarated;
}
void Robot::goTo(WorldPosition3D* wantedPosition){

	while(isRobotTolaratedAtLocation(this->_position,wantedPosition) == false){
		// move robot to location
	}
}
