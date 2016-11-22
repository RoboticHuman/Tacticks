#include "AgentAttributeEnum.h"
using namespace std;


AgentAttributeEnum::AgentAttributeEnum(std::string name, int defaultValue, vector<std::string> possibleValues):
	AgentAttribute(name),value(defaultValue),possibleValues(possibleValues){}

int AgentAttributeEnum::getValue(){return value;}
const std::vector<std::string>& AgentAttributeEnum::getPossibleValues(){return possibleValues;}
void AgentAttributeEnum::setValue(int newValue){value = newValue;}


