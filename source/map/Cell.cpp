#include "Cell.h"

Color::Color()
{
}

Color::Color(int red, int green, int blue, float alpha)
{
	this -> red = red;
	this -> green = green;
	this -> blue = blue;
	this -> alpha = alpha;
}

bool Color::isWhite()
{
	bool allColorsAreWhite = this->red == WHITE;
	allColorsAreWhite = allColorsAreWhite && this->blue == WHITE;
	allColorsAreWhite = allColorsAreWhite && this->green == WHITE;
	if (allColorsAreWhite)
	{
		return true;
	}
	return false;
}

void Color::setBlack()
{
	red = green = blue = BLACK;
}

void Color::setWhite()
{
	red = green = blue = WHITE;
}

Cell::Cell()
{
	this->parent = NULL;
    this->closed = false;
    this->opened = false;
	this->walkable = false;
    x = y = f = g = h = INFINITY;
	this -> color = new Color();
}

Cell::Cell(int x, int y, bool walkable)
{
	f = g = h = INFINITY;
	this->parent = NULL;
    this->closed = false;
    this->opened = false;
    this -> walkable = walkable;
    this -> x = x;
    this -> y = y;
	this -> color = new Color();
	(this -> walkable == true) ? color->setWhite() : color->setBlack();
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
	int distanceBetween = DIAGONAL_MOVING_COST;

    if (this->x == other->x || this->y == other->y)
    {
    	distanceBetween = SIMPLE_MOVING_COST;
    }
    return distanceBetween;
}

//distance estimated
int Cell::getHScore(Cell *destination)
{
	int dx = abs(destination->x - this->x);
    int dy = abs(destination->y - this->y);
    return (SIMPLE_MOVING_COST * (dx + dy)); /*+
			(DIAGONAL_MOVING_COST - 2 * SIMPLE_MOVING_COST) *
			min(dx, dy));*/
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
	if (this->x == other.x && this->y == other.y)
		return true;

	return false;
}
