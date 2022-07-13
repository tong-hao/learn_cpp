#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/executors/ThreadedExecutor.h>
#include <folly/futures/Future.h>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <utility>

int main(int argc, char const *argv[]) {
	//////////////////// ThreadedExecutor ////////////////////
	// folly
	folly::ThreadedExecutor x;
	auto ret = folly::via(&x)
	               .thenValue([&](auto &&) { return 42; })
	               .thenValue([&](int n) { return folly::to<std::string>(n); })
	               .get();
	std::cout << (ret == "42") << std::endl;

	//////////////////// CPUThreadPoolExecutor ////////////////////

	// folly.via(pool)
	folly::CPUThreadPoolExecutor pool{2};
	for (int i = 0; i < 10; i++) {
		folly::via(&pool).thenValue([&](auto &&) {
			std::cout << std::this_thread::get_id() << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		});
	}

	// pool.add(task)
	auto f = [&]() {
		std::cout << "pool.exec " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	};
	for (int i = 0; i < 10; i++) {
		pool.add(f);
	}

	// pool.getPoolStats()
	while (pool.getPoolStats().pendingTaskCount > 0) {
		folly::ThreadPoolExecutor::PoolStats stats = pool.getPoolStats();
		std::cout << "pendingTaskCount:" << stats.pendingTaskCount  // wating
		          << " totalTaskCount:"
		          << stats.totalTaskCount  // incomplete task
		          << " activeThreadCount:"
		          << stats.activeThreadCount  // running task
		          << " idleThreadCount:"
		          << stats.idleThreadCount  //
		          //<< "maxIdleTime:" << stats.maxIdleTime
		          << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	//
	pool.stop();

	return 0;
}

// link: -lfolly -lboost_context -lboost_system -ldl -levent -ldouble-conversion
// link: -lz -llz4 -lsnappy -liberty -lfmt -lssl -lcrypto -lpthread -lglog
// link: -lgflags  -lfolly -fopenmp -lnuma