#pragma once
#include <libplayerc++/playerc++.h>
#include<string.h>
#include <iostream>
#include<stdlib.h>
#include "../common/Position.h"



#define NUMBER_OF_LASERS 6

class Robot
{
public:
	Robot(char* ip, int port,WorldPosition3D* startingPosition,int width,int height);
	~Robot(void);
	WorldPosition3D* getPosition();
	float getLaserDistance(int laserIndex);
	int getWidth();
	int getHeight();
	void goTo(WorldPosition3D* wantedPosition);

private:
	const double static angleTolerance = 1;
	const double static distanceTolerance = 5;

	WorldPosition3D* _position;
	int _width,_height;
	PlayerCc::PlayerClient* _playerClient;
	PlayerCc::Position2dProxy* _playerPsition;
	PlayerCc::LaserProxy* _lasers;
	void _updatePosition();
	void _setSpeed(float speed, float angularSpeed);
	void _setYaw(double wantedYaw);
};
