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
bool isParticalBelifeHigher(Particle* p1, Particle* p2){
	return (p1->getBelief() < p2->getBelief());
}
void LocalizationManager::_sortParticalsByBelife(){
	sort(this->_particles, this->_particles + PARTICLE_COUNT,isParticalBelifeHigher);
}
Particle* LocalizationManager::_getBestParticle(){
	return this->_particles[PARTICLE_COUNT - 1];
}
void LocalizationManager::update(double changeX, double changeY, double changeYaw, Robot* robot){
	// update the particals
	for(int particalIndex = 0; particalIndex < PARTICLE_COUNT; particalIndex++){
		//this->_particles[particalIndex]->update(changeX,changeY,changeYaw,robot);
	}

	//sort the particals
	this->_sortParticalsByBelife();

	for (int newParticalIndex = 0; newParticalIndex < PARTICLE_KILL; ++newParticalIndex)
	{
		this->_particles[newParticalIndex]->mutateFromRefrance(this->_getBestParticle());
	}


}
LocalizationManager::~LocalizationManager(void)
{
}
