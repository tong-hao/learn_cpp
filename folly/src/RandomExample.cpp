#include <folly/Random.h>
#include <iostream>

int main(int argc, char const *argv[]) {
	double min = 0.3;
	double max = 0.4;

	for (int i = 0; i < 100; i++) {
		double d = folly::Random::secureRandDouble(min, max);
		std::cout << d << std::endl;
	}

	return 0;
}

// link:-lfolly -lglog -lgflags -ldouble-conversion -lpthread -ldl -liberty