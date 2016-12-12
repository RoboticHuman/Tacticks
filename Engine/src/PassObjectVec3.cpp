#include "PassObjectVec3.h"

PassObjectVec3::PassObjectVec3(const glm::vec3& defaultValue, const std::string& name):
	PassObject(name),value(defaultValue){}

glm::vec3 PassObjectVec3::getValue() const {return value;}
void PassObjectVec3::setValue(glm::vec3 newValue){value = newValue;}
