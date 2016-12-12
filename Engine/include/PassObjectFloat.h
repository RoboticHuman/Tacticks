#include <string>
#include "PassObject.h"

#pragma once

class PassObjectFloat : public PassObject
{
	float value;
public:
	PassObjectFloat(const float defaultValue, const std::string& name="");
	float getValue() const;
	void setValue(const float newValue);
};