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
public:
	PositionConveter(ConfigurationManager* paramParser);
	WorldPosition2D* getWorldPosition(MapPosition2D* mapPosition);
	MapPosition2D* getMapPosition(WorldPosition2D* worldPosition);

private:
	int resolutionRelation;
};

#endif /* POSITIONCONVETER_H_ */
