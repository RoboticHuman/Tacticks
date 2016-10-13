#include "BehaviourModuleData.h"
#include "Agent.h"
#include "AgentGroup.h"

BehaviourModuleData::AgentIterator::AgentIterator(const std::unordered_map<int, PrivateAgent>::iterator& it) : iterator(it)
{

}
const Agent* BehaviourModuleData::AgentIterator::operator->() const
{
	return iterator->second.agent;
}
const Agent& BehaviourModuleData::AgentIterator::operator*() const
{
	return *(iterator->second.agent);
}


BehaviourModuleData::GroupIterator::GroupIterator(const std::unordered_map<int, AgentGroup*>::iterator& it) : iterator(it)
{

}
const AgentGroup* BehaviourModuleData::GroupIterator::operator->() const
{
	return iterator->second;
}
const AgentGroup& BehaviourModuleData::GroupIterator::operator*() const
{
	return *(iterator->second);
}


void BehaviourModuleData::addAgent(Agent* agent){
	PrivateAgent& ref = agents[agent->getAgentID()];
	ref.agent = agent;
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
glm::vec3 BehaviourModuleData::getTargetPositionVector(const Agent* agent) const
{
	return agents.at(agent->getAgentID()).targetPosition;
}
glm::vec3 BehaviourModuleData::getTargetVelocityVector(const int agentID) const
{
	return agents.at(agentID).targetVelocity;
}
glm::vec3 BehaviourModuleData::getTargetVelocityVector(const Agent* agent) const
{
	return agents.at(agent->getAgentID()).targetVelocity;
}
Agent* BehaviourModuleData::getAgentByID(int agentID) const
{
	return agents.at(agentID).agent;
}
AgentGroup* BehaviourModuleData::getGroupByID(int groupID) const
{
	return groups.at(groupID);
}

BehaviourModuleData::AgentIterator BehaviourModuleData::BeginAgent()
{
	return AgentIterator(agents.begin());
}
BehaviourModuleData::AgentIterator BehaviourModuleData::EndAgent()
{
	return AgentIterator(agents.end());
}
BehaviourModuleData::GroupIterator BehaviourModuleData::BeginGroup()
{
	return GroupIterator(groups.begin());
}
BehaviourModuleData::GroupIterator BehaviourModuleData::EndGroup()
{
	return GroupIterator(groups.end());
}
