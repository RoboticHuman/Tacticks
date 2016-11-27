#include "PassObjectBool.h"

PassObjectBool::PassObjectBool(const bool defaultValue, const std::string& name):
	PassObject(name),value(defaultValue){}

bool PassObjectBool::getValue() const {return value;}
void PassObjectBool::setValue(bool newValue){value = newValue;}