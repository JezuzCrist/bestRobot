#pragma once
#include "stdlib.h"
#include "math.h"
#include "limits.h"
using namespace std;

struct Position {
	int x;
	int y;

	Position(int x, int y)
	{
		this -> x = x;
		this -> y = y;
	}
};

class Color {
public:
	int red;
	int green;
	int blue;
	float alpha;

	Color(int red, int green, int blue, float alpha);
	bool isWhite();
	void init();
};

class Cell
{
public:
	Cell();
	Cell(int x, int y, bool w);
	Cell(int x, int y, bool w, Color *color);
	Position* getPosition();
	Cell* getParent();
	void setParent(Cell *p);
	int getX();
	int getY();
	Color* getColor();
	float getXf();
	float getYf();
	int getDistanceBetween(Cell *other);
	int getHScore(Cell *p);
	int getDistanceTravelled();
	int getHScore();
	int getFScore();
	void computeScores(Cell *end);
	bool hasParent();
	int min(int num, int num1);
	bool Cell::isOpened();
	bool Cell::isClosed();
	bool operator==(const Cell& rhs) const;
public:
	int x,y,f,g,h;
	Cell* parent;
	bool closed, opened, walkable;
	Color* color;
	const static int SIMPLE_MOVING_COST = 10;
	const static int DIAGONAL_MOVING_COST = 14;
	const static int INFINITY = INT_MAX;
	//void init();
};
