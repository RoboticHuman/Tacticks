#include <string>
#include "AgentAttribute.h"

#pragma once

class AgentAttributeInt : public AgentAttribute
{
	int value;
	int minValue;
	int maxValue;
public:
	AgentAttributeInt(std::string name, int defaultValue, int minValue, int maxValue);
	int getValue();
	int getMinValue();
	int getMaxValue();
	void setValue(int newValue);
};