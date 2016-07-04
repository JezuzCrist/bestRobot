#pragma once
#include "Particle.h"


using namespace std;

#define PARTICLE_COUNT 50
#define PARTICLE_SPREAD 10
#define PARTICLE_KILL 20

class LocalizationManager
{
public:
	LocalizationManager(void);
	~LocalizationManager(void);
	void update(double changeX, double changeY, double changeYaw, Robot* robot);
	MapPosition3D getEstimatedPosition();


private:
	Particle* _particles[PARTICLE_COUNT];
	Particle _bestEstimatedPartical;
	void _init();
	void _sortParticalsByBelife();
	Particle* _getBestParticle();
};

