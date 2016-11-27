#include "PassObject.h"
#include <iostream>
using namespace std;

PassArray::PassArray(int size) : lst(size)
{

}
PassArray::PassArray(const std::vector<PassObject>& list) : lst(list)
{

}

PassArray& PassArray::operator=(const PassArray& cpy)
{
	cout << "*********hmmmm Wired" << this << ' ' << &lst << ' ' << lst.size() << ' ' << cpy.size() << endl;
	lst.resize(0);
	cout << "AfterResize" << endl;
	lst = cpy.lst;
	return *this;
}
PassArray& PassArray::operator+=(const PassObject& val)
{
	lst.push_back(val);
	return *this;
}
PassArray PassArray::operator+(const PassObject& val) const
{
	PassArray ret(*this);
	return ret += val;
}
PassArray& PassArray::operator+=(const PassArray& val)
{
	for(const PassObject& obj : val.lst)
		lst.push_back(obj);
	return *this;
}
PassArray PassArray::operator+(const PassArray& val) const
{
	PassArray ret(*this);
	return ret += val;
}
const PassObject& PassArray::operator[](unsigned int ind) const
{
	return lst[ind];
}
PassObject& PassArray::operator[](unsigned int ind)
{
	return lst[ind];
}
int PassArray::size() const
{
	return lst.size();
}

PassObject::PassObject(const string&)
{
	this->name = name;
	this->data.type = Data::Null;
	this->data.i = 0;
}
PassObject::PassObject(const string& name, int val)
{
	this->name = name;
	this->data.type = Data::Integer;
	this->data.i = val;
}
PassObject::PassObject(const string& name, double val)
{
	this->name = name;
	this->data.type = Data::Decimal;
	this->data.f = val;
}
PassObject::PassObject(const string& name, const string& val)
{
	this->name = name;
	this->data.type = Data::String;
	new (&data.str) std::string();
	this->data.str = val;
}
PassObject::PassObject(const string& name, const PassArray& val)
{
	new (&data.arr) PassArray();
	cout << "Yaaay" << endl;
	this->name = name;
	this->data.type = Data::Array;
	cout << "Before arr=" << endl;
	this->data.arr = val;
	cout << "Yaaaaaaaay2" << endl;
}

PassObject& PassObject::operator=(const PassObject& cpy)
{
	name = cpy.name;
	data = cpy.data;
	return *this;
}
PassArray PassObject::operator+(const PassObject& val)
{
	return PassArray({*this}) + val;
}

void PassObject::setName(const string& val)
{
	name = val;
}
void PassObject::setValue(int val)
{
	data.type = Data::Integer;
	data.i = val;
}
void PassObject::setValue(double val)
{
	data.type = Data::Decimal;
	data.f = val;
}
void PassObject::setValue(const string& val)
{
	data.type = Data::String;
	data.str = val;
}
void PassObject::setValue(const PassArray& val)
{
	data.type = Data::Array;
	new (&data.arr) PassArray();
	data.arr = val;
}

string PassObject::getName() const
{
	return name;
}
int PassObject::asInteger() const
{
	return data.i;
}
double PassObject::asDecimal() const
{
	return data.f;
}
string PassObject::asString() const
{
	return data.str;
}
PassArray PassObject::asArray() const
{
	return data.arr;
}

bool PassObject::isInteger() const
{
	return data.type == Data::Integer;
}
bool PassObject::isDecimal() const
{
	return data.type == Data::Decimal;
}
bool PassObject::isString() const
{
	return data.type == Data::String;
}
bool PassObject::isArray() const
{
	return data.type == Data::Array;
}
bool PassObject::isValid() const
{
	return name == "" || data.type == Data::Null;
}

PassObject::Data::Data()
{
	type = Null;
}
PassObject::Data::Data(const Data& cpy)
{
	type = cpy.type;
	if(type == Integer) i = cpy.i;
	else if(type == Decimal) f = cpy.f;
	else if(type == String) str = cpy.str;
	else if(type == Array) arr = cpy.arr;
}
PassObject::Data::Data(Data&& cpy)
{
	type = cpy.type;
	if(type == Integer) i = cpy.i;
	else if(type == Decimal) f = cpy.f;
	else if(type == String) str = move(cpy.str);
	else if(type == Array) arr = move(cpy.arr);
}
PassObject::Data::~Data()
{

}
PassObject::Data& PassObject::Data::operator=(const Data& cpy)
{
	type = cpy.type;
	if(type == Integer) i = cpy.i;
	else if(type == Decimal) f = cpy.f;
	else if(type == String) str = cpy.str;
	else if(type == Array) arr = cpy.arr;
	return *this;
}
