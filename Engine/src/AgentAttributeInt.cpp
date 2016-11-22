#include "AgentAttributeInt.h"
using namespace std;


AgentAttributeInt::AgentAttributeInt(string name, int defaultValue, int minValue, int maxValue):
	AgentAttribute(name),value(defaultValue),minValue(minValue),maxValue(maxValue){}

int AgentAttributeInt::getValue(){return value;}
int AgentAttributeInt::getMinValue(){return minValue;}
int AgentAttributeInt::getMaxValue(){return maxValue;}


void AgentAttributeInt::setValue(int newValue){value = newValue;}
