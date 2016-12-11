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

#pragma once

class SimpleMoveForward : public ForcesBehaviourModule
{
	float radius;
	float calculateVectorScore(glm::vec3& testVector, glm::vec3& preferedVector, const Agent&agent);
	bool calculateTau(const Agent& cur, glm::vec3& vTest, float rCur, const Agent& obj, glm::vec3& vObj, float rObj, float& tau);
public:
	SimpleMoveForward(BehaviourModuleData* behData);
	virtual bool init() override;
	virtual glm::vec3 simulateAgent(const Agent& agent) override;
	virtual std::vector<std::pair<int, glm::vec3> > simulateGroup(const AgentGroup& agentGroup) override;
};
