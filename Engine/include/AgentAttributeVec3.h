#include <string>
#include "AgentAttribute.h"
#include <glm/vec3.hpp>

#pragma once

class AgentAttributeVec3 : public AgentAttribute
{
	glm::vec3 value;
public:
	AgentAttributeVec3(const glm::vec3& defaultValue, const std::string& name="");
	glm::vec3 getValue() const;
	void setValue(const glm::vec3& newValue);
};