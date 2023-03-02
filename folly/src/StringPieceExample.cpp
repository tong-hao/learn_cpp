#include <folly/Range.h>
#include <iostream>

int main(int argc, char const *argv[]) {
	folly::StringPiece str;
	str = "a";

	std::cout << sizeof(str) << std::endl;

	return 0;
}
