#include <iostream>
#include <variant>

int main() {
	std::variant<int32_t, std::string> v;
	int64_t i = 1;
	v = i;
	std::cout << v.index() << std::endl;

	return 0;
}
