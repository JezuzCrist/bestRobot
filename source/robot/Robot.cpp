#include "Robot.h"
using namespace std;
using namespace PlayerCc;

Robot::Robot(char* ip, int port,WorldPosition3D* startingPosition,int width,int height)
{
	this->_playerClient = new PlayerCc::PlayerClient(ip,port);
	this->_playerPsition = new PlayerCc::Position2dProxy(this->_playerClient);
	this->_lasers = new LaserProxy(this->_playerClient);

	this->_playerPsition->SetMotorEnable(true);
	this->_playerPsition->SetOdometry(
		startingPosition->x,startingPosition->y,startingPosition->yaw);

}

void Robot::_setSpeed(float speed, float angularSpeed){
	this->_playerPsition->SetSpeed(speed,angularSpeed);
}

Robot::~Robot(void)
{
}
