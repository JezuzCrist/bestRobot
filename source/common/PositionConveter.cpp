#include "PositionConveter.h"

PositionConveter::PositionConveter(ConfigurationManager* paramParser)
{
	this -> resolutionRelation = (int)(paramParser->gridResolutionInCm /
									   paramParser->mapResolutionInCm);
}

WorldPosition2D* PositionConveter::getWorldPosition(MapPosition2D* mapPosition)
{
	WorldPosition2D* worldPosFromMapPos;
	worldPosFromMapPos = new WorldPosition2D(mapPosition->x * resolutionRelation,
											 mapPosition->y * resolutionRelation);
	return worldPosFromMapPos;
}

MapPosition2D* PositionConveter::getMapPosition(WorldPosition2D* worldPosition)
{
	MapPosition2D* mapPosFromWorldPos;
	mapPosFromWorldPos = new WorldPosition2D(worldPosition->x / resolutionRelation,
											 worldPosition->y / resolutionRelation);
	return mapPosFromWorldPos;
}
