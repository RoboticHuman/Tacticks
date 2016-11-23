#ifndef NavigationFactory_H
#define NavigationFactory_H

#include <map>
#include <string>
#include "Navigation.h"

class NavigationFactory
{
	NavigationFactory() = delete;
	NavigationFactory(const NavigationFactory&) = delete;
	NavigationFactory(NavigationFactory&&) = delete;
	~NavigationFactory() = delete;
private:
	static const std::string libraryPath;
	static std::map<std::string, Navigation*> nav;
public:
	static Navigation& getNav(std::string navName);
	static void rmNav(std::string navName);
};

#endif
