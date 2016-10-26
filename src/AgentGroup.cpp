#include "AgentGroup.h"
#include "Agent.h"

int AgentGroup::nextGroupID = nullGroupID + 1;

AgentGroup::AgentGroup() : groupID(nextGroupID++)
{

}

int AgentGroup::getGroupID() const
{
	return groupID;
}

void AgentGroup::addAgent(Agent* agentPtr)
{
	agentIDs.push_back(agentPtr->getAgentID());
	agentPtr->setGroupID(groupID);
}
