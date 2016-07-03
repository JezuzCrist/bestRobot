#pragma once
#include "Particle.h"
#include "Position.h"
#include <list>
#include <ctime>
using namespace std;

#define STARTING_PARTICLE_COUNT 50
#define PARTICLE_SPREAD 10

class LocalizationManager
{
public:
	LocalizationManager(void);
	~LocalizationManager(void);
	void update();
	Position getEstimatedPosition();


private:
	list<Particle> _particles;
	Particle _bestEstimatedPartical;
	void _init();
};

