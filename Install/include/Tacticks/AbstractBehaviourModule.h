#ifndef AbstractBehaviourModule_h
#define AbstractBehaviourModule_h

class BehaviourModuleData;

class AbstractBehaviourModule
{
protected:
	BehaviourModuleData* behData;
	AbstractBehaviourModule(BehaviourModuleData* data);

public:
    //virtual void eventX(...) {};
};

#endif
