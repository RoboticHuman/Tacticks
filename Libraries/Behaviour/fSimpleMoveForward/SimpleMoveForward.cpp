#include <Tacticks/ForcesBehaviourModule.h>
#include <Tacticks/Behaviour.h>
#include <Tacticks/BehaviourModuleData.h>
#include <Tacticks/AgentAttributeVec3.h>
#include <Tacticks/Agent.h>
#include <Tacticks/AgentGroup.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "SimpleMoveForward.h"
using namespace std;


extern "C"
AbstractBehaviourModule* newBeh(BehaviourModuleData* behData)
{
	return new SimpleMoveForward(behData);
}


extern "C"
BehaviourInfo declareDependencies()
{
	return {BehaviourInfo::Type::Force, {}};
}

SimpleMoveForward::SimpleMoveForward(BehaviourModuleData* behData) : ForcesBehaviourModule(behData){}

bool SimpleMoveForward::init()
{
	return true;
}

glm::vec3 SimpleMoveForward::simulateAgent(const Agent& agent)
{
	const AgentAttributeVec3* pos = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Position"));
	const AgentAttributeVec3* target = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Target"));
	if(pos == nullptr) return glm::vec3(-1,0,0);
	if(target == nullptr) return glm::vec3(1,0,0);



	return glm::normalize(target->getValue() - pos->getValue());
}
vector<pair<int, glm::vec3> > SimpleMoveForward::simulateGroup(const AgentGroup& agentGroup)
{
	vector<pair<int, glm::vec3> > res;
	for(const int aID : agentGroup.getAgentList())
		res.push_back(make_pair(aID, simulateAgent(*behData->getAgentByID(aID))));
	return res;
}
