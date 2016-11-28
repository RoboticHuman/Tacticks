#include "AbstractNavigation.h"
#include "PassObject.h"

void AbstractNavigation::setParameters(const std::vector<PassObject*>& args){dirty=true;this->args = args;}
bool AbstractNavigation::isDirty(){return dirty;}
void AbstractNavigation::clearDirty(){dirty = false;}
