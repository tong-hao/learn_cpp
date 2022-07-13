#include <folly/Conv.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/executors/ThreadedExecutor.h>
#include <folly/futures/Future.h>
#include <folly/init/Init.h>
#include <iostream>
#include <memory>
#include <thread>

using namespace folly;
using namespace std;

folly::CPUThreadPoolExecutor executors{2};

int convertID(std::string id) {
	cout << "convertID:" << id << endl;

	return 100;
}

int AddVertex(int x) {
	// do something with x
	cout << "add vertex(" << x << ")" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(20));

	return x + 1;
}

// thrift
Future<int> future_AddVertex(std::string id) {
	cout << "begin future_AddVertex" << endl;

	cout << "1.making Promise" << endl;
	Promise<std::string> p;

	cout << "2.promise getSemiFuture" << endl;
	Future<std::string> f = p.getSemiFuture().via(&executors);

	cout << "3.futrue thenValue" << endl;
	auto f2 = move(f).via(&executors).thenValue(convertID);
	auto f3 = move(f2).via(&executors).thenValue(AddVertex);

	cout << "4.promist setValue" << endl;
	p.setValue(id);

	cout << "end future_AddVertex" << endl;
	return f3;
}

int main(int argc, char *argv[]) {
	FLAGS_logtostderr = 1;
	folly::init(&argc, &argv);

	auto onResponse = [](int ret) {
		std::cout << "onResponse:" << ret << std::endl;
	};

	auto onError = [](auto &&e) {
		std::cout << "onError:" << e.what() << std::endl;
	};

	for (int i = 0; i < 5; i++) {
		auto f = future_AddVertex(folly::to<std::string>(i));
		std::move(f).thenValue(onResponse).thenError(onError);
	}

	executors.stop();

	// one by one
	Promise<Unit> p;
	Future<Unit> f = p.getFuture();

	auto func1 = [](folly::Unit) { return "abc"; };
	auto func2 = [](std::string s) { return 8; };

	Future<std::string> f1 = std::move(f).thenValue(func1);
	Future<int> f2 = std::move(f1).thenValue(func2);

	p.setValue();

	auto ret = std::move(f2).get();
	std::cout << "one by one : " << ret << std::endl;

	return 0;
}

// link: -lfolly -lboost_context -lboost_system -ldl -levent -ldouble-conversion
// link: -lz -llz4 -lsnappy -liberty -lfmt -lssl -lcrypto -lpthread -lglog
// link: -lgflags  -lfolly -fopenmp -lnuma