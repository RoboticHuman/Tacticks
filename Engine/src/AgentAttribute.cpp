#include "AgentAttribute.h"

int AgentAttribute::nextAttributeID = 0;

AgentAttribute::AgentAttribute(std::string name):
	name(name),attributeID(nextAttributeID++)
{}

int AgentAttribute::getAttributeID() {return attributeID;}

std::string AgentAttribute::getName() {return name;}
