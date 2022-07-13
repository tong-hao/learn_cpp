#pragma once 
#include "Animal.h"

namespace cpp_primer {
namespace ch07 {


class Dog : public Animal { // 注意：此处为public
  public:
	Dog() = default; // 注意：如果=0 则是抽象类型；
	~Dog() = default;

	void Say() override; // 注意：如果派生类不是virtual则编译失败

};

}
}