#include <folly/futures/Future.h>
#include <folly/io/async/EventBase.h>
#include <iostream>

int main(int argc, char *argv[]) {
	FLAGS_logtostderr = 1;

	folly::EventBase evb;
	folly::via(&evb)
	    .thenValue([](folly::Unit) { std::cout << "1" << std::endl; })
	    .thenValue([](folly::Unit) { std::cout << "2" << std::endl; });

	folly::via(&evb, []() { std::cout << "3" << std::endl; });

	std::cout << "over" << std::endl;
}
//-liberty

// link:-lfolly -lglog -lgflags -lpthread  -ldl -levent
// link:-ldouble-conversion -lboost_context
// link:-lfmt