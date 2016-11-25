#include "AgentAttributeFloat.h"
using namespace std;


AgentAttributeFloat::AgentAttributeFloat(const std::string& name, float defaultValue, float minValue, float maxValue):
	AgentAttribute(name),value(defaultValue),minValue(minValue),maxValue(maxValue){}

float AgentAttributeFloat::getValue() const {return value;}
float AgentAttributeFloat::getMinValue() const {return minValue;}
float AgentAttributeFloat::getMaxValue() const {return maxValue;}


void AgentAttributeFloat::setValue(float newValue){value = newValue;}
