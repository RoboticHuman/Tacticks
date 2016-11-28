#include <unordered_map>
#include <glm/vec3.hpp>
#include "Agent.h"
#include "AgentGroup.h"

#pragma once

class Agent;
class AgentGroup;
class AgentIterator;
class GroupIterator;
class BehaviourPipeline;
class AttributeFactory;

// BehaviourModuleData Prototype
//################################################
class BehaviourModuleData
{
	friend AgentIterator;
	friend GroupIterator;
	friend BehaviourPipeline;
	friend AttributeFactory;
private:
	struct PrivateAgent
	{
		Agent agent;
		glm::vec3 targetPosition;
		glm::vec3 targetVelocity;
	};

    std::unordered_map<int, PrivateAgent> agents;
    AgentGroup nullGroup;
    std::unordered_map<int, AgentGroup> groups;
    /*
        TODO:
        Add removeGroupByID()
    */
	int addAgent();
	int addGroup();
	void removeAgentByID(int id);

public:
	BehaviourModuleData();
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
	AgentIterator(const AgentIterator&) = default;
	AgentIterator(AgentIterator&&) = default;
	~AgentIterator() = default;
    const Agent* operator->() const;
    const Agent& operator*() const;
	AgentIterator& operator++();
    AgentIterator operator++(int);
    bool operator==(const AgentIterator& val) const;
    bool operator!=(const AgentIterator& val) const;
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
	GroupIterator(const GroupIterator&) = default;
	GroupIterator(GroupIterator&&) = default;
	~GroupIterator() = default;
    const AgentGroup* operator->() const;
    const AgentGroup& operator*() const;
	GroupIterator& operator++();
    GroupIterator operator++(int);
    bool operator==(const GroupIterator& val) const;
    bool operator!=(const GroupIterator& val) const;
};
//################################################
