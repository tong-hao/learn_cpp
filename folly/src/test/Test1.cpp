#include <folly/Conv.h>
#include <iostream>

int main(int argc, char const *argv[]) {
	int16_t i1 = folly::to<int16_t>(3123);
	std::cout << i1 << std::endl;

	return 0;
}
// link:-lfolly -ldouble-conversion -ldl -lpthread -lfmt
