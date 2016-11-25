#pragma once
#include <string>
#include "Model.h"

class DrawableAgent
{
    Model agentModel;
    int agentID;
public:
    DrawableAgent(std::string pathToModel,int agentID);
    Model& getAgentModel();
    int getAgentID();
};
