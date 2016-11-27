#include "AbstractBehaviourModule.h"
#include "PassObject.h"
AbstractBehaviourModule::AbstractBehaviourModule(BehaviourModuleData* data) : behData(data){};
void AbstractBehaviourModule::eventPreSimulate(){};
