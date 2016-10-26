#include <unordered_map>
#include <glm/vec3.hpp>

#ifndef BehaviourModuleData_hpp
#define BehaviourModuleData_hpp

class Agent;
class AgentGroup;

// AgentIterator Prototype
//################################################
class AgentIterator
{
    friend BehaviourModuleData;
private:
    std::unordered_map<int, PrivateAgent>::iterator iterator;
    
    AgentIterator(const std::unordered_map<int, PrivateAgent>::iterator&);
public:
    const Agent* operator->() const;
    const Agent& operator*() const;
    void operator++() const;
};
//################################################

// GroupIterator Prototype
//################################################
class GroupIterator
{
    friend BehaviourModuleData;
private:
    std::unordered_map<int, AgentGroup*>::iterator iterator;
    
    GroupIterator(const std::unordered_map<int, AgentGroup*>::iterator&);
public:
    const AgentGroup* operator->() const;
    const AgentGroup& operator*() const;
    void operator++() const;
};
//################################################

// BehaviourModuleData Prototype
//################################################
class BehaviourModuleData
{
	struct PrivateAgent
	{
		Agent* agent;
		glm::vec3 targetPosition;
		glm::vec3 targetVelocity;
	};

private:
    std::unordered_map<int, PrivateAgent> agents;
    std::unordered_map<int, AgentGroup*> groups;

public:
    /*
        TODO: 
        Move addAgent and addGroup functionality to a place
        not accessible by the Behaviour Modules
    */
	void addAgent(Agent*);
	void addGroup(AgentGroup*);

	glm::vec3 getTargetPositionVector(const int agentID) const;
	glm::vec3 getTargetPositionVector(const Agent* agentPtr) const;
	glm::vec3 getTargetVelocityVector(const int agentID) const;
	glm::vec3 getTargetVelocityVector(const Agent* agentPtr) const;
	const Agent* getAgentByID(int agentID) const;
	const AgentGroup* getGroupByID(int groupID) const;

	AgentIterator firstAgent();
	AgentIterator lastAgent();
	GroupIterator firstGroup();
	GroupIterator lastGroup();
};
//################################################

#endif
