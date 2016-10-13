#include "Agent.h"
#include "AgentGroup.h"

int Agent::nextAgentID = 0;

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
