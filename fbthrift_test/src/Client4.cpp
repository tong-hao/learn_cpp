#include <folly/executors/IOThreadPoolExecutor.h>
#include <folly/executors/ThreadedExecutor.h>
#include <folly/futures/Future.h>
#include <folly/init/Init.h>
#include <folly/io/async/EventBase.h>
#include <memory>
#include <protocol/gen-cpp2/CalculatorService.h>
#include <thrift/lib/cpp/async/TAsyncSocket.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>
#include <thrift/lib/cpp2/async/RocketClientChannel.h>
#include <vector>
#include "thrift_client_pool.h"

DEFINE_string(host, "::1", "host");
DEFINE_int32(port, 7777, "port");

using apache::thrift::HeaderClientChannel;
using apache::thrift::async::TAsyncSocket;
using fbthrift::calc::cpp2::CalculatorServiceAsyncClient;
using folly::IOThreadPoolExecutor;

int main(int argc, char** argv) {
	FLAGS_logtostderr = true;
	folly::init(&argc, &argv);

	// auto socket = TAsyncSocket::newSocket(
	//                 folly::EventBaseManager::get()->getEventBase(),
	//                 FLAGS_host,
	//                 FLAGS_port,
	//                 100);
	// auto client = std::make_unique<CalculatorServiceAsyncClient>(
	//                 HeaderClientChannel::newChannel(socket));

	// folly::EventBase eventBase;
	// auto socket = TAsyncSocket::UniquePtr(new TAsyncSocket(&eventBase,
	// FLAGS_host, FLAGS_port)); auto channel =
	// apache::thrift::RocketClientChannel::newChannel(std::move(socket));
	// auto client =
	// std::make_unique<CalculatorServiceAsyncClient>(std::move(channel));

	try {
		common::ThriftClientPool<CalculatorServiceAsyncClient> pool(2);

		folly::IOThreadPoolExecutor exec{10};

		for (int i = 0; i < 100; i++) {
			folly::via(&exec).thenValue([&pool, i](folly::Unit) mutable {
				const std::atomic<bool>* is_good;
				auto request = ::fbthrift::calc::cpp2::AddRequest();
				request.num1 = i;
				request.num2 = i;
				auto client =
				    pool.getClient(FLAGS_host, FLAGS_port, 0, &is_good);

				client->future_add(request)
				    .thenValue([&](auto&& response) {
					    LOG(INFO) << std::this_thread::get_id();
					    LOG(INFO) << "response code: " << response.get_code();
					    LOG(INFO) << "response message: " << response.get_msg();
				    })
				    .thenError([&](auto&& e) {
					    LOG(ERROR) << "client: error: " << e.what();
				    });
			});
		}

	} catch (apache::thrift::transport::TTransportException& ex) {
		LOG(ERROR) << "Request failed " << ex.what();
	}
}
