// #include <fmt/format-inl.h>
// #include <fmt/format.h>
#include <folly/SharedMutex.h>
#include <folly/Synchronized.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/executors/IOThreadPoolExecutor.h>
#include <folly/futures/Future.h>
#include <folly/hash/FarmHash.h>
#include <folly/init/Init.h>
#include <folly/stop_watch.h>
#include <algorithm>
#include <boost/variant.hpp>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <memory>
#include <thread>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

int main() {
	std::shared_ptr<folly::IOThreadPoolExecutor> exec =
	    std::make_shared<folly::IOThreadPoolExecutor>(2);

	for (size_t i = 0; i < 10; i++) {
		folly::via(exec.get(), []() {});
		// exec.add([i, &exec]() {
		// 	LOG(INFO) << "begin: sleep" << i << std::endl;

		// 	folly::EventBase e;
		// 	folly::via(&e, [i]() {
		// 		for (size_t j = 0; j < 3; j++) {
		// 			LOG(INFO) << "sleep" << i << j << std::endl;
		// 			std::this_thread::sleep_for(std::chrono::milliseconds(3));
		// 		}
		// 	});
		// 	LOG(INFO) << "end: sleep" << i << std::endl;
		// });
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));

	exec->stop();
	return 0;
}

// link: -lfolly -liberty  -lpthread
//
// link:-ldl -levent
// link: -lboost_context
// link:-std=c++17
// link:-lfmt
// link:-ldouble-conversion
// link:-lgflags -lglog
