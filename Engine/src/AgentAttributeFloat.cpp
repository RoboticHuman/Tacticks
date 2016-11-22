#include "AgentAttributeFloat.h"
using namespace std;


AgentAttributeFloat::AgentAttributeFloat(string name, float defaultValue, float minValue, float maxValue):
	AgentAttribute(name),value(defaultValue),minValue(minValue),maxValue(maxValue){}

float AgentAttributeFloat::getValue(){return value;}
float AgentAttributeFloat::getMinValue(){return minValue;}
float AgentAttributeFloat::getMaxValue(){return maxValue;}


void AgentAttributeFloat::setValue(float newValue){value = newValue;}
