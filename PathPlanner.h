#pragma once
#include "Cell.h"
#include "map.h"
#include <list>

class PathPlanner
{
public:
	PathPlanner(Map* worldMap);

	vector<Position*> getPath(int sourceX, int sourceY, int destX, int destY);

private:
	Map* _map;

	Cell* getCellFromMap(int x, int y);
	bool cellIsWalkable(Cell* Cell);
	list<Cell*> getNeighbors(Cell *current);
	Cell* getSmallestF(list<Cell*> CellsList);
	vector<Position*> reconstruct_path(Cell *start, Cell *end);
	void resetOpenedCells(list<Cell*> openList);
	void setClose(list<Cell*> openList, Cell *CellToClose);
	void setOpen(list<Cell*> openList, Cell *CellToOpen);
};

