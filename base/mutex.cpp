#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

long num;
std::mutex mtx;
void update() {
	std::lock_guard<std::mutex> lg(mtx);
	long temp = num;
	std::cout << "begin: update" << std::to_string(temp) << std::endl;
	++num;
	std::cout << "end: update" << std::to_string(temp) << std::endl;
}

int main(int argc, char const* argv[]) {
	std::vector<std::thread> threads;
	for (int i = 0; i < 10; i++) {
		threads.emplace_back(std::thread(update));
	}

	for (auto& th : threads) {
		th.join();
	}

	std::cout << "num:" << num << std::endl;

	return 0;
}