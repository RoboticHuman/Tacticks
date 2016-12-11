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

class NaiveCollisionAvoidance : public ForcesBehaviourModule
{
	float radius;
	float alpha;
public:
	NaiveCollisionAvoidance(BehaviourModuleData* behData);
	virtual bool init() override;
	virtual glm::vec3 simulateAgent(const Agent& agent) override;
	virtual std::vector<std::pair<int, glm::vec3> > simulateGroup(const AgentGroup& agentGroup) override;
};
