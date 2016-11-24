#include <vector>

#pragma once

class Agent;
class BehaviourModuleData;

class AgentGroup
{
	friend BehaviourModuleData;
	static int nextGroupID;

private:
	const int groupID;
    /* 
        TODO: Benchmark vector usage vs unordered_set
     */
    std::vector<int> agentIDs;

    AgentGroup(int gID);
public:
	const static int nullGroupID = -1;

	AgentGroup();
	int getGroupID() const;

	void addAgent(Agent* agentPtr);
	const std::vector<int>& getAgentList() const;
};
