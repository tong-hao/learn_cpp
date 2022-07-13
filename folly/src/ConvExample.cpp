#include <folly/Conv.h>
#include <iostream>
#include <string>

using namespace folly;

int main(int argc, char const *argv[]) {
	// toAppend
	std::string str;
	toAppend(1, &str);
	toAppend("!=", &str);
	toAppend(2.5, &str);

	std::cout << str << std::endl;

	// int to string
	std::string s1 = to<std::string>(100);
	std::cout << "s1==100 ? " << (s1 == "100") << std::endl;

	// string to int
	int i = 0;
	i = to<int>("100");
	std::cout << "i is " << i << std::endl;

	// to char
	std::string s2 = "a";
	char ch1 = s2[0];
	std::cout << ch1 << std::endl;
	auto ch2 = folly::to<std::string>(*reinterpret_cast<const char *>(&ch1));
	std::cout << ch2 << std::endl;

	// parse int from string
	std::string s3 = "200 is a num.";
	StringPiece pc(s3);
	i = to<int>(&pc);
	std::cout << "i is " << i << ", StringPinece is " << pc << std::endl;

	// to double
	std::string s4 = "1.1";
	auto f1 = to<float>(s4);
	std::cout << (f1 == 1.1f) << std::endl;

	return 0;
}

// link:-lfolly
// link:-ldouble-conversion
// link:-dl