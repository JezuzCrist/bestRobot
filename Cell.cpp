#include "StdAfx.h"
#include "Cell.h"

Color::Color(int red, int green, int blue, float alpha)
{
	this -> red = red;
	this -> green = green;
	this -> blue = blue;
	this -> alpha = alpha;
}

bool Color::isWhite()
{
	if (red == 255 && green == 255 && blue == 255)
		return true;
	return false;
}


Cell::Cell()
{
	this->parent = NULL;
    this->closed = false;
    this->opened = false;
    x = y = f = g = h = INFINITY;
}

Cell::Cell(int x, int y, bool w)
{
	f = g = h = INFINITY;
	this->parent = NULL;
    this->closed = false;
    this->opened = false;
    this -> walkable = w;
    this -> x = x;
    this -> y = y;
}

Cell::Cell(int x, int y, bool w, Color *color)
{
	f = g = h = INFINITY;
	this->parent = NULL;
    this->closed = false;
    this->opened = false;
    this -> walkable = w;
    this -> x = x;
    this -> y = y;
	this -> color = color;
}

Position* Cell::getPosition()
{
    return new Position(x, y);
}

Cell* Cell::getParent()
{
    return parent;
}

void Cell::setParent(Cell *p)
{
    parent = p;
}

int Cell::getX()
{
    return x;
}

int Cell::getY()
{
    return y;
}

bool Cell::isOpened()
{
	return opened;
}

bool Cell::isClosed()
{
	return closed;
}

Color* Cell::getColor()
{
	return color;
}

int Cell::getDistanceBetween(Cell *other)
{
    return (this->x == other->x || this->y == other->y) ? SIMPLE_MOVING_COST : DIAGONAL_MOVING_COST;
}

//distance estimated
int Cell::getHScore(Cell *destination)
{
	int dx = abs(destination->x - this->x);
    int dy = abs(destination->y - this->y);
    return (SIMPLE_MOVING_COST * (dx + dy) /*+ 
			(DIAGONAL_MOVING_COST - 2 * SIMPLE_MOVING_COST) * 
			min(dx, dy)*/);
}

int Cell::getDistanceTravelled()
{
    return g;
}

int Cell::getHScore()
{
    return h;
}

//heoroistic
int Cell::getFScore()
{
    return f;
}

void Cell::computeScores(Cell *end)
{
	int distanceFromStart;
	distanceFromStart = parent->getDistanceTravelled() + parent->getDistanceBetween(this);
    g = distanceFromStart;
    h = getHScore(end);
    f = g + h;
}

bool Cell::hasParent()
{
    return parent != NULL;
}

int Cell::min(int num, int num1)
{
	if (num < num1)
		return num;
	return num1;
}

bool Cell::operator==(const Cell& other) const
{
	bool Equal = true;

	if (this->x == other.x && this->y == other.y)
		return true;

	return false;
}
