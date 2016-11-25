#include <string>
#include "AgentAttribute.h"
#include <glm/vec3.hpp>

#pragma once

class AgentAttributeVec3 : public AgentAttribute
{
	glm::vec3 value;
public:
	AgentAttributeVec3(const std::string& name, const glm::vec3& defaultValue);
	glm::vec3 getValue() const;
	void setValue(const glm::vec3& newValue);
};