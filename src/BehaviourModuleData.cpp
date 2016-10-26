#include "BehaviourModuleData.h"
#include "Agent.h"
#include "AgentGroup.h"


// AgentIterator Implementation
//################################################
AgentIterator::AgentIterator(const std::unordered_map<int, BehaviourModuleData::PrivateAgent>::iterator& it) : iterator(it){}

const Agent* AgentIterator::operator->() const
{
	return iterator->second.agent;
}
const Agent& AgentIterator::operator*() const
{
	return *(iterator->second.agent);
}
AgentIterator& AgentIterator::operator++()
{
	++iterator;
    return *this;
}
AgentIterator AgentIterator::operator++(int)
{
	AgentIterator ret = *this;
	++iterator;
    return ret;
}
//#################################################

// GroupIterator Implementation
//#################################################
GroupIterator::GroupIterator(const std::unordered_map<int, AgentGroup*>::iterator& it) : iterator(it){}

const AgentGroup* GroupIterator::operator->() const
{
	return iterator->second;
}
const AgentGroup& GroupIterator::operator*() const
{
	return *(iterator->second);
}
GroupIterator& GroupIterator::operator++()
{
	++iterator;
    return *this;
}
GroupIterator GroupIterator::operator++(int)
{
	GroupIterator ret = *this;
	++iterator;
    return ret;
}
//#################################################

// BehaviourModuleData Implementation
//#################################################
void BehaviourModuleData::addAgent(Agent* agentPtr){
	PrivateAgent& ref = agents[agentPtr->getAgentID()];
	ref.agent = agentPtr;
    /*
        TODO:
        Add the following functionality as soon as the targetPosition
        is available in the agent class
    */
	//ref.targetPosition = agent->globalTargetPosition();
	//ref.targetVelocity = agent->position() - ref.targetPosition;
}
void BehaviourModuleData::addGroup(AgentGroup* group)
{
	groups[group->getGroupID()] = group;
}

glm::vec3 BehaviourModuleData::getTargetPositionVector(const int agentID) const
{
	return agents.at(agentID).targetPosition;
}
glm::vec3 BehaviourModuleData::getTargetPositionVector(const Agent* agentPtr) const
{
	return agents.at(agentPtr->getAgentID()).targetPosition;
}
glm::vec3 BehaviourModuleData::getTargetVelocityVector(const int agentID) const
{
	return agents.at(agentID).targetVelocity;
}
glm::vec3 BehaviourModuleData::getTargetVelocityVector(const Agent* agentPtr) const
{
	return agents.at(agentPtr->getAgentID()).targetVelocity;
}
const Agent * BehaviourModuleData::getAgentByID(int agentID) const
{
	return agents.at(agentID).agent;
}
const AgentGroup * BehaviourModuleData::getGroupByID(int groupID) const
{
	return groups.at(groupID);
}
AgentIterator BehaviourModuleData::beginAgent()
{
	return AgentIterator(agents.begin());
}
AgentIterator BehaviourModuleData::endAgent()
{
	return AgentIterator(agents.end());
}
GroupIterator BehaviourModuleData::beginGroup()
{
	return GroupIterator(groups.begin());
}
GroupIterator BehaviourModuleData::endGroup()
{
	return GroupIterator(groups.end());
}
//#################################################
