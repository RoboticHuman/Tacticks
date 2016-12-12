#include "AgentAttributeBool.h"
using namespace std;


AgentAttributeBool::AgentAttributeBool(bool defaultValue, const std::string& name):
	AgentAttribute(name),value(defaultValue){}

bool AgentAttributeBool::getValue() const {return value;}
void AgentAttributeBool::setValue(bool newValue){value = newValue;}
