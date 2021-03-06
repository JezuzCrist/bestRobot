#pragma once
#include <libplayerc++/playerc++.h>
#include "../common/Position.h"



#define NUMBER_OF_LASERS 6
#define YAW_ABOVE 90
#define YAW_BELOW 270
#define YAW_RIGHT 0
#define YAW_LEFT 180

class Robot
{
public:
	Robot(char* ip, int port,WorldPosition3D* startingPosition,int width,int height, double mapResolutionCm);
	~Robot(void);
	WorldPosition3D* getPosition();
	float getLaserDistance(int laserIndex);
	int getWidth();
	int getHeight();
	double getMapResolution();
	void goTo(WorldPosition3D* wantedPosition);

private:
	const double static angleTolerance = 3;
	const double static distanceTolerance = 2;

	const float static forwardSpeed = 0.2;
	const float static angularSpeed = 0.5;

	WorldPosition3D* _position;
	int _width,_height;
	double mapResolutionCm;
	PlayerCc::PlayerClient* _playerClient;
	PlayerCc::Position2dProxy* _playerPsition;
	PlayerCc::LaserProxy* _lasers;
	void _updatePosition();
	void _stop();
	void _moveForward(float speed);
	void _spin(float speed);
	void _setSpeed(float speed, float angularSpeed);
	void _setYaw(WorldPosition3D* wantedPosition);

	bool _isAngleTolarated(WorldPosition3D* robot, WorldPosition3D* wanted);
	bool _isDistanceTolarated(WorldPosition3D* robot, WorldPosition3D* wanted);
	bool _isRobotTolaratedAtLocation(WorldPosition3D* robot, WorldPosition3D* wanted);

	void _setYawToTarget(WorldPosition3D* wantedPosition);
};
