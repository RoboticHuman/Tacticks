#pragma once
#include <string>
#include <Tacticks/Model.h>
#include "DrawableModel.h"

class DrawableAgent
{
    Model agentModel;
    DrawableModel drawableAgentModel;
    int agentID;
public:
    DrawableAgent(std::string pathToModel,int agentID);
    Model& getAgentModel();
    DrawableModel& getAgentDrawableModel();
    int getAgentID();
};
