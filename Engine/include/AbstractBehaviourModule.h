#include <glm/vec3.hpp>
#include <vector>

class Agent;
class AgentGroup;

#pragma once

class BehaviourModuleData;

class AbstractBehaviourModule
{
protected:
	BehaviourModuleData* behData;
	AbstractBehaviourModule(BehaviourModuleData* data);

public:
	virtual ~AbstractBehaviourModule() = default;
	virtual glm::vec3 simulateAgent(const Agent& agent) = 0;
	virtual std::vector<std::pair<int, glm::vec3> > simulateGroup(const AgentGroup& agentGroup) = 0;
	virtual void eventPreSimulate();
    //virtual void eventX(...) {};
};
