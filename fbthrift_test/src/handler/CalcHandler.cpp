#include "handler/CalcHandler.h"

#include <folly/Conv.h>
#include <folly/Hash.h>
#include <folly/RWSpinLock.h>
#include <folly/Random.h>
#include <folly/Range.h>
#include <folly/String.h>
#include <folly/ThreadLocal.h>
#include <folly/Varint.h>
#include <folly/dynamic.h>
#include <folly/futures/Future.h>
#include <folly/init/Init.h>
#include <folly/json.h>
#include <glog/logging.h>
#include <thread>

folly::Future<std::unique_ptr<AddResponse>> CalcHandler::future_add(
    std::unique_ptr<AddRequest> req) {
	auto doAdd = [request = std::move(req)](folly::Unit) mutable {
		auto thread_name = std::this_thread::get_id();
		LOG(INFO) << "begin:CalcHandler::add " << thread_name;
		std::unique_ptr<AddResponse> response;
		auto num1 = request->get_num1();
		auto num2 = request->get_num2();

		response->set_code(200);
		auto msg = folly::sformat(" num1={}, num2={}, result={}", num1, num2,
		                          (num1 + num2));
		response->set_msg(msg);
		std::this_thread::sleep_for(std::chrono::seconds(3));

		LOG(INFO) << "end:CalcHandler::add " << thread_name;
		return response;
	};

	return folly::via(executors_.get()).thenValue(std::move(doAdd));
}