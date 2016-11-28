#pragma once
#include <glm/vec3.hpp>
#include <vector>

class PassObject;
class Agent;
class AgentGroup;

class BehaviourModuleData;

class AbstractBehaviourModule
{
	void setParameters(const std::vector<PassObject*>& args);
protected:
	BehaviourModuleData* behData;
	AbstractBehaviourModule(BehaviourModuleData* data);
	std::vector<PassObject*> args;
	bool dirty=true;

public:
	virtual ~AbstractBehaviourModule() = default;
	virtual bool init() = 0;
	virtual bool IsDirty();
	virtual void clearDirty();
	virtual glm::vec3 simulateAgent(const Agent& agent) = 0;
	virtual std::vector<std::pair<int, glm::vec3> > simulateGroup(const AgentGroup& agentGroup) = 0;
	virtual void eventPreSimulate();
    //virtual void eventX(...) {};
};
