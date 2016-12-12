#include <string>
#include "PassObject.h"

#pragma once

class PassObjectBool : public PassObject
{
	bool value;
public:
	PassObjectBool(const bool defaultValue, const std::string& name="");
	bool getValue() const;
	void setValue(bool newValue);
};