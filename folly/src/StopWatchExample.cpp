#include <folly/stop_watch.h>
#include <chrono>
#include <iostream>

int main(int argc, char const *argv[]) {
	folly::stop_watch<> stop_watch{};

	std::cout << "1" << std::endl;
	const auto wait = std::chrono::seconds(1);
	std::cout << stop_watch.elapsed(wait) << std::endl;
	while (!stop_watch.elapsed(wait)) {
		// std::cout << "2" << std::endl;
	}
	std::cout << stop_watch.elapsed(wait) << std::endl;
	std::cout << "end" << std::endl;
	return 0;
}
// link:-lfolly