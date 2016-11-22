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
const string BehaviourModuleFactory::libraryPath = "../Libraries/Behaviour/";

AbstractBehaviourModule* BehaviourModuleFactory::construct(std::string behName, BehaviourModuleData* data)
{
	//Checks if behaviour file exist and have read permission.
	if(access((libraryPath + behName + "/" + behName + ".beh").c_str(), F_OK | R_OK) == -1) return nullptr;

	/*
		TODO: Read file content, build shared object, ... etc.
	*/

	//Loading Shared Object
	void* handle = dlopen((libraryPath + behName + "/" + behName + ".so").c_str(), RTLD_NOW);
	if(handle == nullptr) return nullptr;

	typedef AbstractBehaviourModule* (*newBeh_t)(BehaviourModuleData*);
	newBeh_t newBeh = (newBeh_t)dlsym(handle, "newBeh");
	if(newBeh == nullptr) return nullptr;

	/*
		TODO: Proper shared object clean up is required
		dlclose(handle);
	*/

	return newBeh(data);
}

Behaviour BehaviourModuleFactory::getMetaData(std::string behName)
{
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
	return ret;
}
