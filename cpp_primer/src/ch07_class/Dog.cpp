#include "Dog.h"
#include "iostream"

namespace cpp_primer {
namespace ch07 {

void Dog::Say()  {
	std::cout << "I am a Dog. My name is " << GetName() << std::endl;
}

}
}