#include <folly/Function.h>
#include <iostream>
#include <string>

int function1(std::string& s) {
	return 1;
}

int main(int argc, char const* argv[]) {
	folly::Function<int(std::string&) const> f1 = function1;

	std::string s1 = "hello";
	auto ret1 = f1(s1);
	std::cout << ret1 << std::endl;

	folly::Function<int(std::string&) const> f2 = [](std::string& s) {
		return 2;
	};
	auto ret2 = f2(s1);
	std::cout << ret2 << std::endl;

	auto f21 = std::move(f2);
	std::cout << f21(s1) << std::endl;

	return 0;
}

// link:-lfolly