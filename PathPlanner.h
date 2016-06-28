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
	list<Cell*> PathPlanner::getNeighbors(Cell *current);
	Cell* PathPlanner::getSmallestF(list<Cell*> CellsList);
	vector<Position*> PathPlanner::reconstruct_path(Cell *start, Cell *end);
	void PathPlanner::resetOpenedCells(list<Cell*> openList);
	void PathPlanner::setClose(list<Cell*> openList, Cell *CellToClose);
	void PathPlanner::setOpen(list<Cell*> openList, Cell *CellToOpen);
};

