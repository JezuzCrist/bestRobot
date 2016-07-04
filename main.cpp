// robot_nir_omer.cpp : Defines the entry point for the console application.

#include "source/managers/configuration/ConfigurationManager.h"


int main()
{
	ConfigurationManager p = ConfigurationManager();
	p.parse("parameters.txt");

	cout << p.mapFileLocation<< endl;
	cout << p.startPosition.point.x<<","<<p.startPosition.point.y<<","<<p.startPosition.angle<< endl;
	cout<<p.goal.x<<","<<p.goal.y<<endl;
	cout<<p.size.width<<","<<p.size.height<<endl;
	cout<<p.mapResolutionInCm<<endl;
	cout<<p.gridResolutionInCm<<endl;
	cout<<"compiling and building is working in linux !"<<endl;
	return 0;
}
