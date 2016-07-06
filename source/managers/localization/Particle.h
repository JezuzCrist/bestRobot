#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>    // std::max
#include "math.h"

#include "../../common/Position.h"
#include "../../robot/Robot.h"

using namespace std;

#define MAX_PROB_DISTANCE 2
#define MAX_PROB_YAW 150
#define MAX_OBS_DISTANCE 5
#define COEFFICIENT 1.5

class Particle
{
public:
	Particle(void);
	Particle(double x, double y, double yaw);
	Particle(Particle* mutateFromThisPartical,int LOCATION_RANDOMNESS);
	~Particle(void);

	void update(double changeX, double changeY, double changeYaw, Robot* robot);
	void move(double changeX, double changeY, double changeYaw);
	void mutateFromRefrance(Particle* partical,int LOCATION_RANDOMNESS);
	double probMov(double deltaX, double deltaY, double deltaTeta);

	double getBelief();
	WorldPosition3D* getPosition();

private:
	double _belief,acurecyPrediction;
	WorldPosition3D* position;


	void _cloneFrom(WorldPosition3D* position);
	void _randomizeLocation(int LOCATION_RANDOMNESS);
	double _getParticleObservationsProbablity(Robot* robot);
	void _updateLocationEstimation();
};

