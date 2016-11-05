#ifndef BEHAVIOUR_MODULE_FACTORY_H
#define BEHAVIOUR_MODULE_FACTORY_H

#include <string>
#include <vector>

class AbstractBehaviourModule;
class BehaviourModuleFactory;

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
public:
	static AbstractBehaviourModule* construct(std::string behName);
	static Behaviour getMetaData(std::string behName);
};

#endif
