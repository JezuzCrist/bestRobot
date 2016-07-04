#pragma once
#include "../../map/Cell.h"
#include "../../map/Map.h"
#include <list>

class PathPlanner
{
public:
	PathPlanner(Map* worldMap);

	vector<MapPosition2D*> getPath(MapPosition2D sourcePoint, MapPosition2D destPoint);

private:
	Map* _map;

	Cell* getCellFromMap(int x, int y);
	bool cellIsWalkable(Cell* Cell);
	list<Cell*> getNeighbors(Cell *current);
	Cell* getSmallestF(list<Cell*> CellsList);
	vector<MapPosition2D*> reconstruct_path(Cell *start, Cell *end);
	void resetOpenedCells(list<Cell*> openList);
	void setClose(list<Cell*> openList, Cell *CellToClose);
	void setOpen(list<Cell*> openList, Cell *CellToOpen);
};

