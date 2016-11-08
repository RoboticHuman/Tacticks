#include <vector>

#pragma once

class Agent;

class AgentGroup
{
	static int nextGroupID;
public:
	const static int nullGroupID = 0;

private:
	const int groupID;
    /* 
        TODO: Benchmark vector usage vs unordered_set
     */
    std::vector<int> agentIDs;

public:
	AgentGroup();
	int getGroupID() const;

	void addAgent(Agent* agentPtr);
};
