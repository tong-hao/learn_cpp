/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <folly/Memory.h>
#include <folly/io/async/EventBaseManager.h>
#include <folly/portability/GFlags.h>
#include <folly/portability/Unistd.h>
#include <proxygen/httpserver/HTTPServer.h>
#include <proxygen/httpserver/RequestHandlerFactory.h>

#include "MyHandler.h"
#include "NoFoundHandler.h"

// using proxygen;
using folly::SocketAddress;
using Protocol = proxygen::HTTPServer::Protocol;
using HandlerCreator = std::function<proxygen::RequestHandler*()>;

DEFINE_int32(http_port, 8080, "Port to listen on with HTTP protocol");
DEFINE_string(ip, "localhost", "IP/Hostname to bind to");
DEFINE_int32(threads, 0,
             "Number of threads to listen on. Numbers <= 0 "
             "will use the number of cores on this machine.");

class HandlerFactory : public proxygen::RequestHandlerFactory {
public:
	HandlerFactory(std::map<std::string, HandlerCreator> handlers)
	    : handlers_(handlers) {
	}
	void onServerStart(folly::EventBase* /*evb*/) noexcept override {
	}

	void onServerStop() noexcept override {
	}

	proxygen::RequestHandler* onRequest(
	    proxygen::RequestHandler*,
	    proxygen::HTTPMessage* msg) noexcept override {
		auto path = msg->getPath();
		LOG(INFO) << "path=" << path;
		if (path.empty()) {
			path = "/";
		} else if (path.size() > 1 && path.back() == '/') {
			path.pop_back();
		}

		auto iter = handlers_.find(path);
		if (iter != handlers_.end()) {
			return iter->second();
		}
		LOG(INFO) << "Can not find the handler. path=";  // << path;
		return new test::NoFoundHandler();
	}

private:
	std::map<std::string, HandlerCreator> handlers_;
};

int main(int argc, char* argv[]) {
	FLAGS_logtostderr = 1;  //输出到控制台
	gflags::ParseCommandLineFlags(&argc, &argv, true);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();

	std::vector<proxygen::HTTPServer::IPConfig> ip_configs = {
	    {SocketAddress(FLAGS_ip, FLAGS_http_port, true), Protocol::HTTP},
	};

	//
	std::map<std::string, HandlerCreator> handlers = {
	    {"/", []() { return new test::MyHandler(); }}};

	if (FLAGS_threads <= 0) {
		FLAGS_threads = sysconf(_SC_NPROCESSORS_ONLN);
		CHECK(FLAGS_threads > 0);
	}

	proxygen::HTTPServerOptions options;
	options.threads = static_cast<size_t>(FLAGS_threads);
	options.idleTimeout = std::chrono::milliseconds(60000);
	options.shutdownOn = {SIGINT, SIGTERM};
	options.enableContentCompression = false;
	options.handlerFactories = proxygen::RequestHandlerChain()
	                               .addThen<HandlerFactory>(handlers)
	                               .build();
	// Increase the default flow control to 1MB/10MB
	options.initialReceiveWindow = uint32_t(1 << 20);
	options.receiveStreamWindowSize = uint32_t(1 << 20);
	options.receiveSessionWindowSize = 10 * (1 << 20);
	options.h2cEnabled = true;

	proxygen::HTTPServer server(std::move(options));
	server.bind(ip_configs);

	// Start HTTPServer mainloop in a separate thread
	std::thread t([&]() { server.start(); });
	LOG(INFO) << "listen on: " << FLAGS_http_port;

	t.join();
	return 0;
}
