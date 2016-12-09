#include <Tacticks/ForcesBehaviourModule.h>
#include <Tacticks/Behaviour.h>
#include <Tacticks/BehaviourModuleData.h>
#include <Tacticks/AgentAttributeVec3.h>
#include <Tacticks/Agent.h>
#include <Tacticks/AgentGroup.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "DetourQueries.h"
#include <DetourNavMeshBuilder.h>
#include <DetourCommon.h>
using namespace std;


extern "C"
AbstractBehaviourModule* newBeh(BehaviourModuleData* behData)
{
	return new DetourQueries(behData);
}


extern "C"
BehaviourInfo declareDependencies()
{
	return {BehaviourInfo::Type::Milestone, {"NLdtNavMesh"}};
}

DetourQueries::DetourQueries(BehaviourModuleData* behData) : MilestonesBehaviourModule(behData){}

bool DetourQueries::init()
{
	navMesh = static_cast<dtNavMesh*>(NavigationFactory::getNav("NLdtNavMesh").getNav()->getRawData()[0]);
	navQuery.init(navMesh,100);
	return (navMesh != nullptr);
}

glm::vec3 DetourQueries::simulateAgent(const Agent& agent)
{
	const AgentAttributeVec3* pos = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Position"));
	const AgentAttributeVec3* target = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Target"));

	glm::vec3 vec3Pos = pos->getValue();
	const float floatPos[3] = {vec3Pos.x,vec3Pos.y,vec3Pos.z};
	glm::vec3 vec3Target = target->getValue();
	const float floatTarget[] = {vec3Target.x,vec3Target.y,vec3Target.z};
	dtQueryFilter m_filter;
	m_filter.setIncludeFlags(0xffff ^ 0x10);
	m_filter.setExcludeFlags(0);
	dtPolyRef* startPolyRef,*endPolyRef;
	float *nearestStartPoint;
	float *nearestEndPoint;
	float extent[]={2.f,4.f,2.f};
	navQuery.findNearestPoly(floatPos,extent,&m_filter,startPolyRef,nearestStartPoint);
	//navQuery.findNearestPoly(&floatTarget,extent,&m_filter,endPolyRef,nearestEndPoint);

	return glm::vec3(1,0,0);

}
vector<pair<int, glm::vec3> > DetourQueries::simulateGroup(const AgentGroup& agentGroup)
{
	vector<pair<int, glm::vec3> > res;
	for(const int aID : agentGroup.getAgentList())
		res.push_back(make_pair(aID, simulateAgent(*behData->getAgentByID(aID))));
	return res;
}
