#include "NavigationFactory.h"
#include "AbstractNavigation.h"
using namespace std;


const string NavigationFactory::libraryPath = "Libraries/Navigation/";
map<string, Navigation*> NavigationFactory::nav;

Navigation& NavigationFactory::getNav(string navName)
{
	if(nav.count(navName) == 0)
		nav[navName] = new Navigation(navName.c_str(), (libraryPath + navName + "/" + navName + ".so").c_str());
	return *nav[navName];
}

void NavigationFactory::rmNav(std::string navName)
{
	if(nav.count(navName) != 0){
		delete nav[navName];
		nav.erase(navName);
	}
}

bool NavigationFactory::compileAll()
{
	for(auto navLib : nav){
		navLib.second->getNav()->init();
	}
}
