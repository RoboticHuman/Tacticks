#ifndef PassObject_H
#define PassObject_H

#include <string>
#include <vector>

class PassObject;
class PassArray
{
	std::vector<PassObject> lst;
public:
	PassArray(int size = 0);
	PassArray(const std::vector<PassObject>& list);
	PassArray(const PassArray&) = default;
	PassArray(PassArray&&) = default;
	~PassArray() = default;

	PassArray& operator=(const PassArray& cpy);
	PassArray& operator+=(const PassObject& val);
	PassArray operator+(const PassObject& val) const;
	PassArray& operator+=(const PassArray& val);
	PassArray operator+(const PassArray& val) const;
	PassObject operator[](unsigned int ind) const;
	int size() const;
};
class PassObject
{
	std::string name;
	struct Data
	{
		enum
		{
			Null,
			Integer,
			Decimal,
			String,
			Array
		} type = Null;
		union
		{
			int i;
			double f;
			std::string str;
			PassArray arr;
		};

		Data();
		Data(const Data& cpy);
		Data(Data&&) = default;
		~Data();
		Data& operator=(const Data& cpy);
	} data;
public:
	PassObject(const std::string& name = "");
	PassObject(const std::string& name, int val);
	PassObject(const std::string& name, double val);
	PassObject(const std::string& name, const std::string& val);
	PassObject(const std::string& name, const PassArray& val);
	PassObject(const PassObject& cpy) = default;
	PassObject(PassObject&&) = default;
	~PassObject() = default;

	PassObject operator=(const PassObject& cpy);
	PassArray operator+(const PassObject& val);

	void setName(const std::string& val);
	void setValue(int val);
	void setValue(double val);
	void setValue(const std::string& val);
	void setValue(const PassArray& val);

	std::string getName() const;
	int asInteger() const;
	double asDecimal() const;
	std::string asString() const;
	PassArray asArray() const;

	bool isInteger() const;
	bool isDecimal() const;
	bool isString() const;
	bool isArray() const;
	bool isValid() const;
};

#endif
