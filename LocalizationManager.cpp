#include "stdafx.h"
#include "LocalizationManager.h"


void _initRandom(){
	srand(time(NULL));
}

LocalizationManager::LocalizationManager(void)
{
	this->_init();
}

void LocalizationManager::_init()
{
	for (int i = 0; i < STARTING_PARTICLE_COUNT; i++)
	{
		_initRandom();

		double particleX =  (rand() % PARTICLE_SPREAD) / PARTICLE_SPREAD;
		double particleY = (rand() % PARTICLE_SPREAD) / PARTICLE_SPREAD;
		double particleYaw = (rand() % PARTICLE_SPREAD) / PARTICLE_SPREAD;

		Particle newParticle;
		newParticle.move(particleX,particleY,particleYaw);
		_particles.push_back(newParticle);
	}
}

LocalizationManager::~LocalizationManager(void)
{
}
