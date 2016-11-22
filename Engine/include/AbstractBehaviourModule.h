#pragma once

class BehaviourModuleData;

class AbstractBehaviourModule
{
protected:
	BehaviourModuleData* behData;
	AbstractBehaviourModule(BehaviourModuleData* data);

public:
    //virtual void eventX(...) {};
};
