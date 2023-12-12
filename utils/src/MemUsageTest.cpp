#include <array>
#include <chrono>
#include <iostream>
#include <thread>
#include <unordered_map>

#include "MemUsage.h"

int main(int argc, char const* argv[]) {
	using namespace std::chrono_literals;

	auto m1 = memUsage();
	std::unordered_map<int, int> m;
	m.reserve(10000);
	for (int i = 0; i < 10000; i++) {
		m[i] = 2 * i;
	}

	std::this_thread::sleep_for(10s);
	auto m2 = memUsage();
	std::cout << m2.vmRss_ - m1.vmRss_ << std::endl;

	std::array<int, 10000> arr;
	for (int i = 0; i < 10000; i++) {
		arr[i] = 2 * i;
	}

	std::this_thread::sleep_for(10s);
	auto m3 = memUsage();
	std::cout << m3.vmRss_ - m2.vmRss_ << std::endl;
	return 0;
}
