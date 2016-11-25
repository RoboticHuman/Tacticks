#include "AgentAttribute.h"
#include "AttributeFactory.h"

#pragma once

class DependancyManager
{
	AttributeFactory& attrFactory;
public:
	DependancyManager(AttributeFactory& attributeFactory);
	void addAttribute(const AgentAttribute* attribute);
};