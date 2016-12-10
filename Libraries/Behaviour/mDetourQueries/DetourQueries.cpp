#include <Tacticks/ForcesBehaviourModule.h>
#include <Tacticks/Behaviour.h>
#include <Tacticks/BehaviourModuleData.h>
#include <Tacticks/AgentAttributeVec3.h>
#include <Tacticks/Agent.h>
#include <Tacticks/AgentGroup.h>
#include <glm/geometric.hpp>
#include "DetourQueries.h"
#include <iostream>
using namespace std;

#define MAX_PATHSLOT      128 // how many paths we can store
#define MAX_PATHPOLY      256 // max number of polygons in a path
#define MAX_PATHVERT      512 // most verts in a path

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
DetourQueries::~DetourQueries(){cache.clear(); dtFreeNavMeshQuery(navQuery);}

bool DetourQueries::init()
{
	navMesh = static_cast<dtNavMesh*>(NavigationFactory::getNav("NLdtNavMesh").getNav()->getRawData()[0]);
	navQuery = dtAllocNavMeshQuery();
	navQuery->init(navMesh,2048);
	return (navMesh != nullptr);
}

void DetourQueries::findPathToTargetInAgent(const Agent& agent)
{
	const AgentAttributeVec3* pos = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Position"));
	const AgentAttributeVec3* target = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Target"));
	dtStatus status;
	glm::vec3 vec3Pos = pos->getValue();
	float floatPos[] = {vec3Pos.x,vec3Pos.y,vec3Pos.z};
	glm::vec3 vec3Target = target->getValue();
	float floatTarget[] = {vec3Target.x,vec3Target.y,vec3Target.z};
	dtQueryFilter m_filter;
	m_filter.setIncludeFlags(0xffff);
	m_filter.setExcludeFlags(0);
	m_filter.setAreaCost(0, 1.0f) ;
	dtPolyRef startPolyRef,endPolyRef;
	float nearestStartPoint[3];
	float nearestEndPoint[3];
	float extent[]={32.f,32.f,32.f};
	dtPolyRef polyPath[MAX_PATHPOLY];
	vector<float> straightPath(MAX_PATHVERT*3);
	int nPathCount=0;
	int nVertCount=0;
	status=navQuery->findNearestPoly(floatPos,extent,&m_filter,&startPolyRef,nearestStartPoint);
	if((status&DT_FAILURE) || (status&DT_STATUS_DETAIL_MASK)) {cout<<"damn, can't find start poly ref"<<endl;}
	status=navQuery->findNearestPoly(floatTarget,extent,&m_filter,&endPolyRef,nearestEndPoint);
	cout<<nearestEndPoint[0]<<" "<<nearestEndPoint[1]<<" "<<nearestEndPoint[1]<<endl;
	if((status&DT_FAILURE) || (status&DT_STATUS_DETAIL_MASK)) {cout<<"damn, can't find end poly ref"<<endl;}
	status=navQuery->findPath(startPolyRef, endPolyRef, nearestStartPoint, nearestEndPoint, &m_filter, polyPath, &nPathCount, MAX_PATHPOLY);
	if((status&DT_FAILURE) || (status&DT_STATUS_DETAIL_MASK)) {cout<<"damn, can't find path"<<endl;}
	status=navQuery->findStraightPath(nearestStartPoint, nearestEndPoint, polyPath, nPathCount, &straightPath[0], nullptr, nullptr, &nVertCount, MAX_PATHVERT) ;
	if((status&DT_FAILURE) || (status&DT_STATUS_DETAIL_MASK)) {cout<<"damn can't find straight path"<<endl;}
	AgentPathData agentPathData; agentPathData.straightPath=straightPath; agentPathData.currentAgentTarget=vec3Target; agentPathData.currentPathVertexIndex=0;
	cache[agent.getAgentID()]=agentPathData;
}

void  DetourQueries::setPathValidity(bool isValid)
{
	valid = isValid;
}

glm::vec3 DetourQueries::simulateAgent(const Agent& agent)
{
	if(cache.count(agent.getAgentID())==0) findPathToTargetInAgent(agent);
	AgentPathData &agentPathData=cache[agent.getAgentID()];
	if(agentPathData.currentPathVertexIndex>=agentPathData.straightPath.size() || agentPathData.currentAgentTarget!=dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Target"))->getValue()) findPathToTargetInAgent(agent);
	const AgentAttributeVec3* pos = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Position"));
	glm::vec3 agentPos = pos->getValue();
	glm::vec3 intermediateTarget = glm::vec3(agentPathData.straightPath[agentPathData.currentPathVertexIndex],
		agentPathData.straightPath[agentPathData.currentPathVertexIndex+1],
		agentPathData.straightPath[agentPathData.currentPathVertexIndex+2]);
	if(intermediateTarget!=glm::vec3(0,0,0) && glm::distance(agentPos,intermediateTarget)>0.05f) {return intermediateTarget;}
	else{
		agentPathData.currentPathVertexIndex+=3;
	}
	return agentPos;
}
vector<pair<int, glm::vec3> > DetourQueries::simulateGroup(const AgentGroup& agentGroup)
{
	vector<pair<int, glm::vec3> > res;
	for(const int aID : agentGroup.getAgentList())
		res.push_back(make_pair(aID, simulateAgent(*behData->getAgentByID(aID))));
	return res;
}
