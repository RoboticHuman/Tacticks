#include <Tacticks/ForcesBehaviourModule.h>
#include <Tacticks/NavigationFactory.h>
#include <Tacticks/AbstractNavigation.h>
#include <Tacticks/Behaviour.h>
#include <Tacticks/BehaviourModuleData.h>
#include <Tacticks/MilestonesBehaviourModule.h>
#include <Tacticks/AgentAttributeVec3.h>
#include <Tacticks/Agent.h>
#include <Tacticks/AgentGroup.h>
#include <DetourNavMeshQuery.h>
#include <DetourNavMesh.h>


#pragma once

class DetourQueries : public MilestonesBehaviourModule
{
	dtNavMeshQuery navQuery;
	dtNavMesh* navMesh;
public:
	DetourQueries(BehaviourModuleData* behData);
	virtual bool init() override;
	virtual glm::vec3 simulateAgent(const Agent& agent) override;
	virtual std::vector<std::pair<int, glm::vec3> > simulateGroup(const AgentGroup& agentGroup) override;
};
