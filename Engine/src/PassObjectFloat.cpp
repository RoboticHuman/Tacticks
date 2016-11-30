#include "PassObjectFloat.h"
using namespace std;


PassObjectFloat::PassObjectFloat(const float defaultValue, const std::string& name):
	PassObject(name),value(defaultValue){}

float PassObjectFloat::getValue() const {return value;}

void PassObjectFloat::setValue(const float newValue){value = newValue;}
