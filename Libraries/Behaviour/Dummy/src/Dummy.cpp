#include <Tacticks/MilestonesBehaviourModule.h>
#include <Tacticks/BehaviourModuleData.h>
#include <Tacticks/Agent.h>
#include <iostream>
using namespace std;

class Dummy : public MilestonesBehaviourModule{
public:
	Dummy(BehaviourModuleData* ptr) : MilestonesBehaviourModule(ptr){
		cout << "Dummy was constructed" << endl;
	}

	void event1(){
		cout << "Dummy::event1" << endl;
	}
	void event2(){
		cout << "Dummy::event2" << endl;
		AgentIterator it = behData->beginAgent();
		cout << "Dummy:: AgentID " << it->getAgentID() << endl;
	}
};

extern "C"
AbstractBehaviourModule* newBeh(BehaviourModuleData* ptr){
	cout << "Dummy__newBeh" << endl;
	return new Dummy(ptr);
}
