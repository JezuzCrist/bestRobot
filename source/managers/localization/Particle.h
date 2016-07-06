#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>    // std::max
#include "math.h"

#include "../../common/Position.h"
#include "../../robot/Robot.h"
#include "../../map/Map.h"
using namespace std;

#define MAX_PROB_DISTANCE 2
#define MAX_PROB_YAW 150
#define MAX_OBS_DISTANCE 5
#define COEFFICIENT 1.5

#define MIN_OBSTICAL_DISTANCE 10.0
#define MAX_LASER_ANGEL 230
#define SKIP_LASER_ANGLE 40
#define LASER_SENSOR_SEPERATION 0.36
#define LASER_SENSOR_CENTER 120.0

class Particle
{
public:
	Particle(void);
	Particle(double x, double y, double yaw);
	Particle(Particle* mutateFromThisPartical,int LOCATION_RANDOMNESS,Robot* robot,Map* map);
	~Particle(void);

	void update(double changeX, double changeY, double changeYaw, Robot* robot,Map* map);
	void move(double changeX, double changeY, double changeYaw);
	void mutateFromRefrance(Particle* partical,int LOCATION_RANDOMNESS,Robot* robot,Map* map);
	double probMov(double deltaX, double deltaY, double deltaTeta);

	double getBelief();
	WorldPosition3D* getPosition();

private:
	double _belief,acurecyPrediction;
	WorldPosition3D* position;

	Robot* _robot;
	WorldPosition3D* _lastRobotPosition;
	void _cloneFrom(WorldPosition3D* position);
	void _randomizeLocation(int LOCATION_RANDOMNESS);
	double _getParticleObservationsProbablity(Robot* robot, Map* map);
	void _updateLocationEstimation(Robot* robot,Map* map);
};

