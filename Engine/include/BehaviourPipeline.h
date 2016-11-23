#include <vector>
#include "ForcesBehaviourModule.h"
#include "MilestonesBehaviourModule.h"
#include "BehaviourModuleData.h"
#include "Agent.h"
#include "AgentGroup.h"

#pragma once

class BehaviourPipeline
{
    std::vector<ForcesBehaviourModule*> forcesPipeline;
    std::vector<MilestonesBehaviourModule*> milestonesPipeline;
    BehaviourModuleData behData;
public:
    template<typename t>
    ForcesBehaviourModule* addForcesModule();
    template<typename t>
    MilestonesBehaviourModule* addMilestonesModule();
    
    bool deleteForcesModule(unsigned int index);
    bool deleteMilestonesModule(unsigned int index);
    
    bool incrementForcesModuleIndex(unsigned int originalIndex);
    bool incrementMilestonesModuleIndex(unsigned int originalIndex);
    
    bool decrementForcesModuleIndex(unsigned int originalIndex);
    bool decrementMilestonesModuleIndex(unsigned int originalIndex);
    
    bool moveForcesModuleToIndex(unsigned int originalIndex, unsigned int targetIndex);
    bool moveMilestonesModuleToIndex(unsigned int originalIndex, unsigned int targetIndex);

    int addAgent();
    int addGroup();
    void removeAgentByID(int id);
    const Agent* getAgentByID(int id);
    const AgentGroup* getGroupByID(int id);

    
    ForcesBehaviourModule* getForcesModuleAtIndex(unsigned int index);
    MilestonesBehaviourModule* getMilestonesModuleAtIndex(unsigned int index);
    
    // runBehaviourPipeline placeholder
    
    
};