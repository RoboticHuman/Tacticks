#include "AgentGroup.h"
#include "Agent.h"
using namespace std;
int AgentGroup::nextGroupID = nullGroupID + 1;

AgentGroup::AgentGroup(int gID) : groupID(gID)
{

}
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
const vector<int>& AgentGroup::getAgentList() const
{
	return agentIDs;
}