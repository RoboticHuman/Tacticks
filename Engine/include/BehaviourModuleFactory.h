#ifndef BEHAVIOUR_MODULE_FACTORY_H
#define BEHAVIOUR_MODULE_FACTORY_H

#include <string>
#include "Behaviour.h"

class BehaviourModuleFactory
{
	BehaviourModuleFactory() = delete;
	BehaviourModuleFactory(const BehaviourModuleFactory&) = delete;
	BehaviourModuleFactory(BehaviourModuleFactory&&) = delete;
	~BehaviourModuleFactory() = delete;
private:
	static const std::string libraryPath;
public:
	static Behaviour getBeh(std::string behName);
};

#endif
