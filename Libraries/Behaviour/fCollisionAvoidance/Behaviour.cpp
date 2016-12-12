#include <Tacticks/ForcesBehaviourModule.h>
#include <Tacticks/NavigationFactory.h>
#include <Tacticks/AbstractNavigation.h>
#include <Tacticks/Behaviour.h>
#include <Tacticks/BehaviourModuleData.h>
#include <Tacticks/AgentAttributeVec3.h>
#include <Tacticks/Agent.h>
#include <Tacticks/AgentGroup.h>
#include <Tacticks/PassObject.h>
#include <Tacticks/PassObjectInt.h>
#include <Tacticks/PassObjectArray.h>
#include <Tacticks/PassObjectVec3.h>
#include <Tacticks/PassObjectFloat.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
using namespace std;
using namespace glm;

class CollisionAvoidance : public ForcesBehaviourModule
{

public:
	CollisionAvoidance(BehaviourModuleData* behData) : ForcesBehaviourModule(behData){}
	virtual bool init()
	{
		return true;
	}
	virtual vec3 simulateAgent(const Agent& agent)
	{
		cout << "Called" << endl;
		float maxAcc = dynamic_cast<PassObjectFloat*>(args[0])->getValue();
		float radius = dynamic_cast<PassObjectFloat*>(args[1])->getValue();

		float dist;

		float shortestTime = 1e9;
		float firstMinSeparation;
		const Agent* firstTarget = nullptr;
		float firstDistance;
		vec3 firstRelativePos;
		vec3 firstRelativeVel;

		vec3 agentPos = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Position"))->getValue(); //- curMeanPos;
		vec3 agentVel = behData->getTargetVelocityVector(&agent);
		cout << "agentVel" << glm::to_string(agentVel) << endl;
		for(AgentIterator aIt = behData->beginAgent(); aIt != behData->endAgent(); aIt++){
			if(agent.getAgentID() == aIt->getAgentID()) continue;
			vec3 targetPos = dynamic_cast<const AgentAttributeVec3*>(aIt->getAttribute("Position"))->getValue(); //- curMeanPos;
			vec3 targetVel = behData->getTargetVelocityVector(aIt->getAgentID());
			vec3 relativePos = targetPos - agentPos;
			vec3 relativeVel = targetVel - agentVel;
			float relativeSpeed = glm::length(relativeVel);
			float timeToCollision = glm::dot(relativePos, relativeVel) / (relativeSpeed * relativeSpeed);

			dist = glm::length(relativePos);
			float minSepration = dist - relativeSpeed * shortestTime;

			if(minSepration > 2 * radius) continue;
			cout << timeToCollision << ' ' << shortestTime << endl;
			if(timeToCollision > 0 && timeToCollision < shortestTime){
				shortestTime = timeToCollision;
				firstTarget = &(*aIt);
				firstMinSeparation = minSepration;
				firstDistance = dist;
				firstRelativePos = relativePos;
				firstRelativeVel = relativeVel;
			}
		}
		cout << firstTarget << endl;
		if(firstTarget == nullptr) return agentVel;

		vec3 relativePos;
		if(firstMinSeparation <= 0 || dist < 2*radius){
			vec3 firstTargetPos = dynamic_cast<const AgentAttributeVec3*>(firstTarget->getAttribute("Position"))->getValue(); //- curMeanPos;
			relativePos = firstTargetPos - agentPos;
		}
		else{
			relativePos = firstRelativePos + firstRelativeVel * shortestTime;
		}

		vec3 relativePosNorm = glm::normalize(relativePos);
		if(relativePosNorm.x != relativePosNorm.x) cout << "NAN" << glm::to_string(relativePosNorm) << endl;
		vec3 steering = relativePos * maxAcc;
		return agentVel + steering;
	}
	virtual vector<pair<int, vec3>> simulateGroup(const AgentGroup& agentGroup)
	{
		vector<pair<int, vec3>> res;
		for(const int aID : agentGroup.getAgentList())
			res.push_back(make_pair(aID, simulateAgent(*behData->getAgentByID(aID))));
		return res;
	}
};

extern "C"
AbstractBehaviourModule* newBeh(BehaviourModuleData* behData)
{
	return new CollisionAvoidance(behData);
}


extern "C"
BehaviourInfo declareDependencies()
{
	return {BehaviourInfo::Type::Force, {}};
}
