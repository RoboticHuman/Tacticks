#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <vector>
#include <string>
class AbstractNavigation;

struct NavigationInfo
{
	std::vector<std::string> navDependencies;
};

class Navigation
{
	Navigation() = delete;
	Navigation(const Navigation&) = delete;
	Navigation(Navigation&&) = delete;
private:
	void* soHandle;
	AbstractNavigation* nav;
public:
	std::string navName;
	NavigationInfo navInfo;
public:
	Navigation(const char* name, const char* soPath = nullptr);
	~Navigation();

	bool load(const char* soPath);
	void unload();
	bool isValid() const;
	AbstractNavigation* newNav();
	AbstractNavigation* getNav();
};

#endif