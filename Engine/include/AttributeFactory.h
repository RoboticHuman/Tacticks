#include <map>
#include <string>
#include <utility>
#include "AgentAttribute.h"
#include "BehaviourModuleData.h"

#pragma once

class AttributeFactory
{
	std::map<std::string,std::pair<int,AgentAttribute*> > attributeMap;
	std::unordered_map<int, BehaviourModuleData::PrivateAgent>& agents;
public:
	AttributeFactory(std::unordered_map<int, BehaviourModuleData::PrivateAgent>& agentsContainer);
	void addAttribute(const AgentAttribute* attribute);
	void removeAttribute(std::string attributeName);
	void initializeAgentAttributes(int agentID);
};