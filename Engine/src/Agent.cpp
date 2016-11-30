#include "Agent.h"
#include "AgentGroup.h"

int Agent::nextAgentID = 0;

/*
    TODO:
    Find a proper way of generating agentIDs so as to minimize
    their conflicts in the hash table
*/
Agent::Agent() : agentID(nextAgentID++), groupID(AgentGroup::nullGroupID)
{

}

const AgentAttribute* Agent::getAttribute(std::string attributeToGet) const
{
	// TODO:
	// Add error handling for if string not found
	return attributes.find(attributeToGet)->second;
}
AgentAttribute* Agent::getAttribute(std::string attributeToGet)
{
	// TODO:
	// Add error handling for if string not found
	return attributes.find(attributeToGet)->second;
}


int Agent::getGroupID() const
{
	return groupID;
}
int Agent::getAgentID() const
{
	return agentID;
}
void Agent::setGroupID(int ID)
{
	groupID = ID;
}
Agent::~Agent()
{
	for (auto& attr : attributes) {
		delete attr.second;
	}
}
