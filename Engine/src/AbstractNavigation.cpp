#include "AbstractNavigation.h"
#include "PassObject.h"
#include "World.h"

AbstractNavigation::AbstractNavigation(const World* world) : world(world), dirty(true){}
void AbstractNavigation::setParameters(const std::vector<PassObject*>& args){dirty=true;this->args = args;}
bool AbstractNavigation::isDirty(){return dirty;}
void AbstractNavigation::clearDirty(){dirty = false;}
void AbstractNavigation::constructDebugMesh(){}
