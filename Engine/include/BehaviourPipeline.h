#include <vector>
#include "Navigation.h"
#include "Behaviour.h"

#ifndef BehaviourPipeline_hpp
#define BehaviourPipeline_hpp

class ForcesBehaviourModule;
class MilestonesBehaviourModule;

class BehaviourPipeline
{
    std::vector<Behaviour> forcesPipeline;
    std::vector<Behaviour> milestonesPipeline;
public:
	Navigation* addNavigationLibrary(std::string navName);
	Navigation* getNavigationLibrary(std::string navName);
	void removeNavigationLibrary(std::string navName);

    Behaviour* addForcesModule(std::string behName);
    Behaviour* addMilestonesModule(std::string behName);

    bool  deleteForcesModule(unsigned int index);
    bool deleteMilestonesModule(unsigned int index);

    bool incrementForcesModuleIndex(unsigned int originalIndex);
    bool incrementMilestonesModuleIndex(unsigned int originalIndex);

    bool decrementForcesModuleIndex(unsigned int originalIndex);
    bool decrementMilestonesModuleIndex(unsigned int originalIndex);

    bool moveForcesModuleToIndex(unsigned int originalIndex, unsigned int targetIndex);
    bool moveMilestonesModuleToIndex(unsigned int originalIndex, unsigned int targetIndex);

    Behaviour* getForcesModuleAtIndex(unsigned int index);
    Behaviour* getMilestonesModuleAtIndex(unsigned int index);

    // runBehaviourPipeline placeholder


};


#endif
