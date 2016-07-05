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
	static void createInstance(ConfigurationManager* paramParser)
	{
		instance = new PositionConveter(paramParser);
	}

	static PositionConveter* getInstance()
	{
		return instance;
	}

	WorldPosition2D* getWorldPosition2D(MapPosition2D* mapPosition);
	MapPosition2D* getMapPosition2D(WorldPosition2D* worldPosition);
	WorldPosition3D* getWorldPosition3D(WorldPosition2D* worldPosition);

private:
	int resolutionRelation;
	static PositionConveter* instance;

	PositionConveter(ConfigurationManager* paramParser)
	{
		this -> resolutionRelation = (int)(paramParser->gridResolutionInCm /
										   paramParser->mapResolutionInCm);
	}
};

#endif /* POSITIONCONVETER_H_ */
