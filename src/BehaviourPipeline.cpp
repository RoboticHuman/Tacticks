#include "BehaviourPipeline.h"

#include <vector>
#include <utility>
using namespace std;

template<typename t>
ForcesBehaviourModule* BehaviourPipeline::addForcesModule()
{
    forcesPipeline.push_back(new t);
    return forcesPipeline.back();
}

template<typename t>
MilestonesBehaviourModule* BehaviourPipeline::addMilestonesModule()
{
    milestonesPipeline.push_back(new t);
    return milestonesPipeline.back();
}

bool BehaviourPipeline::deleteForcesModule(unsigned int index)
{
    if (index >= forcesPipeline.size())
        return false;
    else {
        delete forcesPipeline[index];
        forcesPipeline.erase(forcesPipeline.begin()+index);
        return true;
    }
}
bool BehaviourPipeline::deleteMilestonesModule(unsigned int index)
{
    if (index >= milestonesPipeline.size())
        return false;
    else {
        delete milestonesPipeline[index];
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
ForcesBehaviourModule* BehaviourPipeline::getForcesModuleAtIndex(unsigned int index)
{
    if (index >= forcesPipeline.size())
        return nullptr;
    return forcesPipeline[index];
}
MilestonesBehaviourModule* BehaviourPipeline::getMilestonesModuleAtIndex(unsigned int index)
{
    if (index >= milestonesPipeline.size())
        return nullptr;
    return milestonesPipeline[index];
}


