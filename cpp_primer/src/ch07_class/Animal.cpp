#include <iostream>
#include "Animal.h"

namespace cpp_primer {
namespace ch07 {

void Animal::Say(){
	std::cout << "Hello. I'am an Animal. My name is " << name_ << std::endl;
}

Animal Animal::Say2(){
	Say();
	return *this;
}

}
}