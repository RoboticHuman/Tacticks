#include "PassObjectArray.h"

PassObjectArray::PassObjectArray(int size, const std::string& name):value(size),PassObject(name){};
int PassObjectArray::getSize() const {return value.size();}
PassObject*& PassObjectArray::operator[](const unsigned int i) {return value[i];}
void PassObjectArray::push(PassObject* object) {value.push_back(object);}
void PassObjectArray::pop()
{
	delete value.back();
	value.pop_back();
}
PassObjectArray::~PassObjectArray()
{
	for (PassObject* obj : value) {
		delete obj;
	}
}
