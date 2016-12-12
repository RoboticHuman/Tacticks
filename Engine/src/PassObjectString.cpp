#include "PassObjectString.h"

PassObjectString::PassObjectString(const std::string& defaultValue, const std::string& name):
	PassObject(name),value(defaultValue){}

std::string PassObjectString::getValue() const {return value;}
void PassObjectString::setValue(std::string newValue){value = newValue;}