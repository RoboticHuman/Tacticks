#include <unordered_map>
#include <glm/vec3.hpp>

#ifndef BehaviourModuleData_hpp
#define BehaviourModuleData_hpp

class Agent;
class AgentGroup;

class BehaviourModuleData
{
	struct PrivateAgent
	{
		Agent* agent;
		glm::vec3 targetPosition;
		glm::vec3 targetVelocity;
	};
public:
	class AgentIterator
	{
		friend BehaviourModuleData;
	private:
		std::unordered_map<int, PrivateAgent>::iterator iterator;

		AgentIterator(const std::unordered_map<int, PrivateAgent>::iterator&);
	public:
		const Agent* operator->() const;
		const Agent& operator*() const;
	};

	class GroupIterator
	{
		friend BehaviourModuleData;
	private:
		std::unordered_map<int, AgentGroup*>::iterator iterator;

		GroupIterator(const std::unordered_map<int, AgentGroup*>::iterator&);
	public:
		const AgentGroup* operator->() const;
		const AgentGroup& operator*() const;
	};

private:
    std::unordered_map<int, PrivateAgent> agents;
    std::unordered_map<int, AgentGroup*> groups;

public:
    // Interface to BM
	void addAgent(Agent*);
	void addGroup(AgentGroup*);

	glm::vec3 getTargetPositionVector(const int) const;
	glm::vec3 getTargetPositionVector(const Agent*) const;
	glm::vec3 getTargetVelocityVector(const int) const;
	glm::vec3 getTargetVelocityVector(const Agent*) const;
	Agent* getAgentByID(int) const;
	AgentGroup* getGroupByID(int) const;

	AgentIterator BeginAgent();
	AgentIterator EndAgent();
	GroupIterator BeginGroup();
	GroupIterator EndGroup();
};

#endif
