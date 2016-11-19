#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <dlfcn.h>
#include "NavigationFactory.h"
using namespace std;

bool Navigation::validity() const
{
	return name != "";
}

const string NavigationFactory::libraryPath = "Libraries/Navigation/";
map<string, void*> NavigationFactory::navSOHandle;

bool NavigationFactory::load(string navName)
{
	//Checks if navigation file exist and have read permission.
	if(access((libraryPath + navName + "/" + navName + ".nav").c_str(), F_OK | R_OK) == -1) return false;

	/*
		TODO: Read file content, build shared object, ... etc.
	*/

	//Loading Shared Object
	void* handle = dlopen((libraryPath + navName + "/" + navName + ".so").c_str(), RTLD_NOW);
	if(handle == nullptr) return false;

	navSOHandle[navName] = handle;
	return true;
}
void NavigationFactory::unload(string navName)
{
	if(navSOHandle.count(navName) == 0) return;
	dlclose(navSOHandle[navName]);
	navSOHandle.erase(navName);
}
AbstractNavigation* NavigationFactory::newNav(std::string navName)
{
	if(navSOHandle.count(navName) == 0) return nullptr;
	void* handle = navSOHandle[navName];

	typedef AbstractNavigation* (*newNav_t)();
	newNav_t newNav = (newNav_t)dlsym(handle, "newNav");
	if(newNav == nullptr) return nullptr;

	return newNav();
}
Navigation NavigationFactory::getMetaData(std::string navName)
{
	/*
	*	TODO: Parsing for the nav files
	*/
	Navigation ret; ret.name = "";

	FILE* navFile;

	//Checks if navigation file exist and have read permission.
	if((navFile = fopen((libraryPath + navName + ".nav").c_str(), "r")) == nullptr) return ret;

	fclose(navFile);
	return ret;
}
