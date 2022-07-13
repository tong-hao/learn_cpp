#include <folly/executors/IOThreadPoolExecutor.h>
#include <folly/executors/ThreadedExecutor.h>
#include <folly/futures/Future.h>
#include <folly/init/Init.h>
#include <folly/io/async/EventBase.h>
#include <folly/portability/GFlags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <protocol/gen-cpp2/CalculatorService.h>
#include <thrift/lib/cpp/async/TAsyncSocket.h>
#include <thrift/lib/cpp/concurrency/ThreadManager.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>
#include <thrift/lib/cpp2/async/RocketClientChannel.h>
#include <thrift/lib/cpp2/server/ThriftServer.h>
#include <thrift/lib/cpp2/transport/core/ThriftProcessor.h>
#include <thrift/lib/cpp2/transport/rsocket/server/RSRoutingHandler.h>
#include <memory>
#include <thread>
#include <vector>

#include "handler/CalcHandler.h"
#include "thrift_client_pool.h"

DEFINE_int32(chatroom_port, 7777, "Server port");
DEFINE_int32(num_thread_io, 10, "num of io");
DEFINE_int32(num_thread_worker, 10, "num of worker");

using apache::thrift::HeaderClientChannel;
using apache::thrift::ThriftServer;
using apache::thrift::ThriftServerAsyncProcessorFactory;
using apache::thrift::async::TAsyncSocket;
using fbthrift::calc::cpp2::CalculatorServiceAsyncClient;
using folly::IOThreadPoolExecutor;

class ServiceTest : public testing::Test {
protected:
	template <typename ServiceHandler>
	static std::shared_ptr<ThriftServer> newServer_old(int32_t port) {
		auto handler = std::make_shared<ServiceHandler>();
		auto proc_factory =
		    std::make_shared<ThriftServerAsyncProcessorFactory<ServiceHandler>>(
		        handler);

		auto workers_ = apache::thrift::concurrency::PriorityThreadManager::
		    newPriorityThreadManager(FLAGS_num_thread_worker, true);
		workers_->setNamePrefix("worker");
		workers_->start();

		auto server = std::make_shared<ThriftServer>();
		server->setPort(port);
		server->setProcessorFactory(proc_factory);
		server->addRoutingHandler(
		    std::make_unique<apache::thrift::RSRoutingHandler>());

		server->setIdleTimeout(std::chrono::seconds(0));
		server->setIOThreadPool(ioThreadPool_);
		server->setThreadManager(workers_);
		server->setStopWorkersOnStopListening(false);

		return server;
	}

	template <typename ServiceHandler>
	static std::shared_ptr<ThriftServer> newServer(
	    std::shared_ptr<ServiceHandler> handler, int32_t port) {
		// auto handler = std::make_shared<ServiceHandler>();
		// auto proc_factory =
		//     std::make_shared<ThriftServerAsyncProcessorFactory<ServiceHandler>>(
		//         handler);
		// auto server = std::make_shared<ThriftServer>();
		// server->setPort(port);
		// server->setProcessorFactory(proc_factory);
		// server->addRoutingHandler(
		//     std::make_unique<apache::thrift::RSRoutingHandler>());
		// server->setNumIOWorkerThreads(FLAGS_num_thread_worker);
		// server->setIdleTimeout(std::chrono::seconds(0));
		// // server->setIOThreadPool(ioThreadPool_);
		// server->setStopWorkersOnStopListening(true);

		auto processor_factory =
		    std::make_shared<ThriftServerAsyncProcessorFactory<ServiceHandler>>(
		        handler);
		auto server = std::make_unique<ThriftServer>();
		server->setPort(port);
		server->setProcessorFactory(processor_factory);
		server->addRoutingHandler(
		    std::make_unique<apache::thrift::RSRoutingHandler>());
		server->setNumIOWorkerThreads(FLAGS_num_thread_worker);

		return server;
	}

	static void SetUpTestCase() {
		ioThreadPool_ =
		    std::make_shared<folly::IOThreadPoolExecutor>(FLAGS_num_thread_io);

		std::thread th([]() {
			auto handler = std::make_shared<CalcHandler>(ioThreadPool_);
			chatroom_server = ServiceTest::newServer<CalcHandler>(
			    handler, FLAGS_chatroom_port);
			LOG(INFO) << std::this_thread::get_id()
			          << "Server running on port: " << FLAGS_chatroom_port;
			chatroom_server->serve();
		});
		th.detach();
		sleep(2);
	}

	static void TearDownTestCase() {
		// quick_exit(EXIT_SUCCESS);
		ioThreadPool_.reset();
		chatroom_server.reset();
	}

	static std::shared_ptr<ThriftServer> chatroom_server;
	static std::shared_ptr<folly::IOThreadPoolExecutor> ioThreadPool_;
};
std::shared_ptr<ThriftServer> ServiceTest::chatroom_server;
std::shared_ptr<folly::IOThreadPoolExecutor> ServiceTest::ioThreadPool_;

TEST_F(ServiceTest, base) {
	const std::atomic<bool>* is_good;
	common::ThriftClientPool<CalculatorServiceAsyncClient> pool(2);
	auto client = pool.getClient("127.0.0.1", FLAGS_chatroom_port, 0, &is_good);

	std::vector<folly::Future<fbthrift::calc::cpp2::AddResponse>> vct;
	for (int i = 0; i < 1024; i++) {
		fbthrift::calc::cpp2::AddRequest request;
		request.num1 = i;
		request.num2 = 2;
		auto f = client->future_add(request);
		vct.emplace_back(std::move(f));
	}
	folly::collectAll(vct).get();
}

int main(int argc, char** argv) {
	FLAGS_logtostderr = 1;
	testing::InitGoogleTest(&argc, argv);
	folly::init(&argc, &argv);

	return RUN_ALL_TESTS();
}