#include <string>
#include "PassObject.h"

#pragma once

class PassObjectString : public PassObject
{
	std::string value;
public:
	PassObjectString(const std::string& defaultValue, const std::string& name="");
	std::string getValue() const;
	void setValue(std::string newValue);
};