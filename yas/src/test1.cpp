
#include <iostream>
#include <string>
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

/***************************************************************************/

struct A {
	A() : i_(33), s_("abc"), d_(0.001) {
	}

	std::string s_;
	double d_;
	int i_;

	template <typename Ar>
	void serialize(Ar &ar) {
		ar &i_ &s_ &d_;
	}
};

/***************************************************************************/

int main() {
	A a1, a2;
	a1.s_ = "abcd012345678910abcdefgh";
	constexpr std::size_t flags = yas::mem | yas::binary;
	auto buf = yas::save<flags>(a1);

	std::cout << "size of A: " << sizeof(A) << std::endl;
	std::cout << "buffer size: " << buf.size << std::endl;

	for (ssize_t i = 0; i < buf.size; i++) {
		std::cout << *(buf.data.get() + i);
	}
	std::cout << std::endl;

	yas::load<flags>(buf, a2);

	std::cout << "\nload:" << std::endl;
	std::cout << a2.i_ << std::endl;
	std::cout << a2.s_ << std::endl;
	std::cout << a2.d_ << std::endl;
}
