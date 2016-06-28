#pragma once
#include "Cell.h"
#include "map.h"
#include <list>

class PathPlanner
{
public:
	PathPlanner(string& mapImageFilePath);
	bool isEqual(Cell *a, Cell *b);
	Cell* getCellFromMap(int x, int y);
	bool cellIsWalkable(Cell* Cell);
	list<Cell*> PathPlanner::getNeighbors(Cell *current);
	Cell* PathPlanner::getSmallestF(list<Cell*> CellsList);
	vector<Position*> PathPlanner::reconstruct_path(Cell *start, Cell *end);
	void PathPlanner::resetOpenedCells(list<Cell*> openList);
	void PathPlanner::setClose(list<Cell*> openList, Cell *CellToClose);
	void PathPlanner::setOpen(list<Cell*> openList, Cell *CellToOpen);
	vector<Position*> getPath(int x1, int y1, int x2, int y2);

	Map* map;
};

