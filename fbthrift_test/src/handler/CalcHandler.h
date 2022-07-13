#pragma once

#include <folly/Synchronized.h>
#include <folly/executors/IOThreadPoolExecutor.h>
#include <vector>

#include "protocol/gen-cpp2/CalculatorService.h"

using ::fbthrift::calc::cpp2::AddRequest;
using ::fbthrift::calc::cpp2::AddResponse;

class CalcHandler : public fbthrift::calc::cpp2::CalculatorServiceSvIf {
public:
	CalcHandler(std::shared_ptr<folly::IOThreadPoolExecutor> executors)
	    : executors_(executors){};

	folly::Future<std::unique_ptr<AddResponse>> future_add(
	    std::unique_ptr<AddRequest> req) override;

private:
	std::shared_ptr<folly::IOThreadPoolExecutor> executors_;
};
