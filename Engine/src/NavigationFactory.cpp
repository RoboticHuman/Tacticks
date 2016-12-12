#include "NavigationFactory.h"
#include "AbstractNavigation.h"
using namespace std;

const string NavigationFactory::libraryPath = "Libraries/Navigation/";
map<string, Navigation*> NavigationFactory::nav;
map<string, int> NavigationFactory::navCount;
Navigation NavigationFactory::nullNav;

Navigation& NavigationFactory::newNav(string navName)
{
	auto it = navCount.find(navName);
	if(it == navCount.end())
	{
		navCount[navName] = 0;
		nav[navName] = new Navigation(navName.c_str(), (libraryPath + navName + "/" + navName + ".so").c_str());
	}
	navCount[navName]++;
	return *nav[navName];
}
Navigation& NavigationFactory::getNav(string navName)
{
	if(nav.count(navName) == 0) return nullNav;
	return *nav[navName];
}

void NavigationFactory::rmNav(std::string navName)
{
	auto it = navCount.find(navName);
	if(it == navCount.end()) return;	//No such navName
	if(--it->second == 0){
		delete nav[navName];
		nav.erase(navName);
		navCount.erase(navName);
	}
}

void NavigationFactory::rmNav_force(std::string navName)
{
	if(nav.count(navName) != 0){
		delete nav[navName];
		nav.erase(navName);
		navCount.erase(navName);
	}
}

bool NavigationFactory::compileAll()
{
	for(auto& navLib : nav) {
		if(navLib.second->getNav()->isDirty() && !navLib.second->getNav()->init())
			return false;
	}
	return true;
}

vector<string> NavigationFactory::getNavList()
{
	vector<string> ret;
	for(auto it : navCount)
		ret.push_back(it.first);
	return ret;
}
