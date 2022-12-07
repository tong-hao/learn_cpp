#ifndef __STRING__
#define __STRING__
#include <string.h>
#include <iostream>

// usage:
// String s1;
// String s2(s1);
// String s3("hello");
// String s4 = s1;
// s3 = s1;
// std::cout << s1 << std::endl;

class String {
public:
	String(const char* p_str = nullptr);

	String(const String&);

	String& operator=(const String&);

	char* c_str() const {
		return this->data;
	}

	~String() {
		delete data;
	}

private:
	char* data;
};

String::String(const char* p_str) {
	if (p_str) {
		data = new char[strlen(p_str) + 1];
		strcpy(data, p_str);
	} else {
		data = new char[1];
		data[0] = '\0';
	}
}
String::String(const String& other) {
	if (other.data) {
		data = new char[strlen(other.data) + 1];
		strcpy(data, other.data);
	} else {
		data = new char[1];
		data[0] = '\0';
	}
}
String& String::operator=(const String& other) {
	if (this == &other)
		return *this;

	delete this->data;
	this->data = new char[strlen(other.data) + 1];
	strcpy(this->data, other.data);

	return *this;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
	return os << str.c_str();
}

#endif
