#ifndef NavigationFactory_H
#define NavigationFactory_H

#include <map>
#include <string>
#include "Navigation.h"
#include <vector>

class NavigationFactory
{
	NavigationFactory() = delete;
	NavigationFactory(const NavigationFactory&) = delete;
	NavigationFactory(NavigationFactory&&) = delete;
	~NavigationFactory() = delete;
private:
	static const std::string libraryPath;
	static std::map<std::string, Navigation*> nav;
	static std::map<std::string, int> navCount;
	static Navigation nullNav;
public:
	static Navigation& newNav(std::string navName);
	static Navigation& getNav(std::string navName);
	static void rmNav(std::string navName);
	static void rmNav_force(std::string navName);	//Use with extreme caution...
	static bool compileAll();
	static std::vector<std::string> getNavList();
};

#endif
