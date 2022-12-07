#include "Complex.h"

int main(int argc, char const *argv[]) {
	Complex a;
	Complex b(1.0, 2.0);
	Complex c1 = a + b;
	std::cout << "c1:" << c1 << std::endl;
	Complex c2 = a + 1.0;
	std::cout << "c2:" << c1 << std::endl;
	a += b;
	std::cout << "a:" << a << std::endl;

	std::cout << "-a:" << -a << std::endl;

	return 0;
}
