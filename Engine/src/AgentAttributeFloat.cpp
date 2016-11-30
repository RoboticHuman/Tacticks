#include "AgentAttributeFloat.h"
using namespace std;


AgentAttributeFloat::AgentAttributeFloat(const float defaultValue, const float minValue, const float maxValue, const std::string& name):
	AgentAttribute(name),value(defaultValue),minValue(minValue),maxValue(maxValue){}

float AgentAttributeFloat::getValue() const {return value;}
float AgentAttributeFloat::getMinValue() const {return minValue;}
float AgentAttributeFloat::getMaxValue() const {return maxValue;}


void AgentAttributeFloat::setValue(const float newValue){value = newValue;}
