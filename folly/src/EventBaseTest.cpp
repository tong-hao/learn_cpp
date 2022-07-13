#include <folly/executors/IOThreadPoolExecutor.h>
#include <folly/futures/Future.h>
#include <folly/io/async/EventBase.h>
#include <iostream>

// 情况1:
// EventBase是当前线程，所以多个folly::via需要排队
int main1(int argc, char const* argv[]) {
	std::cout << "begin:\n" << std::endl;
	folly::IOThreadPoolExecutor ex{3};
	folly::EventBase eb;
	folly::via(&eb, []() {
		for (int i = 0; i < 10; i++) {
			std::cout << "folly::via111 \n" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		std::cout << "folly::via111 over \n" << std::endl;
	});

	folly::EventBase eb2;
	folly::via(&eb2, []() {
		for (int i = 0; i < 10; i++) {
			std::cout << "folly::via222 \n" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		std::cout << "folly::via222 over \n" << std::endl;
	});
	std::cout << "end:\n" << std::endl;
	return 0;
}
// 情况2:
// folly::via(IOThreadPoolExecutor) 可以并行执行
int main2(int argc, char const* argv[]) {
	std::cout << "begin:\n" << std::endl;
	folly::IOThreadPoolExecutor ex{3};
	folly::EventBase eb;
	folly::via(&ex, []() {
		for (int i = 0; i < 10; i++) {
			std::cout << "folly::via111 \n" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		std::cout << "folly::via111 over \n" << std::endl;
	});

	folly::EventBase eb2;
	folly::via(&ex, []() {
		for (int i = 0; i < 10; i++) {
			std::cout << "folly::via222 \n" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		std::cout << "folly::via222 over \n" << std::endl;
	});
	std::cout << "end:\n" << std::endl;
	return 0;
}

// 情况3:
// folly::via(IOThreadPoolExecutor) 嵌套，可以执行
int main(int argc, char const* argv[]) {
	std::cout << "begin:\n" << std::endl;
	folly::IOThreadPoolExecutor ex{3};
	folly::via(&ex, [&ex]() {
		for (int i = 0; i < 10; i++) {
			folly::via(&ex, []() {
				std::cout << "folly::via111 \n" << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			});
		}
		std::cout << "folly::via111 over \n" << std::endl;
	});

	folly::via(&ex, [&ex]() {
		for (int i = 0; i < 10; i++) {
			folly::via(&ex, []() {
				std::cout << "folly::via222 \n" << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			});
		}
		std::cout << "folly::via222 over \n" << std::endl;
	});
	std::cout << "end:\n" << std::endl;
	return 0;
}

// link:-lfolly -lglog -lgflags -lpthread -liberty -ldl -levent
// link:-ldouble-conversion -lboost_context
