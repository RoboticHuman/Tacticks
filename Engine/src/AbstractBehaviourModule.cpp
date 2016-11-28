#include "AbstractBehaviourModule.h"
#include "PassObject.h"
AbstractBehaviourModule::AbstractBehaviourModule(BehaviourModuleData* data) : behData(data){};
void AbstractBehaviourModule::eventPreSimulate(){};
bool AbstractBehaviourModule::isDirty(){return dirty;}
void AbstractBehaviourModule::clearDirty(){dirty = false;}
void AbstractBehaviourModule::setParameters(const std::vector<PassObject*>& args){dirty=true;this->args = args;}
