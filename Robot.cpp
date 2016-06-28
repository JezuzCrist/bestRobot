#include "stdafx.h"
#include "Robot.h"


Robot::Robot(void)
{
	pc = new PlayerClient(ip, port);
	pp = new Position2dProxy(pc);
	lp = new LaserProxy(pc);
}


Robot::~Robot(void)
{
}
