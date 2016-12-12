#include "AgentAttribute.h"

#pragma once

class AgentAttributeInt : public AgentAttribute
{
	int value;
	int minValue;
	int maxValue;
public:
	AgentAttributeInt(const int defaultValue, const int minValue, const int maxValue, const std::string& name="");
	int getValue() const;
	int getMinValue() const;
	int getMaxValue() const;
	void setValue(const int newValue);
};