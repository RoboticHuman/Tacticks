#include <string>
#include <vector>
#include "AgentAttribute.h"

#pragma once

class AgentAttributeEnum : public AgentAttribute
{
	int value;
	std::vector<std::string> possibleValues;
public:
	AgentAttributeEnum(std::string name, int defaultValue, std::vector<std::string> possibleValues);
	int getValue();
	const std::vector<std::string>& getPossibleValues();
	void setValue(int newValue);
};