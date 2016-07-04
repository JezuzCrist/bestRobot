#pragma once

struct Position2D
{
	int x;
	int y;

	Position2D()
	{
	}

	Position2D(int x, int y)
	{
		this -> x = x;
		this -> y = y;
	}
};
typedef Position2D WorldPosition2D;
typedef Position2D MapPosition2D;

struct Position3D
{
	double x;
	double y;
	double yaw;

	Position3D()
	{
	}

	Position3D(double x, double y, double yaw)
	{
		this -> x = x;
		this -> y = y;
		this -> yaw = yaw;
	}

	Position3D(Position2D position2D, double yaw)
	{
		this -> x = (double)position2D.x;
		this -> y = (double)position2D.y;
		this -> yaw = yaw;
	}
};
typedef Position3D WorldPosition3D;
typedef Position3D MapPosition3D;
