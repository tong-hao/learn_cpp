#include <folly/init/Init.h>
#include <folly/io/async/EventBase.h>
#include <thrift/lib/cpp/async/TAsyncSocket.h>
#include <thrift/lib/cpp2/async/RocketClientChannel.h>

#include "protocol/gen-cpp2/CalculatorService.h"

DEFINE_string(host, "::1", "host");
DEFINE_int32(port, 7777, "port");

using apache::thrift::async::TAsyncSocket;
using fbthrift::calc::cpp2::CalculatorServiceAsyncClient;

int main(int argc, char** argv) {
	FLAGS_logtostderr = true;
	folly::init(&argc, &argv);

	folly::EventBase eventBase;
	auto socket = TAsyncSocket::UniquePtr(
	    new TAsyncSocket(&eventBase, FLAGS_host, FLAGS_port));
	auto channel =
	    apache::thrift::RocketClientChannel::newChannel(std::move(socket));
	auto client =
	    std::make_unique<CalculatorServiceAsyncClient>(std::move(channel));

	try {
		auto response = ::fbthrift::calc::cpp2::AddResponse();
		auto request = ::fbthrift::calc::cpp2::AddRequest();
		request.num1 = 1;
		request.num2 = 7;

		client->sync_add(response, request);
		LOG(INFO) << "response code: " << response.get_code();
		LOG(INFO) << "response message: " << response.get_msg();

	} catch (apache::thrift::transport::TTransportException& ex) {
		LOG(ERROR) << "Request failed " << ex.what();
	}
}
