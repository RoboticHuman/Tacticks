#include <string>
#include "AgentAttribute.h"

#pragma once

class AgentAttributeBool : public AgentAttribute
{
	bool value;
public:
	AgentAttributeBool(bool defaultValue, const std::string& name="");
	bool getValue() const;
	void setValue(bool newValue);
};