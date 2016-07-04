#pragma once
#include <libplayerc++/playerc++.h>
#include <string.h>
#include "../common/Position.h"



#define NUMBER_OF_LASERS 6

class Robot
{
public:
	Robot(char* ip, int port,WorldPosition3D* startingPosition,int width,int height);
	~Robot(void);
	WorldPosition3D* getPosition();
	float getLaserDistance(int index);
	int getWidth();
	int getHeight();
	void goTo(WorldPosition3D* wantedPosition);

private:
	WorldPosition3D* _position;
	int _width,_height;
	PlayerCc::PlayerClient* _playerClient;
	PlayerCc::Position2dProxy* _playerPsition;
	PlayerCc::LaserProxy* _lasers;
	void _updatePosition();
	void _setSpeed(float speed, float angularSpeed);

};
