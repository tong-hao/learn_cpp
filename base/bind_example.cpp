#include <functional>
#include <iostream>

using namespace std::placeholders;

double my_divide(double x, double y) {
	return x / y;
}

int main(int argc, char const *argv[]) {
	auto f1 = std::bind(my_divide, _1, _2);
	std::cout << f1(10, 5) << std::endl;

	auto f2 = std::bind(my_divide, _1, 3);
	std::cout << f2(10) << std::endl;

	auto f3 = std::bind(my_divide, _2, _1);
	std::cout << f3(10, 5) << std::endl;

	return 0;
}