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

public:
	const static int nullGroupID = 0;

	AgentGroup();
	int getGroupID() const;

	void addAgent(Agent* agentPtr);
};
