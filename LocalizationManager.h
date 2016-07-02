#pragma once
#include "Particle.h"
#include <list>
#include <ctime>
using namespace std;

class LocalizationManager
{
public:
	LocalizationManager(void);
	~LocalizationManager(void);



private:
	list<Particle> _particles;
};

