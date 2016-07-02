#include "stdafx.h"
#include "LocalizationManager.h"


LocalizationManager::LocalizationManager(void)
{
	int STARTING_PARTICLE_COUNT = 200;
	int PARTICLE_SPREAD = 20;
	for (int i = 0; i < STARTING_PARTICLE_COUNT; i++)
	{
		//initialize random seed
		srand(time(NULL));

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
