#include <Tacticks/AbstractBehaviourModule.h>
#include <Tacticks/NavigationFactory.h>
#include <Tacticks/AbstractNavigation.h>
#include <Tacticks/Behaviour.h>
#include <Tacticks/BehaviourModuleData.h>
#include <Tacticks/AgentAttributeVec3.h>
#include <Tacticks/Agent.h>
#include <Tacticks/AgentGroup.h>
using namespace std;
using namespace glm;

class CatnMouse : public AbstractBehaviourModule
{
	AbstractNavigation* nav2d;
public:
	CatnMouse(BehaviourModuleData* behData) : AbstractBehaviourModule(behData){}
	virtual bool init(vector<PassObject> args)
	{
		nav2d = NavigationFactory::getNav("2DNavigator").getNav();
		return nav2d != nullptr;
	}
	virtual vec3 simulateAgent(const Agent& agent)
	{
		const AgentAttributeVec3* pos = dynamic_cast<const AgentAttributeVec3*>(agent.getAttribute("Position"));
		if(pos == nullptr) return vec3();
		vector<PassObject> args;
		args.push_back(PassObject("x", pos->getValue().x));
		args.push_back(PassObject("y", pos->getValue().y));
		vector<PassObject> ret = nav2d->getData("OneLove", args);
		if(ret.size() == 0) return vec3();
		return vec3(ret[0].asArray()[0].asInteger(), ret[0].asArray()[1].asInteger(), 0.0);
	}
	virtual vector<pair<int, vec3>> simulateGroup(const AgentGroup& agentGroup)
	{
		vector<pair<int, vec3>> res;
		for(const int aID : agentGroup.getAgentList())
			res.push_back(make_pair(aID, simulateAgent(*behData->getAgentByID(aID))));
		return res;
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
	return {BehaviourInfo::Type::Milestone, {"2DNavigator"}};
}