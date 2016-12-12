#include <iostream>
#include <Tacticks/BehaviourModuleFactory.h>
#include <Tacticks/NavigationFactory.h>
#include <Tacticks/BehaviourPipeline.h>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>
#include <glm/ext.hpp>
using namespace glm;
using namespace std;

BehaviourPipeline pipeline;

int main()
{
	auto lst = BehaviourModuleFactory::getBehList();
	pipeline.addNavigationLibrary("2DNavigator");
	cout << "Forces:" << endl;
	for(string str : lst.first)
		cout << str << endl;

	cout << "Milestone:" << endl;
	for(string str : lst.second)
		cout << str << endl;

	cout << "Navigation:" << endl;
	for(string str : NavigationFactory::getNavList())
		cout << str << endl;

	pipeline.removeNavigationLibrary("2DNavigator");
	cout << "After Navigation:" << endl;
	for(string str : NavigationFactory::getNavList())
		cout << str << endl;
}
