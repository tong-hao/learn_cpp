#include <folly/ThreadCachedInt.h>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main(int argc, char const *argv[]) {
	folly::ThreadCachedInt<int64_t> my_int(1);

	for (int i = 0; i < 100000; i++) {
		++my_int;
		// my_int.set(i);

		if (i % 10000 == 0) {
			std::cout << "fast:" << my_int.readFast()
			          << ", full:" << my_int.readFull() << std::endl;
			// std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	return 0;
}

// link:-lfolly -lglog -lgflags -lpthread -ldl -ldouble-conversion