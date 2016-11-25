#include "AgentAttributeBool.h"
using namespace std;


AgentAttributeBool::AgentAttributeBool(const std::string& name, bool defaultValue):
	AgentAttribute(name),value(defaultValue){}

bool AgentAttributeBool::getValue() const {return value;}
void AgentAttributeBool::setValue(bool newValue){value = newValue;}
