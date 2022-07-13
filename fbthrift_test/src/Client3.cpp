#include <folly/ThreadLocal.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/executors/IOThreadPoolExecutor.h>
#include <folly/executors/ThreadedExecutor.h>
#include <folly/futures/Future.h>
#include <folly/init/Init.h>
#include <folly/io/async/EventBase.h>
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
std::shared_ptr<CalculatorServiceAsyncClient> client_;

auto threadFactory =
    std::make_shared<folly::NamedThreadFactory>("ThreadFactory");
auto ioThreadPool =
    std::make_shared<folly::IOThreadPoolExecutor>(3, std::move(threadFactory));

std::shared_ptr<CalculatorServiceAsyncClient> createClient_old(
    folly::EventBase* event_base) {
	LOG(INFO) << "createClient...";

	//   auto socket = TAsyncSocket::newSocket(
	//                 event_base,
	//                 FLAGS_host,
	//                 FLAGS_port,
	//                 100);
	// auto client = std::make_shared<CalculatorServiceAsyncClient>(
	//                 HeaderClientChannel::newChannel(socket));

	std::shared_ptr<CalculatorServiceAsyncClient> client;
	event_base->runImmediatelyOrRunInEventBaseThreadAndWait([event_base,
	                                                         &client]() {
		TAsyncSocket::UniquePtr socket = TAsyncSocket::UniquePtr(
		    new TAsyncSocket(event_base, FLAGS_host, FLAGS_port, 10000));

		auto channel =
		    apache::thrift::RocketClientChannel::newChannel(std::move(socket));
		// auto client =
		// std::make_shared<CalculatorServiceAsyncClient>(std::move(channel));

		client.reset(new CalculatorServiceAsyncClient(std::move(channel)));

		// client = std::make_shared<CalculatorServiceAsyncClient>(new
		// CalculatorServiceAsyncClient(std::move(channel)), [event_base](auto *
		// p) {
		//    event_base->runImmediatelyOrRunInEventBaseThreadAndWait([p] {
		//      LOG(INFO) << "runImmediatelyOrRunInEventBaseThreadAndWait";
		//      delete p;
		//    });
		//  });
	});

	return client;
}

std::shared_ptr<CalculatorServiceAsyncClient> createClient(
    folly::EventBase* evb) {
	LOG(INFO) << "createClient...";
	std::string ipAddr = FLAGS_host;
	int32_t port = FLAGS_port;
	int64_t timeout = 10000;
	bool compatibility = true;

	auto channel = apache::thrift::ReconnectingRequestChannel::newChannel(
	    *evb,
	    [compatibility, ipAddr, port, timeout](folly::EventBase& eb) mutable {
		    static thread_local int connectionCount = 0;
		    VLOG(2) << "Connecting to " << ipAddr << ":" << port << " for "
		            << ++connectionCount << " times";
		    TAsyncSocket::UniquePtr socket;

		    eb.runImmediatelyOrRunInEventBaseThreadAndWait(
		        [&socket, &eb, ipAddr, port]() {
			        socket = TAsyncSocket::UniquePtr(
			            new TAsyncSocket(&eb, ipAddr, port, 10000));
		        });

		    auto headerClientChannel =
		        apache::thrift::HeaderClientChannel::newChannel(
		            std::move(socket));
		    if (timeout > 0) {
			    headerClientChannel->setTimeout(timeout);
		    }

		    if (compatibility) {
			    headerClientChannel->setProtocolId(
			        apache::thrift::protocol::T_BINARY_PROTOCOL);
		    }
		    return headerClientChannel;
	    });

	auto client =
	    std::make_shared<CalculatorServiceAsyncClient>(std::move(channel));

	return client;
}

std::shared_ptr<CalculatorServiceAsyncClient> getClient(
    std::string host, folly::EventBase* event_base) {
	std::pair<std::string, folly::EventBase*> k =
	    std::make_pair(host, event_base);

	auto it = client_map_->find(k);
	if (it != client_map_->end()) {
		return std::move(it->second);
	}
	auto client = createClient(event_base);

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

int main1(int argc, char** argv) {
	FLAGS_logtostderr = true;
	folly::init(&argc, &argv);

	// std::shared_ptr<folly::EventBase> event_base(new folly::EventBase());
	// client_ = getClient("127.0.0.1", event_base);

	// folly::CPUThreadPoolExecutor executor{3};
	auto evb = ioThreadPool->getEventBase();
	for (int i = 0; i < 10; i++) {
		LOG(INFO) << i;
		folly::Promise<int> p;
		p.getFuture().via(evb).thenValue(doTask);
		p.setValue(i);
	}

	return 0;
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
		evb->runInEventBaseThread([&]() {
			LOG(INFO) << "thread name=" << evb->getName()
			          << std::this_thread::get_id();
			auto request = ::fbthrift::calc::cpp2::AddRequest();
			request.num1 = i;
			request.num2 = i;

			auto client = getClient("127.0.0.1", evb);

			LOG(INFO) << "future_add: ";
			auto f = client->future_add(
			    request);  //.thenValue(onResponse).thenError(onError);
		});
		/*folly::via(evb, [&]() {
		  //LOG(INFO) << "thread name=" << evb->getName();
		  auto request = ::fbthrift::calc::cpp2::AddRequest();
		  request.num1 = i;
		  request.num2 = i;

		  auto client = getClient("127.0.0.1", evb);

		  LOG(INFO) << "future_add: ";
		  auto f =
		client->future_add(request).thenValue(onResponse).thenError(onError);
		});*/
	}

	return 0;
}
