#include "DependancyManager.h"

DependancyManager::DependancyManager(AttributeFactory& attributeFactory):attrFactory(attributeFactory){}

void DependancyManager::addAttribute(const AgentAttribute* attribute) {attrFactory.addAttribute(attribute);}