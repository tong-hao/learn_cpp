#include <iostream>
#include <string>
#include <variant>

int main() {
	std::variant<std::string, int> v;
	std::cout << "v.index = " << v.index() << '\n';
	v = 1;
	v = "bdc";

	std::cout << "v.index = " << v.index() << '\n';
	std::cout << std::get<std::string>(v) << "\n";
	// std::cout << std::get<int>(v) << "\n";
}

// link:-std=c++1z