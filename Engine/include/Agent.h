#include <cmath>
#include <unordered_map>
#include "AgentAttribute.h"

#pragma once

class BehaviourModuleData;

class Agent
{
	friend BehaviourModuleData;
	static int nextAgentID;

    std::unordered_map<int,AgentAttribute*> attributes;

    int groupID;
    const int agentID;

public:
	Agent();

	void setGroupID(int);
	int getGroupID() const;
	int getAgentID() const;
};
