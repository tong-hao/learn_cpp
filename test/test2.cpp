#include <iostream>
#include <queue>
#include <vector>

#include <iomanip>

int main(int argc, char const* argv[]) {
	std::tm t{};
	std::cout << std::get_time(&t, "%Y-%m-%dT%H:%M:%S")._M_fmt;

	return 0;
}
