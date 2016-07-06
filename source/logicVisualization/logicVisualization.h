
#ifndef LOGICVISUALIZATION_H_
#define LOGICVISUALIZATION_H_
#include "../common/Position.h"
#include "../common/PositionConveter.h"
#include "../map/Map.h"


class logicVisualization {
public:
	logicVisualization();
	void printToPicture(vector<MapPosition2D*> pathToGoal, Map* map,
			            ConfigurationManager* configurationManager,vector<MapPosition2D*> waypoints);
	virtual ~logicVisualization();
};

#endif /* LOGICVISUALIZATION_H_ */
