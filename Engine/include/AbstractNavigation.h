#ifndef AbstractNavigation_H
#define AbstractNavigation_H

#include <vector>
#include <string>

class PassObject;
class AbstractNavigation
{
	void setParameters(const std::vector<PassObject*>& args);
protected:
	std::vector<PassObject*> args;
	bool dirty=true;
public:
	virtual ~AbstractNavigation() = default;
	virtual bool init() = 0;
	virtual void clearDirty();
	virtual bool IsDirty();
	virtual std::vector<PassObject*> getData(std::string dataName, std::vector<PassObject*> args) = 0;
};

#endif
