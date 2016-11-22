#include <string>
#include "AgentAttribute.h"

#pragma once

class AgentAttributeFloat : public AgentAttribute
{
	float value;
	float minValue;
	float maxValue;
public:
	AgentAttributeFloat(std::string name, float defaultValue, float minValue, float maxValue);
	float getValue();
	float getMinValue();
	float getMaxValue();
	void setValue(float newValue);
};