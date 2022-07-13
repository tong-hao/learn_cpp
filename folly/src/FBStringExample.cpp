#include <folly/FBString.h>    // folly::fbstring
#include <folly/gen/String.h>  //folly::gen::split()
#include <iostream>
#include <string>

int main(int argc, char const* argv[]) {
	folly::fbstring str = "abc";
	std::cout << str << std::endl;
	std::cout << "str.size() == " << str.size() << std::endl;
	std::cout << (str == "abc") << std::endl;

	// split
	auto items = folly::gen::split("a,b,c", ",");
	items.foreach ([](auto&& item) { std::cout << item << std::endl; });

	return 0;
}

// link:-lfolly