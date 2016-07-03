#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>    // std::max

#include "PositionD.h"
#include "Robot.h"

using namespace std;

#define LOCATION_RANDOMNESS 10

#define MAX_PROB_DISTANCE 2
#define MAX_PROB_YAW 150
#define MAX_OBS_DISTANCE 5
#define COEFFICIENT 1.5

class Particle
{
public:
	Particle(void);
	Particle(double x, double y, double yaw);
	Particle(Particle* mutateFromThisPartical);
	~Particle(void);

	void update(double changeX, double changeY, double changeYaw, Robot* robot);
	void move(double changeX, double changeY, double changeYaw);
	void mutateFromRefrance(Particle* partical);
	double probMov(double deltaX, double deltaY, double deltaTeta);

	double getBelief();
	PositionD getPosition(); 

private:
	double _belief,acurecyPrediction;
	PositionD position; 


	void _cloneFrom(PositionD position);
	void _randomizeLocation();
	double _getParticleObservationsProbablity(Robot* robot);
	void _updateLocationEstimation();
};

