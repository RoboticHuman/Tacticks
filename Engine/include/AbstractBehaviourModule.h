#pragma once
#include <glm/vec3.hpp>
#include <vector>

class PassObject;
class Agent;
class AgentGroup;

class BehaviourModuleData;

class AbstractBehaviourModule
{
protected:
	BehaviourModuleData* behData;
	AbstractBehaviourModule(BehaviourModuleData* data);
	std::vector<PassObject*> args;
	bool dirty;

public:
	virtual ~AbstractBehaviourModule() = default;
	void setParameters(const std::vector<PassObject*>& args);
	virtual bool init() = 0;
	virtual bool isDirty();
	virtual void clearDirty();
	virtual glm::vec3 simulateAgent(const Agent& agent) = 0;
	virtual std::vector<std::pair<int, glm::vec3> > simulateGroup(const AgentGroup& agentGroup) = 0;
	virtual void eventPreSimulate();
    //virtual void eventX(...) {};
};
