#ifndef BEHAVIOUR_MODULE_FACTORY_H
#define BEHAVIOUR_MODULE_FACTORY_H

#include <string>
#include <vector>
#include <map>

class AbstractBehaviourModule;
class BehaviourModuleData;

struct Behaviour
{
	std::string name;
	enum class Type
	{
		Force,
		Milestone,
		Null	//Used for invalid types.
	} type;
	std::vector<std::string> navDependencies;
public:
	bool validity() const;
};

class BehaviourModuleFactory
{
	BehaviourModuleFactory() = delete;
	BehaviourModuleFactory(const BehaviourModuleFactory&) = delete;
	BehaviourModuleFactory(BehaviourModuleFactory&&) = delete;
	~BehaviourModuleFactory() = delete;
private:
	static const std::string libraryPath;
	static std::map<std::string, void*> behSOHandle;
public:
	static bool load(std::string behName);
	static void unload(std::string behName);
	static AbstractBehaviourModule* newBeh(std::string behName, BehaviourModuleData* data);
	static Behaviour getMetaData(std::string behName);
};

#endif
