#include "PassObject.h"

#pragma once

class PassObjectInt : public PassObject
{
	int value;
public:
	PassObjectInt(const int defaultValue, const std::string& name="");
	int getValue() const;
	void setValue(const int newValue);
};