#include "BehaviourPipeline.h"
#include <vector>
#include <utility>
#include "ForcesBehaviourModule.h"
#include "MilestonesBehaviourModule.h"
#include "BehaviourModuleFactory.h"
#include "NavigationFactory.h"
using namespace std;
using namespace glm;

BehaviourPipeline::BehaviourPipeline():behData(),attrFactory(behData.agents),depManager(attrFactory)
{

}


Navigation* BehaviourPipeline::addNavigationLibrary(std::string navName)
{
	return &NavigationFactory::getNav(navName);
}
Navigation* BehaviourPipeline::getNavigationLibrary(std::string navName)
{
	return &NavigationFactory::getNav(navName);
}
void BehaviourPipeline::removeNavigationLibrary(std::string navName)
{
	NavigationFactory::rmNav(navName);
}


Behaviour* BehaviourPipeline::addForcesModule(string behName)
{
    forcesPipeline.push_back(BehaviourModuleFactory::getBeh(behName));
	if(forcesPipeline.back().behInfo.behType != BehaviourInfo::Type::Force)
	{
		forcesPipeline.pop_back();
		return nullptr;
	}
    return &forcesPipeline.back();
}

Behaviour* BehaviourPipeline::addMilestonesModule(string behName)
{
	milestonesPipeline.push_back(BehaviourModuleFactory::getBeh(behName));
	if(milestonesPipeline.back().behInfo.behType != BehaviourInfo::Type::Milestone)
	{
		milestonesPipeline.pop_back();
		return nullptr;
	}
    return &milestonesPipeline.back();
}

bool BehaviourPipeline::deleteForcesModule(unsigned int index)
{
    if (index >= forcesPipeline.size())
        return false;
    else {
        forcesPipeline.erase(forcesPipeline.begin()+index);
        return true;
    }
}
bool BehaviourPipeline::deleteMilestonesModule(unsigned int index)
{
    if (index >= milestonesPipeline.size())
        return false;
    else {
        milestonesPipeline.erase(milestonesPipeline.begin()+index);
        return true;
    }
}

bool BehaviourPipeline::incrementForcesModuleIndex(unsigned int originalIndex)
{
    if (originalIndex+1 >= forcesPipeline.size())
        return false;
    else {
        swap(forcesPipeline[originalIndex], forcesPipeline[originalIndex+1]);
        return true;
    }
}
bool BehaviourPipeline::incrementMilestonesModuleIndex(unsigned int originalIndex)
{
    if (originalIndex+1 >= milestonesPipeline.size())
        return false;
    else {
        swap(milestonesPipeline[originalIndex], milestonesPipeline[originalIndex+1]);
        return true;
    }
}

bool BehaviourPipeline::decrementForcesModuleIndex(unsigned int originalIndex)
{
    if (originalIndex == 0 || originalIndex >= forcesPipeline.size())
        return false;
    else {
        swap(forcesPipeline[originalIndex], forcesPipeline[originalIndex-1]);
        return true;
    }
}
bool BehaviourPipeline::decrementMilestonesModuleIndex(unsigned int originalIndex)
{
    if (originalIndex == 0 || originalIndex >= milestonesPipeline.size())
        return false;
    else {
        swap(milestonesPipeline[originalIndex], milestonesPipeline[originalIndex-1]);
        return true;
    }
}

bool BehaviourPipeline::moveForcesModuleToIndex(unsigned int originalIndex, unsigned int targetIndex)
{
    if (originalIndex >= forcesPipeline.size() || targetIndex >= forcesPipeline.size())
        return false;
    else {
        swap(forcesPipeline[originalIndex], forcesPipeline[targetIndex]);
        return true;
    }
}
bool BehaviourPipeline::moveMilestonesModuleToIndex(unsigned int originalIndex, unsigned int targetIndex)
{
    if (originalIndex >= milestonesPipeline.size() || targetIndex >= milestonesPipeline.size())
        return false;
    else {
        swap(milestonesPipeline[originalIndex], milestonesPipeline[targetIndex]);
        return true;
    }
}

int BehaviourPipeline::addAgent() 
{
    int ret = behData.addAgent();
    attrFactory.initializeAgentAttributes(ret);
    return ret;
}

const Agent* BehaviourPipeline::getAgentByID(int id) 
{
    return behData.getAgentByID(id);
}

int BehaviourPipeline::addGroup() 
{
    return behData.addGroup();
}
const AgentGroup* BehaviourPipeline::getGroupByID(int id) 
{
    return behData.getGroupByID(id);
}


Behaviour* BehaviourPipeline::getForcesModuleAtIndex(unsigned int index)
{
    if (index >= forcesPipeline.size())
        return nullptr;
    return &forcesPipeline[index];
}
Behaviour* BehaviourPipeline::getMilestonesModuleAtIndex(unsigned int index)
{
    if (index >= milestonesPipeline.size())
        return nullptr;
    return &milestonesPipeline[index];
}

bool BehaviourPipeline::compile(){return true;}
void BehaviourPipeline::simulate()
{
    for(Behaviour& tBeh : milestonesPipeline){
        AbstractBehaviourModule* beh = tBeh.getBeh();
        beh->eventPreSimulate();
        for(GroupIterator gIt = behData.beginGroup(); gIt != behData.endGroup(); gIt++){
            vector<pair<int, vec3> > ret = beh->simulateGroup(*gIt);
            for(auto res : ret){
                behData.agents[res.first].targetPosition = res.second;
                //behData.agents[res.first].targetVelocity = res.second - *****curPosition*****;
            }
        }
        for(int aID : behData.nullGroup.getAgentList()){
            vec3 res = beh->simulateAgent(behData.agents[aID].agent);
            behData.agents[aID].targetPosition = res;
            //behData.agents[aID].targetVelocity = res - *****curPosition*****;
        }
    }

    for(Behaviour& tBeh : forcesPipeline){
        AbstractBehaviourModule* beh = tBeh.getBeh();
        beh->eventPreSimulate();
        for(GroupIterator gIt = behData.beginGroup(); gIt != behData.endGroup(); gIt++){
            vector<pair<int, vec3> > ret = beh->simulateGroup(*gIt);
            for(auto res : ret)
                behData.agents[res.first].targetVelocity = res.second;
        }
        for(int aID : behData.nullGroup.getAgentList())
            behData.agents[aID].targetVelocity = beh->simulateAgent(behData.agents[aID].agent);
    }
}


