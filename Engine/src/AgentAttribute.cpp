#include "AgentAttribute.h"

int AgentAttribute::nextAttributeID = 0;

AgentAttribute::AgentAttribute(const std::string& name):
	name(name),attributeID(nextAttributeID++)
{}

int AgentAttribute::getAttributeID() const {return attributeID;}

std::string AgentAttribute::getName() const {return name;}
