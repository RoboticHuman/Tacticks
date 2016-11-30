#include "BehaviourModuleData.h"
#include "Agent.h"
#include "AgentGroup.h"
using namespace std;


// AgentIterator Implementation
//################################################
AgentIterator::AgentIterator(const std::unordered_map<int, BehaviourModuleData::PrivateAgent>::iterator& it) : iterator(it){}

const Agent* AgentIterator::operator->() const
{
	return &iterator->second.agent;
}
const Agent& AgentIterator::operator*() const
{
	return iterator->second.agent;
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
bool AgentIterator::operator==(const AgentIterator& val) const
{
	return iterator == val.iterator;
}
bool AgentIterator::operator!=(const AgentIterator& val) const
{
	return iterator != val.iterator;
}
//#################################################

// GroupIterator Implementation
//#################################################
GroupIterator::GroupIterator(const std::unordered_map<int, AgentGroup>::iterator& it) : iterator(it){}

const AgentGroup* GroupIterator::operator->() const
{
	return &iterator->second;
}
const AgentGroup& GroupIterator::operator*() const
{
	return iterator->second;
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
bool GroupIterator::operator==(const GroupIterator & val) const
{
	return iterator == val.iterator;
}
bool GroupIterator::operator!=(const GroupIterator& val) const
{
	return iterator != val.iterator;
}

//#################################################

// BehaviourModuleData Implementation
//#################################################
BehaviourModuleData::BehaviourModuleData() : nullGroup(AgentGroup::nullGroupID)
{

}

int BehaviourModuleData::addAgent()
{
	int agentID = Agent::nextAgentID;
	agents.insert({agentID,PrivateAgent()});
	nullGroup.addAgent(&(agents[agentID].agent));
	return agentID;
}

int BehaviourModuleData::addGroup()
{
	groups.insert({AgentGroup::nextGroupID,AgentGroup()});
	return AgentGroup::nextGroupID-1;
}
void BehaviourModuleData::removeAgentByID(int id)
{
	agents.erase(id);
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
const Agent* BehaviourModuleData::getAgentByID(int agentID) const
{
	return &agents.at(agentID).agent;
}
const AgentGroup* BehaviourModuleData::getGroupByID(int groupID) const
{
	return &groups.at(groupID);
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
