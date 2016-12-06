#include "DrawableAgent.h"



DrawableAgent::DrawableAgent(std::string pathToModel,int agentID):agentModel(pathToModel),drawableAgentModel(&agentModel),agentID(agentID){
}

Model& DrawableAgent::getAgentModel(){
    return agentModel;
}
DrawableModel& DrawableAgent::getAgentDrawableModel(){
    return drawableAgentModel;
}

int DrawableAgent::getAgentID(){
    return agentID;
}
