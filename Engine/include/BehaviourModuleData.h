#include <unordered_map>
#include <glm/vec3.hpp>
#include "AgentGroup.h"

#pragma once

class Agent;
class AgentGroup;
class AgentIterator;
class GroupIterator;
class BehaviourPipeline;

// BehaviourModuleData Prototype
//################################################
class BehaviourModuleData
{
	friend AgentIterator;
	friend GroupIterator;
	friend BehaviourPipeline;
private:
	struct PrivateAgent
	{
		Agent* agent;
		glm::vec3 targetPosition;
		glm::vec3 targetVelocity;
	};

	std::unordered_map<int, Agent> internallyStoredAgents;
    std::unordered_map<int, PrivateAgent> agents;
    std::unordered_map<int, AgentGroup> groups;
    /*
        TODO:
        Add removeGroupByID()
    */
	int addAgent();
	int addGroup();
	bool addExternalAgent(Agent* externalAgent);
	void removeAgentByID(int id);

public:

	glm::vec3 getTargetPositionVector(const int agentID) const;
	glm::vec3 getTargetPositionVector(const Agent* agentPtr) const;
	glm::vec3 getTargetVelocityVector(const int agentID) const;
	glm::vec3 getTargetVelocityVector(const Agent* agentPtr) const;
	const Agent* getAgentByID(int agentID) const;
	const AgentGroup* getGroupByID(int groupID) const;

	AgentIterator beginAgent();
	AgentIterator endAgent();
	GroupIterator beginGroup();
	GroupIterator endGroup();
};
//################################################

// AgentIterator Prototype
//################################################
class AgentIterator
{
	friend BehaviourModuleData;
private:
    std::unordered_map<int, BehaviourModuleData::PrivateAgent>::iterator iterator;

    AgentIterator(const std::unordered_map<int, BehaviourModuleData::PrivateAgent>::iterator&);
public:
    const Agent* operator->() const;
    const Agent& operator*() const;
	AgentIterator& operator++();
    AgentIterator operator++(int);
};
//################################################

// GroupIterator Prototype
//################################################
class GroupIterator
{
	friend BehaviourModuleData;
private:
    std::unordered_map<int, AgentGroup>::iterator iterator;

    GroupIterator(const std::unordered_map<int, AgentGroup>::iterator&);
public:
    const AgentGroup* operator->() const;
    const AgentGroup& operator*() const;
	GroupIterator& operator++();
    GroupIterator operator++(int);
};
//################################################
