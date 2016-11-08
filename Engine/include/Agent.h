#pragma once

class Agent
{
	static int nextAgentID;

    // Attribute Container Placeholder

    int groupID;
    const int agentID;

public:
	Agent();

	void setGroupID(int);
	int getGroupID() const;
	int getAgentID() const;
};
