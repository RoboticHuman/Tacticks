#include <string>
#include <vector>

#pragma once

class PassObject
{
private:
	std::string name;
public:
	PassObject(const std::string& objectName="");
	std::string getName();
	virtual ~PassObject() = default;
};
