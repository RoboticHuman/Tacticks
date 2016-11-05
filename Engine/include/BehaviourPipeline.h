#include <vector>
#include <ForcesBehaviourModule.h>
#include <MilestonesBehaviourModule.h>

#ifndef BehaviourPipeline_hpp
#define BehaviourPipeline_hpp

class BehaviourPipeline
{
    std::vector<ForcesBehaviourModule*> forcesPipeline;
    std::vector<MilestonesBehaviourModule*> milestonesPipeline;
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
    
    ForcesBehaviourModule* getForcesModuleAtIndex(unsigned int index);
    MilestonesBehaviourModule* getMilestonesModuleAtIndex(unsigned int index);
    
    // runBehaviourPipeline placeholder
    
    
};


#endif