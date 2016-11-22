#include "AgentAttributeBool.h"
using namespace std;


AgentAttributeBool::AgentAttributeBool(string name, bool defaultValue):
	AgentAttribute(name),value(defaultValue){}

bool AgentAttributeBool::getValue(){return value;}
void AgentAttributeBool::setValue(bool newValue){value = newValue;}
