#include <string>
#include <vector>
#include "AgentAttribute.h"

#pragma once

class AgentAttributeEnum : public AgentAttribute
{
	int value;
	std::vector<std::string> possibleValues;
public:
	AgentAttributeEnum(int defaultValue, const std::vector<std::string>& possibleValues, const std::string& name="");
	int getValue() const;
	const std::vector<std::string>& getPossibleValues() const;
	void setValue(int newValue);
};