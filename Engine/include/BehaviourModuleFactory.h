#pragma once

#include <string>
#include <vector>

class AbstractBehaviourModule;
class BehaviourModuleFactory;
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
public:
	static AbstractBehaviourModule* construct(std::string behName, BehaviourModuleData* data);
	static Behaviour getMetaData(std::string behName);
};
