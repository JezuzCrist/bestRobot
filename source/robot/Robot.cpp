#include "Robot.h"
#include <libplayerc++/playerc++.h>

using namespace std;

Robot::Robot(char* ip, int port,WorldPosition3D* startingPosition,int width,int height, double mapResolutionCm)
{
	this->_playerClient = new PlayerCc::PlayerClient(ip,port);
	this->_playerPsition = new PlayerCc::Position2dProxy(this->_playerClient);
	this->_lasers = new PlayerCc::LaserProxy(this->_playerClient);

	this->_position = startingPosition;

	this->_height = height;
	this->_width = width;
	this->mapResolutionCm = mapResolutionCm;

	for(int i = 0; i < 15; i++)
	{
		_playerClient->Read();
	}

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
double distanceBetweenPositions(WorldPosition3D* p1, WorldPosition3D* p2){
	double 	deltaX = p1->x - p2->x,
			deltaY = p1->y - p2->y;
	double distance = sqrt( pow(deltaX,2) + pow(deltaY ,2) );
	return distance;
}
bool Robot::_isDistanceTolarated(WorldPosition3D* robot, WorldPosition3D* wanted){
	double distance = distanceBetweenPositions(robot,wanted);
	bool isTolarated = ( distance < this->distanceTolerance );
	return isTolarated;
}
bool Robot::_isAngleTolarated(WorldPosition3D* robot, WorldPosition3D* wanted){
	double deltaYaw = abs( robot->yaw - wanted->yaw );
	bool isTolarated = ( deltaYaw < this->angleTolerance );
	return isTolarated;
}
bool Robot::_isRobotTolaratedAtLocation(WorldPosition3D* robot, WorldPosition3D* wanted){
	if(this->_isAngleTolarated(robot, wanted) == false)
		return false;
	if(this->_isDistanceTolarated(robot, wanted) == false)
		return false;
	return true;
}
void Robot::_stop(){
	this->_setSpeed(0,0);
}
void Robot::_moveForward(float speed){
	this->_setSpeed(speed,0);
}
void Robot::_spin(float angularSpeed){
	this->_setSpeed(0,angularSpeed);
}
void Robot::_setYaw(WorldPosition3D* wantedPosition){
	while(this->_isAngleTolarated(this->_position,wantedPosition) == false ){
		this->_updatePosition();
		this->_spin(this->angularSpeed);
	}
	this->_stop();
}
void Robot::_updatePosition(){
	this->_playerClient->Read();
	this->_position->x = this->_playerPsition->GetXPos()*(100/this->mapResolutionCm);
	this->_position->y = this->_playerPsition->GetYPos()*(100/this->mapResolutionCm);
	this->_position->yaw = PlayerCc::rtod(this->_playerPsition->GetYaw());
	if(this->_position->yaw < 0){
		cout<<"before"<<this->_position->yaw<<endl;
		cout<<"*-1  "<<this->_position->yaw*-1<<endl;
		this->_position->yaw = this->_position->yaw*-1 + 180.0;
	}
	cout << "robot Pos : x:" << this->_position->x<<", y "<<this->_position->y<<",x yaw "<<this->_position->yaw<<endl;

}
void Robot::_setYawToTarget(WorldPosition3D* wantedPosition){
	bool targetAbove = wantedPosition->y > this->_position->y,
		targetBelow = wantedPosition->y < this->_position->y,
		targetRight = wantedPosition->x > this->_position->x,
		targetLeft = wantedPosition->x < this->_position->x;

	if(!targetLeft && !targetRight){
		if(targetAbove)
			wantedPosition->yaw = YAW_ABOVE;
		else { wantedPosition->yaw = YAW_BELOW; }
	}

	if(!targetAbove && !targetBelow){
		if(targetLeft)
			wantedPosition->yaw = YAW_LEFT;
		else { wantedPosition->yaw = YAW_RIGHT; }
	}

	double 	deltaX = this->_position->x - wantedPosition->x,
			deltaY = this->_position->y - wantedPosition->y;

	double hypotinus = distanceBetweenPositions(this->_position, wantedPosition);
	if( targetAbove && targetRight ){
		double angle = asin(deltaY/hypotinus);
		wantedPosition->yaw = angle + YAW_ABOVE + (90 - angle);
	}
	if( targetAbove && targetLeft ){
		double angle = asin(deltaY/hypotinus);
		wantedPosition->yaw = angle;
	}
	if( targetBelow && targetRight ){
		double angle = asin(deltaX/hypotinus);
		wantedPosition->yaw = angle + YAW_RIGHT + (90 - angle);
	}
	if( targetBelow && targetLeft ){
		double angle = asin(deltaX/hypotinus);
		wantedPosition->yaw = angle + YAW_BELOW;
	}
	cout << "wantedYaw" << wantedPosition->yaw <<endl;
	this->_setYaw(wantedPosition);
}

void Robot::goTo(WorldPosition3D* wantedPosition){
	cout << "start goto"<<endl;
	while(this->_isRobotTolaratedAtLocation(this->_position,wantedPosition) == false)
	{
		cout << "while goto wanted:x:"<<wantedPosition->x<<"y:"<<wantedPosition->y<<endl;
		// move robot to location

		this->_setYawToTarget(wantedPosition);
		this->_moveForward(this->forwardSpeed);
		this->_updatePosition();
	}
	this->_stop();
}

Robot::~Robot(void)
{
}
