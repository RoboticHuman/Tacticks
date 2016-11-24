#include "AgentAttributeInt.h"
using namespace std;


AgentAttributeInt::AgentAttributeInt(const std::string& name, int defaultValue, int minValue, int maxValue):
	AgentAttribute(name),value(defaultValue),minValue(minValue),maxValue(maxValue){}

int AgentAttributeInt::getValue() const {return value;}
int AgentAttributeInt::getMinValue() const {return minValue;}
int AgentAttributeInt::getMaxValue() const {return maxValue;}


void AgentAttributeInt::setValue(int newValue){value = newValue;}
