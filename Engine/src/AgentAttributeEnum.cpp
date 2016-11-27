#include "AgentAttributeEnum.h"
using namespace std;


AgentAttributeEnum::AgentAttributeEnum(int defaultValue, const vector<std::string>& possibleValues, const std::string& name):
	AgentAttribute(name),value(defaultValue),possibleValues(possibleValues){}

int AgentAttributeEnum::getValue() const {return value;}
const std::vector<std::string>& AgentAttributeEnum::getPossibleValues() const {return possibleValues;}
void AgentAttributeEnum::setValue(int newValue){value = newValue;}


