#include <folly/ProducerConsumerQueue.h>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main(int argc, char const* argv[]) {
	folly::ProducerConsumerQueue<std::string> queue(100);

	std::thread reader([&queue]() {
		for (int i = 0; i < 10; i++) {
			std::string* p;
			do {
				p = queue.frontPtr();
			} while (!p);

			std::cout << "read: " << *p << std::endl;

			queue.popFront();
		}
	});

	for (int i = 0; i < 10; i++) {
		std::string str = "abc";
		while (!queue.write(std::move(str))) {
			continue;
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}

// link:-lfolly -lpthread