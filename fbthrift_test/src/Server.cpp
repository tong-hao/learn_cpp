#include <folly/executors/IOThreadPoolExecutor.h>
#include <folly/init/Init.h>
#include <folly/portability/GFlags.h>
#include <glog/logging.h>
#include <handler/CalcHandler.h>
#include <thrift/lib/cpp/concurrency/ThreadManager.h>
#include <thrift/lib/cpp2/server/ThriftServer.h>
#include <thrift/lib/cpp2/transport/core/ThriftProcessor.h>
#include <thrift/lib/cpp2/transport/rsocket/server/RSRoutingHandler.h>
#include <thread>

DEFINE_int32(chatroom_port, 7777, "Server port");
DEFINE_int32(num_thread_io, 10, "num of io");
DEFINE_int32(num_thread_worker, 10, "num of worker");

using apache::thrift::ThriftServer;
using apache::thrift::ThriftServerAsyncProcessorFactory;
// using CalcHandler;

template <typename ServiceHandler>
static std::shared_ptr<ThriftServer> newServer(
    std::shared_ptr<ServiceHandler> handler, int32_t port) {
	auto proc_factory =
	    std::make_shared<ThriftServerAsyncProcessorFactory<ServiceHandler>>(
	        handler);

	auto ioThreadPool_ =
	    std::make_shared<folly::IOThreadPoolExecutor>(FLAGS_num_thread_io);
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

int main(int argc, char** argv) {
	FLAGS_logtostderr = 1;
	folly::init(&argc, &argv);

	auto ioThreadPool_ =
	    std::make_shared<folly::IOThreadPoolExecutor>(FLAGS_num_thread_io);
	auto handler = std::make_shared<CalcHandler>(ioThreadPool_);
	auto chatroom_server = newServer<CalcHandler>(handler, FLAGS_chatroom_port);
	LOG(INFO) << std::this_thread::get_id()
	          << "Server running on port: " << FLAGS_chatroom_port;
	chatroom_server->serve();

	return 0;
}
