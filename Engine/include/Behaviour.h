#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <string>
#include <vector>

class AbstractBehaviourModule;
class BehaviourModuleData;

struct BehaviourInfo
{
	enum class Type
	{
		Force,
		Milestone,
		Null	//Used for invalid types.
	} behType;
	std::vector<std::string> navDependencies;
};

class Behaviour
{
	Behaviour() = delete;
	Behaviour(const Behaviour& cpy) = delete;
private:
	void* soHandle;
	AbstractBehaviourModule* beh;
public:
	std::string behName;
	BehaviourInfo behInfo;
public:
	Behaviour(const char* name, const char* soPath = nullptr);
	Behaviour(Behaviour&& cpy);
	~Behaviour();

	bool load(const char* soPath);
	void unload();
	bool isValid() const;
	AbstractBehaviourModule* construct(BehaviourModuleData* behData);
	AbstractBehaviourModule* getBeh();
};

#endif
