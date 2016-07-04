#pragma once
#include <libplayerc++/playerc++.h>
#include "../common/PositionD.h"
using namespace std;
using namespace PlayerCc;


#define NUMBER_OF_LASERS 6

class Robot
{
public:
	Robot(char* ip, int port,PositionD* startingPosition,int width,int height);
	~Robot(void);
	PositionD* getPosition();
	float getLaserDistance(int index);
	int getWidth();
	int getHeight();
	void goTo(PositionD* wantedPosition);

private:
	PositionD _position;
	int _width,_height;
	PlayerClient* _playerClient;
	Position2dProxy* _playerPsition;
	LaserProxy* _lasers;
	void _updatePosition();

};
