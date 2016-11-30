#include "PassObjectInt.h"
using namespace std;


PassObjectInt::PassObjectInt(const int defaultValue, const std::string& name):
	PassObject(name),value(defaultValue){}

int PassObjectInt::getValue() const {return value;}

void PassObjectInt::setValue(const int newValue){value = newValue;}
