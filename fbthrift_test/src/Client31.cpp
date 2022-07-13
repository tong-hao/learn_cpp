#include <folly/ThreadLocal.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/executors/IOThreadPoolExecutor.h>
#include <folly/executors/ThreadedExecutor.h>
#include <folly/futures/Future.h>
#include <folly/init/Init.h>
#include <folly/io/async/EventBase.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <thrift/lib/cpp/async/TAsyncSocket.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>
#include <thrift/lib/cpp2/async/ReconnectingRequestChannel.h>
#include <thrift/lib/cpp2/async/RocketClientChannel.h>
#include <utility>  // std::pair
#include <vector>
#include "protocol/gen-cpp2/CalculatorService.h"
#include "protocol/gen-cpp2/CalculatorServiceAsyncClient.h"

DEFINE_string(host, "::1", "host");
DEFINE_int32(port, 7777, "port");

using apache::thrift::HeaderClientChannel;
using apache::thrift::async::TAsyncSocket;
using fbthrift::calc::cpp2::CalculatorServiceAsyncClient;

folly::ThreadLocal<std::map<std::pair<std::string, folly::EventBase*>,
                            std::shared_ptr<CalculatorServiceAsyncClient>>>
    client_map_;

auto threadFactory =
    std::make_shared<folly::NamedThreadFactory>("ThreadFactory");
auto ioThreadPool =
    std::make_shared<folly::IOThreadPoolExecutor>(3, std::move(threadFactory));

auto createClient(folly::EventBase* evb) {
	struct Deleter {
		explicit Deleter(folly::EventBase* evb) : evb_(evb) {
		}

		void operator()(CalculatorServiceAsyncClient* t) {
			// We have to wait for it to avoid memory leak.
			evb_->runInEventBaseThreadAndWait([t] {
				if (!t)
					delete t;
			});
		}

		folly::EventBase* evb_;
	};

	Deleter deleter(evb);

	LOG(INFO) << "createClient...";
	std::string ipAddr = FLAGS_host;
	int32_t port = FLAGS_port;
	int64_t timeout = 10000;
	bool compatibility = false;

	std::shared_ptr<CalculatorServiceAsyncClient> client(nullptr);

	evb->runInEventBaseThreadAndWait([&]() {
		TAsyncSocket::UniquePtr socket =
		    TAsyncSocket::UniquePtr(new TAsyncSocket(evb, ipAddr, port, 10000));
		auto channel =
		    apache::thrift::HeaderClientChannel::newChannel(std::move(socket));
		channel->setTimeout(10000);
		channel->setProtocolId(apache::thrift::protocol::T_BINARY_PROTOCOL);
		channel->setClientType(THRIFT_FRAMED_DEPRECATED);

		client.reset(new CalculatorServiceAsyncClient(std::move(channel)));
	});

	return client;
}

auto getClient(std::string host, folly::EventBase* event_base) {
	std::pair<std::string, folly::EventBase*> k =
	    std::make_pair(host, event_base);

	auto it = client_map_->find(k);
	if (it != client_map_->end()) {
		return it->second;
	}
	auto client = createClient(event_base);

	std::cout << "getProtocolId():" << client->getChannel()->getProtocolId()
	          << std::endl;

	client_map_->emplace(k, client);

	return client;
}

void doTask(int i) {
	// int i = 1;
	// folly::EventBase* evb = p.second;
	auto onResponse = [&](auto&& response) {
		LOG(INFO) << "response code: " << response.get_code();
		LOG(INFO) << "response message: " << response.get_msg();
	};

	auto onError = [&](auto&& e) {
		LOG(ERROR) << "client: error: " << e.what();
	};

	auto request = ::fbthrift::calc::cpp2::AddRequest();
	request.num1 = 1;
	request.num2 = i;

	// std::shared_ptr<folly::EventBase> event_base_(new folly::EventBase());
	auto client = getClient("127.0.0.1", ioThreadPool->getEventBase());

	LOG(INFO) << "future_add: ";
	auto f =
	    client->future_add(request).thenValue(onResponse).thenError(onError);
}

int main(int argc, char** argv) {
	FLAGS_logtostderr = true;
	folly::init(&argc, &argv);

	auto onResponse = [&](auto&& response) {
		LOG(INFO) << "response code: " << response.get_code();
		LOG(INFO) << "response message: " << response.get_msg();
	};

	auto onError = [&](auto&& e) {
		LOG(ERROR) << "client: error: " << e.what();
	};

	for (int i = 0; i < 10; i++) {
		LOG(INFO) << i;

		auto evb = ioThreadPool->getEventBase();
		auto request = ::fbthrift::calc::cpp2::AddRequest();
		request.num1 = i;
		request.num2 = i;

		auto client = getClient("127.0.0.1", evb);

		LOG(INFO) << "future_add: ";
		auto f = client->future_add(request)
		             .thenValue(onResponse)
		             .thenError(onError);
	}

	return 0;
}
