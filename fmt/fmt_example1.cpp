// #include <fmt/format.h>
// #include <fmt/format-inl.h>
#include <fmt/core.h>
#include <iostream>

int main() {
	auto msg = fmt::format("{} {}", "hello", "cpp");
	std::cout << msg;
}

// link: -lfmt -lfolly -ldl -ldouble-conversion -lgflags