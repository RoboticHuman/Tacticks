#include "AgentAttribute.h"

#pragma once

class AgentAttributeInt : public AgentAttribute
{
	int value;
	int minValue;
	int maxValue;
public:
	AgentAttributeInt(const std::string& name, int defaultValue, int minValue, int maxValue);
	int getValue() const;
	int getMinValue() const;
	int getMaxValue() const;
	void setValue(int newValue);
};