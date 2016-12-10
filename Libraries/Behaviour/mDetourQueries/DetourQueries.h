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
#include <DetourNavMeshBuilder.h>
#include <DetourCommon.h>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/gtx/norm.hpp>

#pragma once

class DetourQueries : public MilestonesBehaviourModule
{
	typedef struct
	{
	   std::vector<float> straightPath;
		 int currentPathVertexIndex;
	   glm::vec3 currentAgentTarget;
	}AgentPathData;

	dtNavMeshQuery* navQuery;
	dtNavMesh* navMesh;
	virtual void findPathToTargetInAgent(const Agent& agent);
	bool valid=false;
	std::unordered_map<int,AgentPathData> cache;
public:
	DetourQueries(BehaviourModuleData* behData);
	~DetourQueries();
	virtual bool init() override;
	void setPathValidity(bool isValid);
	virtual glm::vec3 simulateAgent(const Agent& agent) override;
	virtual std::vector<std::pair<int, glm::vec3> > simulateGroup(const AgentGroup& agentGroup) override;
};
