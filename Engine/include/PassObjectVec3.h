#include <glm/vec3.hpp>
#include "PassObject.h"

#pragma once

class PassObjectVec3 : public PassObject
{
	glm::vec3 value;
public:
	PassObjectVec3(const glm::vec3& defaultValue, const std::string& name="");
	glm::vec3 getValue() const;
	void setValue(glm::vec3 newValue);
};
