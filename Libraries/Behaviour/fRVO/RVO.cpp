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
#include <glm/gtx/rotate_vector.hpp>
#include "RVO.h"
using namespace std;
using namespace glm;

#include <iostream>
extern "C"
AbstractBehaviourModule* newBeh(BehaviourModuleData* behData)
{
	return new RVO(behData);
}


extern "C"
BehaviourInfo declareDependencies()
{
	return {BehaviourInfo::Type::Force, {}};
}

RVO::RVO(BehaviourModuleData* behData) : ForcesBehaviourModule(behData){}

bool RVO::init()
{
	radius = dynamic_cast<PassObjectFloat*>(args[3])->getValue();
	clearDirty();
	return true;
}
bool RVO::calculateTau(const Agent& cur, vec3& vTest, float rCur, const Agent& obj, vec3& vObj, float rObj, float& tau)
{
	//RVO Daived Cherry Implementation ??? Not working
	vec3 pCur = dynamic_cast<const AgentAttributeVec3*>(cur.getAttribute("Position"))->getValue(); //- curMeanPos;
	vec3 pObj = dynamic_cast<const AgentAttributeVec3*>(obj.getAttribute("Position"))->getValue(); //- curMeanPos;

	float len_vTest_vObj = glm::length(vTest - vObj);
	float len_pCur_pObj = glm::length(pCur - pObj);

	float a = len_vTest_vObj * len_vTest_vObj; //Probably the same as dot product?
	float b = 2 * len_vTest_vObj * glm::dot(pCur, pObj);
	float c = len_pCur_pObj*len_pCur_pObj - rCur*rObj;

	float t1 = (-b + sqrt(b*b - 4 * a * c)) / (2 * a + 1e-9);
	float t2 = (-b - sqrt(b*b - 4 * a * c)) / (2 * a + 1e-9);

	if(std::max(t1, t2) <= 0) return false;

	//if(std::min(t1, t2) < 0 && std::max(t1, t2) > 0){
	//	return 1e9;
	if(t1 < 0) tau = t2;
	else if(t2 < 0) tau = t1;
	else tau = std::min(t1, t2);

	return true;
}
float RVO::calculateVectorScore(glm::vec3& testVector, glm::vec3& preferedVelocity, const Agent& agent)
{
	float el3shama = dynamic_cast<PassObjectFloat*>(args[4])->getValue(); //i.e. el3'ashama
	float tau = 1e9;
	for(AgentIterator aIt = behData->beginAgent(); aIt != behData->endAgent(); aIt++){
		if(agent.getAgentID() == aIt->getAgentID()) continue;
		vec3 t = behData->getTargetVelocityVector(aIt->getAgentID());
		float temp;
		bool flag = calculateTau(agent, testVector, radius, *aIt, t, radius, temp);
		if(flag)
			tau = std::min(tau, temp);
	}
	float score = el3shama / (tau + 0.001) + glm::length(preferedVelocity - testVector);
	return score;
	//Possible Improvment to have radius and el3'shama as an agent attribute
}
glm::vec3 RVO::simulateAgent(const Agent& agent)
{
	// const AgentAttributeVec3* pos = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Position"));
	// const AgentAttributeVec3* target = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Target"));
	// if(pos == nullptr) return glm::vec3(-1,0,0);
	// if(target == nullptr) return glm::vec3(1,0,0);
	//
	//
	//
	// return glm::normalize(target->getValue() - pos->getValue());
	curMeanPos = vec3(0, 0, 0);
	int agentCount = 0;
	for(AgentIterator aIt = behData->beginAgent(); aIt != behData->endAgent(); aIt++){
		curMeanPos = curMeanPos + dynamic_cast<const AgentAttributeVec3*>(aIt->getAttribute("Position"))->getValue();
		agentCount++;
	}
	curMeanPos /= agentCount * 1.0f;


	glm::vec3 preferedVelocity = behData->getTargetVelocityVector(&agent);
	float rho = dynamic_cast<PassObjectFloat*>(args[0])->getValue();
	int numberOfSamples = dynamic_cast<PassObjectInt*>(args[1])->getValue();
	glm::vec3 agentUpVector = dynamic_cast<PassObjectVec3*>(args[2])->getValue();

	vector<glm::vec3> sampledVectors(numberOfSamples);
	float sampleResolution = 2*rho / numberOfSamples;
	float theta = -rho;
	for(int i=0;i<numberOfSamples;i++, theta+=sampleResolution)
		sampledVectors[i] = glm::rotate(preferedVelocity, theta, agentUpVector);
	float maxScore = calculateVectorScore(preferedVelocity, preferedVelocity, agent);
	vec3 res = preferedVelocity;
	for(auto& sampleVector : sampledVectors)
	{
		float score = calculateVectorScore(sampleVector, preferedVelocity, agent);
		if(score < maxScore){
			maxScore = score;
			res = sampleVector;
		}
	}
	return res;
}
vector<pair<int, glm::vec3> > RVO::simulateGroup(const AgentGroup& agentGroup)
{
	vector<pair<int, glm::vec3> > res;
	for(const int aID : agentGroup.getAgentList())
		res.push_back(make_pair(aID, simulateAgent(*behData->getAgentByID(aID))));
	return res;
}
