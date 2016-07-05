#include "PositionConveter.h"

WorldPosition2D* PositionConveter::getWorldPosition2D(MapPosition2D* mapPosition)
{
	WorldPosition2D* worldPosFromMapPos;
	worldPosFromMapPos = new WorldPosition2D(mapPosition->x * resolutionRelation,
											 mapPosition->y * resolutionRelation);
	return worldPosFromMapPos;
}

MapPosition2D* PositionConveter::getMapPosition2D(WorldPosition2D* worldPosition)
{
	MapPosition2D* mapPosFromWorldPos;
	mapPosFromWorldPos = new WorldPosition2D(worldPosition->x / resolutionRelation,
											 worldPosition->y / resolutionRelation);
	return mapPosFromWorldPos;
}

WorldPosition3D* PositionConveter::getWorldPosition3D(WorldPosition2D* worldPosition)
{
	double yaw = 0;
	WorldPosition3D* worldPosition3D;
	worldPosition3D = new WorldPosition3D(*worldPosition, yaw);
	return worldPosition3D;
}

PositionConveter::PositionConveter(ConfigurationManager* paramsParser)
{
	this -> resolutionRelation = (int)(paramsParser->gridResolutionInCm /
									   paramsParser->mapResolutionInCm);
}
