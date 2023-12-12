#include <chrono>
#include <iostream>
#include <thread>

#include "Time.h"

int main(int argc, char const *argv[]) {
	using namespace std::chrono_literals;

	auto t1 = current_milliseconds();
	std::this_thread::sleep_for(10ms);
	auto t2 = current_milliseconds();

	std::cout << double(t2 - t1) << std::endl;
	return 0;
}
