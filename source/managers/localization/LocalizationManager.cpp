#include "LocalizationManager.h"


LocalizationManager::LocalizationManager(WorldPosition3D startingPoint,Robot* robot,Map* map)
{
	cout<<"ctor LocalizationManager"<<endl;
	this->_robot = robot;
	this->_map = map;
	this->_init(startingPoint);
}

void LocalizationManager::_init(WorldPosition3D startingPoint)
{
	this->_particles.resize(this->ParticalCount);
	Particle* startingLocation = new Particle(startingPoint.x,startingPoint.y,startingPoint.yaw);

	for (int newParticalIndex = 0; newParticalIndex < this->ParticalCount; newParticalIndex++)
	{
		this->_particles[newParticalIndex] = new Particle(startingLocation,this->ParticalFirstSpread,this->_robot,this->_map);
		cout << this->_particles[newParticalIndex]->getBelief() << endl;
	}

}
LocalizationManager::~LocalizationManager(void)
{
}
vector<Particle*> LocalizationManager::getParticals(){
	return this->_particles;
}


bool isParticalBelifeHigher(Particle* p1, Particle* p2){
	return (p1->getBelief() < p2->getBelief());
}
void LocalizationManager::_sortParticalsByBelife(){
	//sort(this->_particles, this->_particles + this->ParticalCount,isParticalBelifeHigher);
}
Particle* LocalizationManager::_getBestParticle(){
	return this->_particles[this->ParticalCount - 1];
}
void LocalizationManager::update(double changeX, double changeY, double changeYaw, Robot* robot){
	// update the particals
	for(int particalIndex = 0; particalIndex < this->ParticalCount; particalIndex++){
		// this->_particles[particalIndex]->move(changeX,changeY,changeYaw,robot);
		this->_particles[particalIndex]->update(changeX,changeY,changeYaw,robot,this->_map);
	}

	//sort the particals
	this->_sortParticalsByBelife();

	for (int newParticalIndex = 0; newParticalIndex < this->ParticalsToRenew; ++newParticalIndex)
	{
		this->_particles[newParticalIndex]->mutateFromRefrance(this->_getBestParticle(),this->ParticalSpread,this->_robot,this->_map);
	}


}
