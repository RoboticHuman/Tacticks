#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <vector>
#include <string>
class AbstractNavigation;
class World;

struct NavigationInfo
{
	std::vector<std::string> navDependencies;
};

class Navigation
{
	Navigation(const Navigation&) = delete;
	Navigation(Navigation&&) = delete;
private:
	void* soHandle;
	AbstractNavigation* nav;
public:
	std::string navName;
	NavigationInfo navInfo;
public:
	Navigation();
	Navigation(const char* name, const char* soPath = nullptr);
	~Navigation();

	bool load(const char* soPath);
	void unload();
	bool isValid() const;
	AbstractNavigation* newNav(const World* world);
	AbstractNavigation* getNav();
};

#endif
