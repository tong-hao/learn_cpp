#include <folly/Conv.h>
#include <folly/Unit.h>
#include <folly/executors/Async.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/executors/ThreadedExecutor.h>
#include <folly/futures/Future.h>
#include <folly/init/Init.h>
#include <folly/io/async/EventBase.h>
#include <folly/synchronization/Baton.h>
#include <iostream>
#include <memory>
#include <thread>

int main(int argc, char *argv[]) {
	FLAGS_logtostderr = 1;
	folly::init(&argc, &argv);
	folly::EventBase evb;
	// folly::getIOExecutor().get()
	folly::via(&evb)
	    .thenValue([](folly::Unit) { std::cout << "1" << std::endl; })
	    .thenValue([](folly::Unit) { std::cout << "2" << std::endl; });

	std::cout << "over" << std::endl;
}

// link:-lfolly -lglog -lgflags -lpthread -liberty -ldl -levent
// link: -ldouble-conversion -lboost_context