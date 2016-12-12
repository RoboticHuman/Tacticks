#include "AgentAttributeVec3.h"


AgentAttributeVec3::AgentAttributeVec3(const glm::vec3& defaultValue, const std::string& name):
	AgentAttribute(name),value(defaultValue){};

glm::vec3 AgentAttributeVec3::getValue() const {return value;}
void AgentAttributeVec3::setValue(const glm::vec3& newValue){value = newValue;}