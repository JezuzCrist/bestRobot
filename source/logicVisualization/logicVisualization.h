
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

private:
	void _printObsticalsAndMap(PositionConveter* positionConverter, Map* map,
	 vector<unsigned char>* image,ImageSize* imgSize);
	void _printPath(PositionConveter* positionConverter,vector<MapPosition2D*> pathToGoal,
			vector<unsigned char>* image,ImageSize* imgSize);
	void _printWayPoints(PositionConveter* positionConverter,vector<MapPosition2D*> waypoints,
			vector<unsigned char>* image,ImageSize* imgSize);

};

#endif /* LOGICVISUALIZATION_H_ */
