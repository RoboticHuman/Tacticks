#ifndef AbstractNavigation_H
#define AbstractNavigation_H

#include <vector>
#include <string>
#include <PassObject.h>

class AbstractNavigation
{
public:
	virtual ~AbstractNavigation() = default;
	virtual void init(std::vector<PassObject> args) = 0;
	virtual std::vector<PassObject> getData(std::string dataName, std::vector<PassObject> args) = 0;
};

#endif
