#include "PathPlanner.h"

PathPlanner::PathPlanner(Map* worldMap)
{
	this->_map = worldMap;
}

Cell* PathPlanner::getCellFromMap(int x, int y)
{
	return this->_map->map[(int)x][(int)y];
}

bool PathPlanner::cellIsWalkable(Cell *cell)
{
	// obstacle case
	for (int i = -1; i < 2; ++i)
		for (int j = -1; j < 2; ++j)
			if (this->_map -> inBound(cell->getX() + i, cell->getY() + j) &&
				!getCellFromMap(cell->getX() + i, cell->getY() + j)-> walkable)
				return false;
	return true;
}

list<Cell*> PathPlanner::getNeighbors(Cell *current)
{
	Cell* neighbor;
	list<Cell*> neighbors;

	for (int x = -1; x < 2; x ++)
    {
        for (int y = -1; y < 2; y ++)
        {
            if (!this->_map->inBound(current->getX() + x, current->getY() + y))
				continue;

			neighbor = getCellFromMap(current->getX() + x, current->getY() + y);

			// If it's current cell then pass
			if (neighbor == current)
				continue;

            // If it's closed or not walkable then pass
			if (neighbor->isClosed() || !cellIsWalkable(neighbor))
                continue;

			// Get this cell
            neighbors.push_back(neighbor);
		}
	}

	return neighbors;
}

Cell* PathPlanner::getSmallestF(list<Cell*> cellsList)
{
	Cell* minCell = (*cellsList.begin()), currCell;
	list<Cell*>::iterator i;

	for (i = cellsList.begin(); i != cellsList.end(); ++ i)
	{
        if (i == cellsList.begin() || (*i)->getFScore() <= minCell->getFScore())
            minCell = (*i);
	}

	return minCell;
}

vector<MapPosition2D*> PathPlanner::reconstruct_path(Cell *start, Cell *end)
{
	Cell *current = end;
	vector<MapPosition2D*> path;

	while (current->hasParent() && !(current == start))
    {
        path.push_back(current->getPosition());
        current = current->getParent();
    }

	return path;
}

void PathPlanner::resetOpenedCells(list<Cell*> openList)
{
	list<Cell*>::iterator i;
	for (i = openList.begin(); i != openList.end(); ++ i)
        (*i)->opened = false;
}

void PathPlanner::setClose(list<Cell*> openList, Cell *cellToClose)
{
	cellToClose->opened = false;
    // Add the current cell to the closedList
    cellToClose->closed = true;
	// Remove the current cell from the openList
	openList.remove(cellToClose);
}

void PathPlanner::setOpen(list<Cell*> openList, Cell *cellToOpen)
{
	cellToOpen->opened = true;
	cellToOpen->opened = false;
	openList.push_back(cellToOpen);
}

vector<MapPosition2D*> PathPlanner::getPath(MapPosition2D sourcePoint, MapPosition2D destPoint)
{
    // Define cells to work with
	Cell *start = getCellFromMap(sourcePoint.x, sourcePoint.y);
    Cell *end = getCellFromMap(destPoint.x, destPoint.y);
	start->g = 0;
	start->f = start->getHScore(end);
    Cell *current = start;
    Cell *neighbor;

	if (!start->walkable || !end->walkable)
		throw "The cell (start or end) is not walkable " + end->walkable;

    // Define the open and the close list
    list<Cell*> openList;
	list<Cell*> neighbors;
    list<Cell*>::iterator i;

    // Add the start cell to the openList
    openList.push_back(start);
    start->opened = true;

	while (!openList.empty())
    {
        // Look for the smallest F value in the openList and make it the current cell
        current = getSmallestF(openList);

        // Stop if we reached the end
        if (current == end)
            break;

		setClose(openList, current);

        // Get all current's adjacent walkable cells
		neighbors = getNeighbors(current);

        for (i = neighbors.begin(); i != neighbors.end(); ++i)
		{
			neighbor = (*i);

            // If it's already in the openList
            if (neighbor->isOpened())
            {
                // If it has a wroste g score than the one that pass through the current cell
                // then its path is improved when it's parent is the current cell
				if (neighbor->getDistanceTravelled() >
					current->getDistanceTravelled() + current->getDistanceBetween(neighbor))
                {
                    // Change its parent and g score
                    neighbor->setParent(current);
                    neighbor->computeScores(end);
                }
            }
            else
            {
                // Add it to the openList with current cell as parent
				setOpen(openList, neighbor);

                // Compute it's g, h and f score
                neighbor->setParent(current);
                neighbor->computeScores(end);
            }
        }
    }

    // Reset
	resetOpenedCells(openList);

    // Resolve the path starting from the end cell
	vector<MapPosition2D*> fromStartToEnd = reconstruct_path(start, end);

    return fromStartToEnd;
}
