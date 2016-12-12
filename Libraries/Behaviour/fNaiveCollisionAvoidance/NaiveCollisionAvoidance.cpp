#include <Tacticks/ForcesBehaviourModule.h>
#include <Tacticks/Behaviour.h>
#include <Tacticks/BehaviourModuleData.h>
#include <Tacticks/AgentAttributeVec3.h>
#include <Tacticks/PassObjectVec3.h>
#include <Tacticks/PassObjectInt.h>
#include <Tacticks/PassObjectFloat.h>
#include <Tacticks/Agent.h>
#include <Tacticks/AgentGroup.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "NaiveCollisionAvoidance.h"
using namespace std;
using namespace glm;

#include <iostream>
extern "C"
AbstractBehaviourModule* newBeh(BehaviourModuleData* behData)
{
	return new NaiveCollisionAvoidance(behData);
}


extern "C"
BehaviourInfo declareDependencies()
{
	return {BehaviourInfo::Type::Force, {}};
}

NaiveCollisionAvoidance::NaiveCollisionAvoidance(BehaviourModuleData* behData) : ForcesBehaviourModule(behData){}

bool NaiveCollisionAvoidance::init()
{
	radius = dynamic_cast<PassObjectFloat*>(args[0])->getValue();
	alpha = dynamic_cast<PassObjectFloat*>(args[1])->getValue();

	clearDirty();
	return true;
}

glm::vec3 NaiveCollisionAvoidance::simulateAgent(const Agent& agent)
{
	vec3 agentPos = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Position"))->getValue();
	vec3 agentVel = behData->getTargetVelocityVector(&agent);

	int count = 0;
	glm::vec3 change(0,0,0);

	for(AgentIterator aIt = behData->beginAgent(); aIt != behData->endAgent(); aIt++){
		if(agent.getAgentID() == aIt->getAgentID()) continue;
		vec3 targetPos = dynamic_cast<const AgentAttributeVec3*>(aIt->getAttribute("Position"))->getValue();

		vec3 distVec = targetPos - agentPos;
		distVec.y = 0;
		float dist = glm::length(distVec);

		if(dist > radius) continue;	// Close enough for collision to happen
		change += (distVec / dist) * alpha;
		count ++;
	}

	agentVel -= change;

	if (glm::length(agentVel)==0) return glm::vec3(0,0,0);
	else return (glm::normalize(agentVel) * 0.06f); // glm::normalize(agentVel) * 0.07f;
}
vector<pair<int, glm::vec3> > NaiveCollisionAvoidance::simulateGroup(const AgentGroup& agentGroup)
{
	vector<pair<int, glm::vec3> > res;
	for(const int aID : agentGroup.getAgentList())
		res.push_back(make_pair(aID, simulateAgent(*behData->getAgentByID(aID))));
	return res;
}
