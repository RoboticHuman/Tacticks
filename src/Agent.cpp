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

void Agent::setGroupID(int ID)
{
	groupID = ID;
}
int Agent::getGroupID() const
{
	return groupID;
}
int Agent::getAgentID() const
{
	return agentID;
}
