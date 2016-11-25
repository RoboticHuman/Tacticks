#include "DrawableAgent.h"



DrawableAgent::DrawableAgent(std::string pathToModel,int agentID):agentModel(pathToModel),agentID(agentID){
}

Model& DrawableAgent::getAgentModel(){
    return agentModel;
}

int DrawableAgent::getAgentID(){
    return agentID;
}
