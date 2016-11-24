#include <string>
#include "AgentAttribute.h"

#pragma once

class AgentAttributeBool : public AgentAttribute
{
	bool value;
public:
	AgentAttributeBool(const std::string& name, bool defaultValue);
	bool getValue() const;
	void setValue(bool newValue);
};