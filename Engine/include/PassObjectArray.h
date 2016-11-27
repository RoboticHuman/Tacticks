#include <string>
#include <vector>
#include "PassObject.h"

#pragma once

class PassObjectArray : public PassObject
{
	std::vector<PassObject*> value;
public:
	PassObjectArray(int size=1, const std::string& name="");
	int getSize() const;
	PassObject* operator[](const unsigned int);
	void push(PassObject* object);
	void pop();
	~PassObjectArray();
};