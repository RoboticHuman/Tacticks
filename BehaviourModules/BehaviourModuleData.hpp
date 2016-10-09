#include <unordered_map>
#include <glm/vec3.hpp>
#include "AgentGroup.hpp"
#include "Agent.hpp"

#ifndef BehaviourModuleData_hpp
#define BehaviourModuleData_hpp

class BehaviourModuleData {
    
private:
    struct PrivateAgent {
        Agent* agent;
        glm::vec3 subTarget;
        glm::vec3 subVelocity;
    };
    
    std::unordered_map<int, PrivateAgent> agents;
    std::unordered_map<int, AgentGroup*> groups;
    
public:
    
    // Interface to BM
    
};

#endif