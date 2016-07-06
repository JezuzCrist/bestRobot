#pragma once
#include "Particle.h"
#include "../../common/Position.h"
#include "../../common/PositionConveter.h"
#include <vector>

#define PARTICLE_COUNT 200

using namespace std;

class LocalizationManager
{
public:
	LocalizationManager(WorldPosition3D startingPoint);
	~LocalizationManager(void);
	void update(double changeX, double changeY, double changeYaw, Robot* robot);
	MapPosition3D getEstimatedPosition();
	vector<Particle*> getParticals();

private:
	const static int ParticalCount = PARTICLE_COUNT;
	const static int ParticalSpread = 20;
	const static int ParticalFirstSpread = 130;
	const static int ParticalsToRenew = 20;


	vector<Particle*> _particles;
	Particle _bestEstimatedPartical;
	void _init(WorldPosition3D startingPoint);
	void _sortParticalsByBelife();
	Particle* _getBestParticle();
};

