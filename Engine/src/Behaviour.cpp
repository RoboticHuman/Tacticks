#include "Behaviour.h"
#include <cstring>
#include <unistd.h>
#include <dlfcn.h>
#include "AbstractBehaviourModule.h"
using namespace std;

Behaviour::Behaviour(const char* name, const char* soPath) : behName(name)
{
	soHandle = beh = nullptr;
	behInfo.behType = BehaviourInfo::Type::Null;
	if(soPath != nullptr) load(soPath);
}
Behaviour::Behaviour(Behaviour&& cpy)
{
	soHandle = cpy.soHandle; cpy.soHandle = nullptr;
	beh = cpy.beh; cpy.beh = nullptr;
	behName = cpy.behName;
	behInfo = move(cpy.behInfo);
}
Behaviour::~Behaviour()
{
	if(soHandle != nullptr) unload();
	if(beh != nullptr) delete beh;
}

bool Behaviour::load(const char* soPath)
{
	//Checks if behaviour file exist and have read permission.
	if(soPath == nullptr || access(soPath, F_OK | R_OK) == -1) return false;

	void* soHandle = dlopen(soPath, RTLD_NOW);
	if(soHandle == nullptr) return false;

	typedef BehaviourInfo (*declDep_t)();
	declDep_t declDep = (declDep_t)dlsym(soHandle, "declareDependencies");
	if(declDep == nullptr) return false;

	behInfo = move(declDep());
	return true;
}
void Behaviour::unload()
{
	if(soHandle != nullptr)
		dlclose(soHandle);
	soHandle = nullptr;
}
bool Behaviour::isValid() const
{
	return behName.size() != 0 && behInfo.behType != BehaviourInfo::Type::Null;
}

AbstractBehaviourModule* Behaviour::newBeh(BehaviourModuleData* behData)
{
	if(soHandle == nullptr) return nullptr;
	if(beh != nullptr) return beh;

	typedef AbstractBehaviourModule* (*newBeh_t)(BehaviourModuleData*);
	newBeh_t newBeh_ptr = (newBeh_t)dlsym(soHandle, "newBeh");
	if(newBeh_ptr == nullptr) return nullptr;

	return beh = newBeh_ptr(behData);
}
AbstractBehaviourModule* Behaviour::getBeh()
{
	if(soHandle == nullptr) return nullptr;
	return beh;
}
