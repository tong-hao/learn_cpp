#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/futures/Future.h>
#include <folly/synchronization/SmallLocks.h>
#include <iostream>
#include <limits>
#include <string>

int main(int argc, char const *argv[]) {
	std::cout << "CHAR_BIT: " << CHAR_BIT << std::endl;

	int data = 0;
	unsigned int data_lock = 3;  // 小于 CHAR_BIT/2
	folly::MicroLock l;

	folly::CPUThreadPoolExecutor executors{3};

	for (int i = 0; i < 10; i++) {
		folly::via(&executors).thenValue([&data, &l, &data_lock](auto &&p) {
			l.lock();
			++data;
			std::cout << ": " << data << std::endl;
			l.unlock();
		});
	}

	return 0;
}

// link:-lfolly -lglog -lgflags -lpthread -levent -ldl -liberty
// link:-ldouble-conversion -lboost_context -lboost_system
