#ifndef NavigationFactory_H
#define NavigationFactory_H

#include <vector>
#include <map>
#include <string>

class AbstractNavigation;

struct Navigation
{
	std::string name;
	std::vector<std::string> navDependencies;
public:
	bool validity() const;
};

class NavigationFactory
{
	NavigationFactory() = delete;
	NavigationFactory(const NavigationFactory&) = delete;
	NavigationFactory(NavigationFactory&&) = delete;
	~NavigationFactory() = delete;
private:
	static const std::string libraryPath;
	static std::map<std::string, void*> navSOHandle;
public:
	static bool load(std::string navName);
	static void unload(std::string navName);
	static AbstractNavigation* newNav(std::string navName);
	static Navigation getMetaData(std::string navName);
};

#endif
