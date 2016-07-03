#include "stdafx.h"
#include "LocalizationManager.h"


LocalizationManager::LocalizationManager(void)
{
	this->_init();
}

void LocalizationManager::_init()
{
	double startingLocationX = 0, startingLocationY = 0,startingYaw = 0, ANGLES_NUM = 360;
	Particle* startingLocation = new Particle(startingLocationX,startingLocationY,startingYaw);

	for (int i = 0; i < PARTICLE_COUNT; i++)
	{
		for (int newParticalIndex = 0; i < PARTICLE_COUNT; newParticalIndex++)
		{
			this->_particles[i] = new Particle(startingLocation);
		}
	}
}

LocalizationManager::~LocalizationManager(void)
{
}
