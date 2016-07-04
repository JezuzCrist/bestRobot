#include "Particle.h"
using namespace std;

void _initRandom(){
	srand(time(NULL));
}

Particle::Particle(void)
{
}
Particle::Particle(double x, double y, double yaw)
{
	this->position.x = x;
	this->position.y = y;
	this->position.yaw = yaw;
}
Particle::Particle(Particle* mutateFromThisPartical)
{
	this->mutateFromRefrance(mutateFromThisPartical);
}

double Particle::getBelief(){	return this->_belief;	}
PositionD Particle::getPosition(){	return this->position;	}


void Particle::move(double changeX, double changeY, double changeYaw)
{
	this->position.x += changeX;
	this->position.y += changeY;
	this->position.yaw += changeYaw;
}
void Particle::_cloneFrom(PositionD clonePosition){
	this->position.x = clonePosition.x;
	this->position.y = clonePosition.y;
	this->position.yaw = clonePosition.yaw;
}
void Particle::_randomizeLocation(){
	_initRandom();
	this->position.x = std::max(0.0, this->position.x + (rand() % LOCATION_RANDOMNESS));
	this->position.y = std::max(0.0, this->position.y + (rand() % LOCATION_RANDOMNESS));
	this->position.yaw = std::max(0.0, this->position.yaw + (rand() % LOCATION_RANDOMNESS));
}
double Particle::_getParticleObservationsProbablity(Robot* robot){
	unsigned hits = 0, misses = 0;

	for(int laserIndex = 0 ; laserIndex < NUMBER_OF_LASERS; laserIndex++){
		double distanceFromObsticel = 0;// = robot->getLaserDistance(i);
		double currentAngle = 0; //((i * (0.36) - 120.0) / 180.0) * M_PI;
		double yawInRad = 0; //= _yaw/180.0 * M_PI;

		// Calculating diffrence in location from obstacle
		double xOffset = distanceFromObsticel * cos(yawInRad + currentAngle);
		double yOffset = distanceFromObsticel * sin(yawInRad + currentAngle);

		// Setting the free spaces in the map

		bool isThereAnObstical = true;// see if there is an obstical at sensores estimated location
		bool obsticalPrediction = true;// get obsticals from memory map at location

		bool miss = (isThereAnObstical != obsticalPrediction);
		bool hit = (isThereAnObstical == obsticalPrediction);

		if(miss){
			misses++;
			//update your map;?
		}
		if(hit){
			hits++;
		}

	}
	double probabiltyEstimation = hits/(hits+misses);
	return probabiltyEstimation;
}
void Particle::_updateLocationEstimation(){
	//this->_belief = this->_getParticleObservationsProbablity() * this->_belief * this->getProgressProbability();
}

void Particle::mutateFromRefrance(Particle* partical){
	this->_cloneFrom(partical->getPosition());
	this->_randomizeLocation();
	this->_updateLocationEstimation();
}

//
//void Particle::UpdateParticle(double deltaX, double deltaY, double deltaYaw, Robot* robot)
//{
//	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
//	double radYaw = (deltaYaw + _yaw);
//
//	// Update robot location
//	_locationX += (cos(radYaw) * distance);
//	_locationY += (sin(radYaw) * distance);
//	_yaw += deltaYaw;
//
//	double progProb = calcProgressProb(deltaX, deltaY, deltaYaw);
//	double obsProb = calcObsProb(robot);
//
//	_belief *= COEFFICIENT * progProb * obsProb;
//
//	if (_belief > 1)
//		_belief = 1;
//}
//

Particle::~Particle(void)
{
}
