#include <string>
#include "AgentAttribute.h"

#pragma once

class AgentAttributeFloat : public AgentAttribute
{
	float value;
	float minValue;
	float maxValue;
public:
	AgentAttributeFloat(const float defaultValue, const float minValue, const float maxValue, const std::string& name="");
	float getValue() const;
	float getMinValue() const;
	float getMaxValue() const;
	void setValue(const float newValue);
};