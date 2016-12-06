#ifndef AbstractNavigation_H
#define AbstractNavigation_H

#include <vector>
#include <string>

class PassObject;
class World;

class AbstractNavigation
{
private:
	bool dirty=true;
protected:
	std::vector<PassObject*> args;
	const World* world;
	AbstractNavigation(const World* world);
public:
	void setParameters(const std::vector<PassObject*>& args);
	virtual ~AbstractNavigation() = default;
	virtual bool init() = 0;
	virtual void clearDirty();
	virtual bool isDirty();
	virtual std::vector<PassObject*> getData(std::string dataName, std::vector<PassObject*> args) = 0;
};

#endif
