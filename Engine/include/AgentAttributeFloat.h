#include <string>
#include "AgentAttribute.h"

#pragma once

class AgentAttributeFloat : public AgentAttribute
{
	float value;
	float minValue;
	float maxValue;
public:
	AgentAttributeFloat(const std::string& name, float defaultValue, float minValue, float maxValue);
	float getValue() const;
	float getMinValue() const;
	float getMaxValue() const;
	void setValue(float newValue);
};