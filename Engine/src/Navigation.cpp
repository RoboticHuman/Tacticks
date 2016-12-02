#include "Navigation.h"
#include <cstring>
#include <unistd.h>
#include <dlfcn.h>
#include "AbstractNavigation.h"
using namespace std;

Navigation::Navigation(const char* name, const char* soPath) : navName(name)
{
	soHandle = nav = nullptr;
	if(soPath != nullptr) load(soPath);
}
Navigation::~Navigation()
{
	if(nav != nullptr) delete nav;
	if(soHandle != nullptr) unload();
}

bool Navigation::load(const char* soPath)
{
	if(soPath == nullptr || access(soPath, F_OK | R_OK) == -1) return false;

	soHandle = dlopen(soPath, RTLD_NOW);
	if(soHandle == nullptr) return false;

	typedef NavigationInfo (*declDep_t)();
	declDep_t declDep = (declDep_t)dlsym(soHandle, "declareDependencies");
	if(declDep == nullptr) return false;

	navInfo = move(declDep());
	return true;
}
void Navigation::unload()
{
	if(soHandle != nullptr)
		dlclose(soHandle);
	soHandle = nullptr;
}
bool Navigation::isValid() const
{
	return navName.size() != 0;
}

AbstractNavigation* Navigation::newNav(const World* world)
{
	if(soHandle == nullptr) return nullptr;
	if(nav != nullptr) return nav;

	typedef AbstractNavigation* (*newNav_t)(const World*);
	newNav_t newNav_ptr = (newNav_t)dlsym(soHandle, "newNav");
	if(newNav_ptr == nullptr) return nullptr;

	return nav = newNav_ptr(world);
}
AbstractNavigation* Navigation::getNav()
{
	if(soHandle == nullptr) return nullptr;
	return nav;
}
