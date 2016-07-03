#pragma once

struct Position {
	int x;
	int y;
	double yaw;
	Position(int x, int y)
	{
		this -> x = x;
		this -> y = y;
	}
	Position(int x, int y,double yaw)
	{
		this -> x = x;
		this -> y = y;
		this->yaw = yaw;
	}
};