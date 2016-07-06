#include "Particle.h"
using namespace std;

void _initRandom(){
	srand(time(NULL));
}

Particle::Particle(void)
{
	this->position = new WorldPosition3D();
	this->_belief = 0;
}
Particle::Particle(double x, double y, double yaw)
{
	this->position = new WorldPosition3D();
	this->_belief = 0;
	this->position->x = x;
	this->position->y = y;
	this->position->yaw = yaw;
}
Particle::Particle(Particle* mutateFromThisPartical,int LOCATION_RANDOMNESS,Robot* robot,Map* map)
{
	this->position = new WorldPosition3D();
	this->_belief = 0;
	this->mutateFromRefrance(mutateFromThisPartical,LOCATION_RANDOMNESS,robot,map);
}

double Particle::getBelief(){	return this->_belief;	}
WorldPosition3D* Particle::getPosition(){	return this->position;	}


void Particle::move(double changeX, double changeY, double changeYaw)
{
	this->position->x += changeX;
	this->position->y += changeY;
	this->position->yaw += changeYaw;
}
void Particle::_cloneFrom(WorldPosition3D* clonePosition){
	this->position->x = clonePosition->x;
	this->position->y = clonePosition->y;
	this->position->yaw = clonePosition->yaw;
}
void Particle::_randomizeLocation(int LOCATION_RANDOMNESS){
	//_initRandom();
//	cout << "RANDOME:" << (rand() % LOCATION_RANDOMNESS) << "  " << (rand() % LOCATION_RANDOMNESS) << endl;
	this->position->x = std::max(0.0, this->position->x + (rand() % LOCATION_RANDOMNESS) - LOCATION_RANDOMNESS/2 );
	this->position->y = std::max(0.0, this->position->y + (rand() % LOCATION_RANDOMNESS) - LOCATION_RANDOMNESS/2 );
	this->position->yaw = std::max(0.0, this->position->yaw + (rand() % LOCATION_RANDOMNESS));
}
double Particle::_getParticleObservationsProbablity(Robot* robot, Map* map){
	unsigned hits = 0, misses = 0;
	// double angleBetweenLasers = 20;
	//(0.36)*i - 120

	for(int laserIndex = 0 ; laserIndex < MAX_LASER_ANGEL; laserIndex+= SKIP_LASER_ANGLE){
		double laserValue = robot->getLaserDistance(laserIndex);
		cout<< "laserIndex" << laserIndex << "   laserValue = " << laserValue << endl;
		double laserAngel = laserIndex * LASER_SENSOR_SEPERATION - LASER_SENSOR_CENTER;
		double currentAngle = robot->getPosition()->yaw; //((i * (0.36) - 120.0) / 180.0) * M_PI;
		// double yawInRad = PlayerCc::dtor(currentAngle); //= _yaw/180.0 * M_PI;

		// Calculating diffrence in location from obstacle
		double distanceFromObsticel = std::min(MIN_OBSTICAL_DISTANCE, laserValue);
		double xOffset = distanceFromObsticel * cos(laserAngel + currentAngle);
		double yOffset = distanceFromObsticel * sin(laserAngel + currentAngle);

		bool isThereAnObstical = (distanceFromObsticel < MIN_OBSTICAL_DISTANCE);// see if there is an obstical at sensores estimated location

		WorldPosition2D* predictedObstical = new WorldPosition2D(this->position->x + xOffset, this->position->y + yOffset);
		cout << "xOffset " <<  predictedObstical->x << "  yOffset"<< predictedObstical->y << endl;
		bool obsticalPrediction = map->hasObstacle(predictedObstical) ;// get obsticals from memory map at location
		//map->get


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
void Particle::_updateLocationEstimation(Robot* robot,Map* map){
	// this->_belief = this->_getParticleObservationsProbablity() * this->_belief * this->getProgressProbability();
	//  2*PAST_BELIFE/3 + NewBelife/3 = belife
	this->_belief = (this->_getParticleObservationsProbablity(robot,map))/3 + 2*(this->_belief)/3;
	cout << "BELIEF === WHAT(" << this->_belief << ")"<< endl;
}

void Particle::mutateFromRefrance(Particle* partical,int LOCATION_RANDOMNESS,Robot* robot,Map* map){
	this->_cloneFrom(partical->getPosition());
	this->_randomizeLocation(LOCATION_RANDOMNESS);
	this->_updateLocationEstimation(robot,map);
}

void Particle::update(double deltaX, double deltaY, double deltaYaw, Robot* robot,Map* map)
{
	this->move(deltaX,deltaY,deltaYaw);
	this->_updateLocationEstimation(robot,map);
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
