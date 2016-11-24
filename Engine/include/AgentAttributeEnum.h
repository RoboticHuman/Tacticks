#include <string>
#include <vector>
#include "AgentAttribute.h"

#pragma once

class AgentAttributeEnum : public AgentAttribute
{
	int value;
	std::vector<std::string> possibleValues;
public:
	AgentAttributeEnum(const std::string& name, int defaultValue, const std::vector<std::string>& possibleValues);
	int getValue() const;
	const std::vector<std::string>& getPossibleValues() const;
	void setValue(int newValue);
};