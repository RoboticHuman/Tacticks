#include "AgentAttributeInt.h"
using namespace std;


AgentAttributeInt::AgentAttributeInt(const int defaultValue, const int minValue, const int maxValue, const std::string& name):
	AgentAttribute(name),value(defaultValue),minValue(minValue),maxValue(maxValue){}

int AgentAttributeInt::getValue() const {return value;}
int AgentAttributeInt::getMinValue() const {return minValue;}
int AgentAttributeInt::getMaxValue() const {return maxValue;}


void AgentAttributeInt::setValue(const int newValue){value = newValue;}
