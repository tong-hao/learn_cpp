#include <fmt/format.h>
#include <iostream>

int main() {
	std::string biz_id = "hello ";
	int i = 12;
	auto msg = fmt::format("get vid error. biz_id={}, id={}\n", biz_id, i);
	std::cout << msg;
}