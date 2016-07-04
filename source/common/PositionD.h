#pragma once

struct PositionD {
	double x;
	double y;
	double yaw;

	PositionD(int x, int y,double yaw)
	{
		this -> x = x;
		this -> y = y;
		this->yaw = yaw;
	}
	PositionD()
	{
	}
};
