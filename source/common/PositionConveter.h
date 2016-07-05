/*
 * PositionConveter.h
 *
 *  Created on: Jul 5, 2016
 *      Author: user
 */
#include "../managers/configuration/ConfigurationManager.h"
#ifndef POSITIONCONVETER_H_
#define POSITIONCONVETER_H_
using namespace std;

class PositionConveter
{
private:
	int resolutionRelation;

public:
	PositionConveter(ConfigurationManager* paramsParser);

	WorldPosition2D* getWorldPosition2D(MapPosition2D* mapPosition);
	MapPosition2D* getMapPosition2D(WorldPosition2D* worldPosition);
	WorldPosition3D* getWorldPosition3D(WorldPosition2D* worldPosition);
};

#endif /* POSITIONCONVETER_H_ */
