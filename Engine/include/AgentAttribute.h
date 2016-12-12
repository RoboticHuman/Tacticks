#include <string>

#pragma once

class AgentAttribute
{
private:
	static int nextAttributeID;
	const int attributeID;
	std::string name;
public:
	AgentAttribute(const std::string&);
	int getAttributeID() const;
	std::string getName() const;
	virtual ~AgentAttribute() = default;
};