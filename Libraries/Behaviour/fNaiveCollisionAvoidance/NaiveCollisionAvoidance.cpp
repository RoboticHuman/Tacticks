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

	float cnt = 0;
	vec3 avgSteer = vec3(0, 0, 0);
	for(AgentIterator aIt = behData->beginAgent(); aIt != behData->endAgent(); aIt++){
		if(agent.getAgentID() == aIt->getAgentID()) continue;
		vec3 targetPos = dynamic_cast<const AgentAttributeVec3*>(aIt->getAttribute("Position"))->getValue();

		vec3 distVec = targetPos - agentPos;
		distVec.y = 0;
		float dist = glm::length(distVec);

		if(dist > radius) continue;	//Far enough for collision to happen

		vec3 distVec_norm = glm::normalize(distVec);	//Assuming target and agent are never in the same corrdinate
		distVec_norm /= dist;
		avgSteer += distVec_norm * alpha;
		cnt += 1.0;
	}
	if(cnt > 0)
		agentVel -= avgSteer / cnt;
	return agentVel;
}
vector<pair<int, glm::vec3> > NaiveCollisionAvoidance::simulateGroup(const AgentGroup& agentGroup)
{
	vector<pair<int, glm::vec3> > res;
	for(const int aID : agentGroup.getAgentList())
		res.push_back(make_pair(aID, simulateAgent(*behData->getAgentByID(aID))));
	return res;
}
