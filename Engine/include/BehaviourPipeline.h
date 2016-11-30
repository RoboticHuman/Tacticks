#include <vector>
#include "BehaviourModuleData.h"
#include "Agent.h"
#include "AgentGroup.h"
#include "Navigation.h"
#include "Behaviour.h"
#include "DependancyManager.h"
#include "AttributeFactory.h"

#pragma once

class ForcesBehaviourModule;
class MilestonesBehaviourModule;

class BehaviourPipeline
{
    BehaviourModuleData behData;
    std::vector<Behaviour> forcesPipeline;
    std::vector<Behaviour> milestonesPipeline;
    AttributeFactory attrFactory;
    DependancyManager depManager;
public:
	Navigation* addNavigationLibrary(std::string navName);
	Navigation* getNavigationLibrary(std::string navName);
	void removeNavigationLibrary(std::string navName);
	void removeNavigationLibrary_force(std::string navName);
	
    BehaviourPipeline();

    // Pipeline Manipulation
    //////////////////////////////////////////////////////////////////////
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
    ///////////////////////////////////////////////////////////////////////


    int addAgent();
    int addGroup();
    void removeAgentByID(int id);
    Agent* getAgentByID(int id);
    AgentGroup* getGroupByID(int id);

    // TODO implement compile properly
    bool compile();
    std::vector<std::pair<int, glm::vec3>> simulate();
};
