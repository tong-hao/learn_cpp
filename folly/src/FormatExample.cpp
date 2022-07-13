#include <folly/Format.h>
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
	// format => stream
	auto fmt1 = folly::format("number1={}, number2={}", 1, 2);
	std::cout << fmt1 << std::endl;

	// sformat => string
	auto fmt2 = folly::sformat("number1={}, number2={}", 1, 2);
	std::cout << fmt2 << std::endl;

	fmt2 = folly::sformat("number1={1}, number2={0}", 1, 2);
	std::cout << fmt2 << std::endl;

	// map
	std::map<std::string, int> map{{"a", 1}, {"b", 2}};
	auto fmt3 = folly::sformat("number1={[a]}, number2={[b]}", map, map);
	std::cout << fmt3 << std::endl;

	// vformat
	auto fmt31 = folly::vformat("number1={a}, number2={b}", map);
	std::cout << fmt31 << std::endl;

	// vector
	std::vector<std::string> vct{"a", "b"};
	auto fmt4 = folly::sformat("str1={[0]}, str2={[1]}", vct, vct);
	std::cout << fmt4 << std::endl;

	return 0;
}

// link:-lfolly -ldouble-conversion