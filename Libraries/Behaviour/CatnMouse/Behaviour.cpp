#include <Tacticks/AbstractBehaviourModule.h>
#include <Tacticks/Behaviour.h>

class CatnMouse : public AbstractBehaviourModule
{
public:
	CatnMouse(BehaviourModuleData* behData) : AbstractBehaviourModule(behData){}
	virtual glm::vec3 simulateAgent(const Agent& agent){
		
	}
	virtual std::vector<std::pair<int, glm::vec3> > simulateGroup(const AgentGroup& agentGroup){

	}
};

extern "C"
AbstractBehaviourModule* newBeh(BehaviourModuleData* behData)
{
	return new CatnMouse(behData);
}


extern "C"
BehaviourInfo declareDependencies()
{
	return {BehaviourInfo::Type::Milestone, {}};
}
