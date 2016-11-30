#include <cmath>
#include <map>
#include <string>
#include "AgentAttribute.h"

#pragma once

class BehaviourModuleData;
class AttributeFactory;

class Agent
{
	friend BehaviourModuleData;
	friend AttributeFactory;
	static int nextAgentID;

    std::map<std::string,AgentAttribute*> attributes;

    int groupID;
    const int agentID;

public:
	Agent();

	void setGroupID(int);
	const AgentAttribute* getAttribute(std::string attributeToGet) const;
	AgentAttribute* getAttribute(std::string attributeToGet);
	int getGroupID() const;
	int getAgentID() const;
	~Agent();
};
