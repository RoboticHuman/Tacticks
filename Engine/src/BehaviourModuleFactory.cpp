#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <dlfcn.h>
#include "BehaviourModuleFactory.h"
using namespace std;

//Behaviour Implementation
bool Behaviour::validity() const
{
	return name.size() != 0 && type != Type::Null;
}

//BehaviourModuleFactory Implementation:
const string BehaviourModuleFactory::libraryPath = "Libraries/Behaviour/";
map<string, void*> BehaviourModuleFactory::behSOHandle;

bool BehaviourModuleFactory::load(string behName)
{
	//Checks if behaviour file exist and have read permission.
	if(access((libraryPath + behName + "/" + behName + ".beh").c_str(), F_OK | R_OK) == -1) return false;

	/*
		TODO: Read file content, build shared object, ... etc.
	*/

	//Loading Shared Object
	void* handle = dlopen((libraryPath + behName + "/" + behName + ".so").c_str(), RTLD_NOW);
	if(handle == nullptr) return false;

	behSOHandle[behName] = handle;
	return true;
}
void BehaviourModuleFactory::unload(string behName)
{
	if(behSOHandle.count(behName) == 0) return;
	dlclose(behSOHandle[behName]);
	behSOHandle.erase(behName);
}
AbstractBehaviourModule* BehaviourModuleFactory::newBeh(std::string behName, BehaviourModuleData* behData)
{
	if(behSOHandle.count(behName) == 0) return nullptr;
	void* handle = behSOHandle[behName];

	typedef AbstractBehaviourModule* (*newBeh_t)(BehaviourModuleData*);
	newBeh_t newBeh = (newBeh_t)dlsym(handle, "newBeh");
	if(newBeh == nullptr) return nullptr;

	return newBeh(behData);
}

Behaviour BehaviourModuleFactory::getMetaData(std::string behName)
{
	/*
	*	TODO: Proper Parsing for the beh files
	*/
	//Constructs an invalid Behaviour
	Behaviour ret; ret.type = Behaviour::Type::Null;

	char buf[1000];
	FILE* behFile;

	//Checks if behaviour file exist and have read permission.
	if((behFile = fopen((libraryPath + behName + ".beh").c_str(), "r")) == nullptr) return ret;

	//For now Assuming no whitespaces.

	//Name:
	fscanf(behFile, "%s\n", buf);
	ret.name = buf;

	//Type:
	fscanf(behFile, "%s\n", buf);
	if(strcmp(buf, "Milestone") == 0) ret.type = Behaviour::Type::Milestone;
	else if(strcmp(buf, "Force") == 0) ret.type = Behaviour::Type::Force;
	else ret.type = Behaviour::Type::Null;


	//Navigation Dependencies
	while(fscanf(behFile, "%[^;\n]%*[;\n]", buf) != EOF)
		ret.navDependencies.push_back(string(buf));

	fclose(behFile);
	return ret;
}
