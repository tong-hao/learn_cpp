#include <iostream>
#include "VectorLite.h"

struct A {
	int data_;
};

struct B {
	int* p_;
	// int8_t i_;
};

int main(int argc, char const* argv[]) {
	VectorLite<A> vct;
	vct.resize(10);
	// for (int i = 0; i < 10; i++) {
	// 	vct[i].data_ = i;
	// 	std::cout << vct.at(i).data_ << std::endl;
	// }

	std::cout << sizeof(B) << std::endl;

	return 0;
}
