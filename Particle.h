#pragma once

using namespace std;

class Particle
{
public:
	Particle(void);
	Particle(double deltaX, double deltaY, double deltaTeta);
	~Particle(void);
	void update(double deltaX, double deltaY, double deltaTeta);
	void move(double deltaX, double deltaY, double deltaTeta);
	//void update(double deltaX, double deltaY, double deltaTeta , LaserProxy* laser);
	double probMov(double deltaX, double deltaY, double deltaTeta);

	double getBelief();

private:
	double _belief,acurecyPrediction;

};

