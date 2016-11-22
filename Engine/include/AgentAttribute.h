#include <string>

#pragma once

class AgentAttribute
{
private:
	static int nextAttributeID;
	const int attributeID;
public:
	const std::string name;
	AgentAttribute(std::string);
	int getAttributeID();
	std::string getName();
};