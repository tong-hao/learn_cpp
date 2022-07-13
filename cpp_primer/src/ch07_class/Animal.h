#pragma once 
#include <string>
#include <iostream>

namespace cpp_primer {
namespace ch07 {
class Animal {
  public:
	Animal() = default;
	Animal(std::string name):name_(name){};

	~Animal() = default;

	void SetName(std::string name){name_ = name;}
	std::string GetName(){return name_;}
	virtual void Say(); // 注意：子类对Say进行override

	Animal Say2();
	Animal SetName2(std::string name){name_ = name; return *this;}

	void TestConst() const{std::cout << "this is const" << std::endl; } //注意：这里不能修改成员变量
	void TestConst() {std::cout << "this is not const" << std::endl; name_ = "const";} // 这里可以修改

private:
	std::string name_ = "unset";

};


}
}

