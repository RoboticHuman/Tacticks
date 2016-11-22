#include <string>
#include "AgentAttribute.h"

#pragma once

class AgentAttributeBool : public AgentAttribute
{
	bool value;
public:
	AgentAttributeBool(std::string name, bool defaultValue);
	bool getValue();
	void setValue(bool newValue);
};