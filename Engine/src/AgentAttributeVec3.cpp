#include "AgentAttributeVec3.h"


AgentAttributeVec3::AgentAttributeVec3(const std::string& name, const glm::vec3& defaultValue):
	AgentAttribute(name),value(defaultValue){};

glm::vec3 AgentAttributeVec3::getValue() const {return value;}
void AgentAttributeVec3::setValue(const glm::vec3& newValue){value = newValue;}