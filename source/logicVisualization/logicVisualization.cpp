#include "logicVisualization.h"
using namespace std;

logicVisualization::logicVisualization(){

}

void logicVisualization::printToPicture(vector<MapPosition2D*> pathToGoal, Map* map,
		            ConfigurationManager* configurationManager,
		             vector<MapPosition2D*> waypoints)
{
	PositionConveter* positionConverter = new PositionConveter(configurationManager);
	ImageSize* imgSize = map->getImgSize();
	vector<unsigned char> image = map->getBlownImage();

	this->_printObsticalsAndMap(positionConverter,map,&image,imgSize);

	this->_printPath(positionConverter,pathToGoal,&image,imgSize);

	this->_printWayPoints(positionConverter,waypoints,&image,imgSize);

	unsigned height = (unsigned)imgSize->height, width = (unsigned)imgSize->width;
	encodeOneStep("output/logic.png", image, width, height);
}


logicVisualization::~logicVisualization() {
	// TODO Auto-generated destructor stub
}

void logicVisualization::_printObsticalsAndMap(PositionConveter* positionConverter,
 Map* map, vector<unsigned char>* image,ImageSize* imgSize){
	WorldPosition2D* worldPosition;


	Cell*** grid = map->getMap();
	ImageSize* mapSize = map->getMapSize();
	
	for (int row = 0; row < imgSize->height; ++row)
	{
		for (int col = 0; col < imgSize->width; ++col)
		{
			// cout << (int)(*image)[row * imgSize->width * 4 + col * 4] << " " 
			// << ((int)(*image)[row * imgSize->width * 4 + col * 4 + 0] == 255) << endl;
			if((int)(*image)[row * imgSize->width * 4 + col * 4 + 0] == 255){
				(*image)[row * imgSize->width * 4 + col * 4 + 0] = 67;
				(*image)[row * imgSize->width * 4 + col * 4 + 1] = 67;
				(*image)[row * imgSize->width * 4 + col * 4 + 2] = 67;
			} else {
				(*image)[row * imgSize->width * 4 + col * 4 + 0] = 72;
				(*image)[row * imgSize->width * 4 + col * 4 + 1] = 72;
				(*image)[row * imgSize->width * 4 + col * 4 + 2] = 72;
			}
		}
	}

	for (int row=0; row < mapSize->height; row++)
	{
		for (int col=0; col<mapSize->width; col++)
		{
			int x = grid[row][col]->x;
			int y = grid[row][col]->y;
			// cout << "row " << row << " col " << col << endl;
			// cout << "X: " << x << " Y: " <<y<< endl;
			MapPosition2D* mapPosition = new MapPosition2D(x, y);
			// cout << "before "<< mapPosition->y <<endl;
			worldPosition = positionConverter->getWorldPosition2D(mapPosition);
			// cout << "after "<< worldPosition->y <<endl;
			int imgRow = worldPosition->y;
			int imgCol = worldPosition->x;
			int color;
			if (grid[row][col]->walkable)
			{
				(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 0] = 67;
				(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 1] = 67;
				(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 2] = 67;
			}
			else
			{
				(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 0] = 80;
				(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 1] = 80;
				(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 2] = 80;
			}
			
		}
	}
};
void logicVisualization::_printPath(PositionConveter* positionConverter,vector<MapPosition2D*> pathToGoal,
		vector<unsigned char>* image,ImageSize* imgSize){

	WorldPosition2D* worldPosition;
	vector<MapPosition2D*>::iterator i;
	 for (i = pathToGoal.begin(); i != pathToGoal.end(); ++ i)
	 {
	 	worldPosition = positionConverter->getWorldPosition2D((*i));
	 	int imgRow = worldPosition->y;
	 	int imgCol = worldPosition->x;
	 	(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 0] = 70;
	 	(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 1] = 174;
	 	(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 2] = 50;
	 }
};
void logicVisualization::_printWayPoints(PositionConveter* positionConverter,vector<MapPosition2D*> waypoints,
		vector<unsigned char>* image,ImageSize* imgSize){

	WorldPosition2D* worldPosition;
	vector<MapPosition2D*>::iterator i;
	for (i = waypoints.begin(); i != waypoints.end(); ++ i)
	{
		worldPosition = positionConverter->getWorldPosition2D((*i));
		int imgRow = worldPosition->y;
		int imgCol = worldPosition->x;
		(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 0] = 88;
		(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 1] = 207;
		(*image)[imgRow * imgSize->width * 4 + imgCol * 4 + 2] = 64;

		(*image)[imgRow * imgSize->width * 4 + (imgCol+1) * 4 + 0] = 88;
		(*image)[imgRow * imgSize->width * 4 + (imgCol+1) * 4 + 1] = 207;
		(*image)[imgRow * imgSize->width * 4 + (imgCol+1) * 4 + 2] = 64;

		(*image)[(imgRow+1) * imgSize->width * 4 + (imgCol) * 4 + 0] = 88;
		(*image)[(imgRow+1) * imgSize->width * 4 + (imgCol) * 4 + 1] = 207;
		(*image)[(imgRow+1) * imgSize->width * 4 + (imgCol) * 4 + 2] = 64;

		(*image)[(imgRow+1) * imgSize->width * 4 + (imgCol+1) * 4 + 0] = 88;
		(*image)[(imgRow+1) * imgSize->width * 4 + (imgCol+1) * 4 + 1] = 207;
		(*image)[(imgRow+1) * imgSize->width * 4 + (imgCol+1) * 4 + 2] = 64;
	}

};
