#include "AgentAttributeEnum.h"
using namespace std;


AgentAttributeEnum::AgentAttributeEnum(const std::string& name, int defaultValue, const vector<std::string>& possibleValues):
	AgentAttribute(name),value(defaultValue),possibleValues(possibleValues){}

int AgentAttributeEnum::getValue() const {return value;}
const std::vector<std::string>& AgentAttributeEnum::getPossibleValues() const {return possibleValues;}
void AgentAttributeEnum::setValue(int newValue){value = newValue;}


