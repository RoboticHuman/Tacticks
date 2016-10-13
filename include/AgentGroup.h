#include <vector>

#ifndef AgentGroup_hpp
#define AgentGroup_hpp

class Agent;

class AgentGroup
{
	static int nextGroupID;
public:
	const static int nullGroupID = 0;

private:
	const int groupID;
    std::vector<int> agentIDs;	// TODO: Benchmark vector usage vs unordered_set

public:
	AgentGroup();
	int getGroupID() const;

	void addAgent(int);
	void addAgent(Agent*);
};

#endif
