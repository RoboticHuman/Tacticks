#include "AttributeFactory.h"
#include "AgentAttributeBool.h"
#include "AgentAttributeEnum.h"
#include "AgentAttributeFloat.h"
#include "AgentAttributeInt.h"
#include "AgentAttributeVec3.h"

using namespace std;

AttributeFactory::AttributeFactory(std::unordered_map<int, BehaviourModuleData::PrivateAgent>& agentsContainer):agents(agentsContainer)
{
	// Default Attributes
	attributeMap.insert(pair<std::string,std::pair<int,AgentAttribute*> >(
		"Position",pair<int,AgentAttribute*>(1,new AgentAttributeVec3("Position",glm::vec3(0,0,0)))));
}

void AttributeFactory::addAttribute(const AgentAttribute* attribute)
{
	map<string, pair<int,AgentAttribute*> >::iterator it(attributeMap.find(attribute->getName()));

	if (it != attributeMap.end())
		it->second.first++;
	else {
		AgentAttribute* attributeToAdd;

		if (dynamic_cast<const AgentAttributeBool*>(attribute)) {
			const AgentAttributeBool* temp = dynamic_cast<const AgentAttributeBool*>(attribute);
			attributeToAdd = new AgentAttributeBool(temp->getName(),temp->getValue());
			for (auto& agent : agents) {
				agent.second.agent.attributes.insert(pair<string,AgentAttribute*>(temp->getName(),
									new AgentAttributeBool(temp->getName(),temp->getValue())));
			}
		}
		else if (dynamic_cast<const AgentAttributeEnum*>(attribute)) {
			const AgentAttributeEnum* temp = dynamic_cast<const AgentAttributeEnum*>(attribute);
			attributeToAdd = new AgentAttributeEnum(temp->getName(),temp->getValue(),
									temp->getPossibleValues());
			for (auto& agent : agents) {
				agent.second.agent.attributes.insert(pair<string,AgentAttribute*>(temp->getName(),
									new AgentAttributeEnum(temp->getName(),temp->getValue(),
										temp->getPossibleValues())));
			}
		}
		else if (dynamic_cast<const AgentAttributeFloat*>(attribute)) {
			const AgentAttributeFloat* temp = dynamic_cast<const AgentAttributeFloat*>(attribute);
			attributeToAdd = new AgentAttributeFloat(temp->getName(),temp->getValue(),
									temp->getMinValue(),temp->getMaxValue());		
			for (auto& agent : agents) {
				agent.second.agent.attributes.insert(pair<string,AgentAttribute*>(temp->getName(),
									new AgentAttributeFloat(temp->getName(),temp->getValue(),
										temp->getMinValue(),temp->getMaxValue())));
			}
		}
		else if (dynamic_cast<const AgentAttributeInt*>(attribute)) {
			const AgentAttributeInt* temp = dynamic_cast<const AgentAttributeInt*>(attribute);
			attributeToAdd = new AgentAttributeInt(temp->getName(),temp->getValue(),
									temp->getMinValue(),temp->getMaxValue());	
			for (auto& agent : agents) {
				agent.second.agent.attributes.insert(pair<string,AgentAttribute*>(temp->getName(),
									new AgentAttributeInt(temp->getName(),temp->getValue(),
										temp->getMinValue(),temp->getMaxValue())));
			}

		}
		else if (dynamic_cast<const AgentAttributeVec3*>(attribute)) {
			const AgentAttributeVec3* temp = dynamic_cast<const AgentAttributeVec3*>(attribute);
			attributeToAdd = new AgentAttributeVec3(temp->getName(),temp->getValue());
			for (auto& agent : agents) {
				agent.second.agent.attributes.insert(pair<string,AgentAttribute*>(temp->getName(),
									new AgentAttributeVec3(temp->getName(),temp->getValue())));
			}
		}
		else {
			// TODO
			// ADD ERROR HANDLING FOR UNSUPPORTED ATTRIBUTE TYPES
		}
		attributeMap.insert(pair<std::string,std::pair<int,AgentAttribute*> >(
			attribute->getName(),pair<int,AgentAttribute*>(1,attributeToAdd)));
	}
}


void AttributeFactory::removeAttribute(std::string attributeName)
{
	map<string, pair<int,AgentAttribute*> >::iterator it(attributeMap.find(attributeName));
	if (it != attributeMap.end()) {
		// If this was the last module depending on this attribute then remove it
		// Otherwise just decrement its count by 1
		if (--(it->second.first) == 0) {
			for (auto& agent : agents) {
				agent.second.agent.attributes.erase(attributeName);
			}
		}
	}
	else {
		// TODO:
		// ADD ERROR HANDLING IF THE DELETED ATTRIBUTE DOESN'T EXIST
	}
}



void AttributeFactory::initializeAgentAttributes(int agentID)
{
	Agent& agentToBeInitialized(agents.find(agentID)->second.agent);
	for (auto& attrPair : attributeMap) {
		AgentAttribute* attribute = attrPair.second.second;
		if (dynamic_cast<const AgentAttributeBool*>(attribute)) {
			const AgentAttributeBool* temp = dynamic_cast<const AgentAttributeBool*>(attribute);
			agentToBeInitialized.attributes.insert(pair<string,AgentAttribute*>(temp->getName(),
									new AgentAttributeBool(temp->getName(),temp->getValue())));
		}
		else if (dynamic_cast<const AgentAttributeEnum*>(attribute)) {
			const AgentAttributeEnum* temp = dynamic_cast<const AgentAttributeEnum*>(attribute);
			agentToBeInitialized.attributes.insert(pair<string,AgentAttribute*>(temp->getName(),
									new AgentAttributeEnum(temp->getName(),temp->getValue(),
											temp->getPossibleValues())));
		}
		else if (dynamic_cast<const AgentAttributeFloat*>(attribute)) {
			const AgentAttributeFloat* temp = dynamic_cast<const AgentAttributeFloat*>(attribute);
			agentToBeInitialized.attributes.insert(pair<string,AgentAttribute*>(temp->getName(),
									new AgentAttributeFloat(temp->getName(),temp->getValue(),
											temp->getMinValue(),temp->getMaxValue())));
		}
		else if (dynamic_cast<const AgentAttributeInt*>(attribute)) {
			const AgentAttributeInt* temp = dynamic_cast<const AgentAttributeInt*>(attribute);
			agentToBeInitialized.attributes.insert(pair<string,AgentAttribute*>(temp->getName(),
									new AgentAttributeInt(temp->getName(),temp->getValue(),
											temp->getMinValue(),temp->getMaxValue())));
		}	
		else if (dynamic_cast<const AgentAttributeVec3*>(attribute)) {
			const AgentAttributeVec3* temp = dynamic_cast<const AgentAttributeVec3*>(attribute);
			agentToBeInitialized.attributes.insert(pair<string,AgentAttribute*>(temp->getName(),
									new AgentAttributeVec3(temp->getName(),temp->getValue())));
		}
	}
}














