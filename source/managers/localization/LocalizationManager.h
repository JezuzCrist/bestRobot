#pragma once
#include "Particle.h"


using namespace std;

#define PARTICLE_COUNT 50
#define PARTICLE_SPREAD 10

class LocalizationManager
{
public:
	LocalizationManager(void);
	~LocalizationManager(void);
	void update(double changeX, double changeY, double changeYaw, Robot* robot);
	PositionD getEstimatedPosition();


private:
	Particle* _particles[PARTICLE_COUNT];
	Particle _bestEstimatedPartical;
	void _init();
};

