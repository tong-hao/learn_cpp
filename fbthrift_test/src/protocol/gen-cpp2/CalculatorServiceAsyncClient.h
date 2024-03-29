/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/gen/client_h.h>

#include "protocol/gen-cpp2/calc_types.h"

namespace apache {
namespace thrift {
class Cpp2RequestContext;
namespace detail {
namespace ac {
struct ClientRequestContext;
}
}  // namespace detail
namespace transport {
class THeader;
}
}  // namespace thrift
}  // namespace apache

namespace fbthrift {
namespace calc {
namespace cpp2 {

class CalculatorServiceAsyncClient
    : public apache::thrift::GeneratedAsyncClient {
public:
	using apache::thrift::GeneratedAsyncClient::GeneratedAsyncClient;

	char const* getServiceName() const noexcept override {
		return "CalculatorService";
	}

	virtual void add(std::unique_ptr<apache::thrift::RequestCallback> callback,
	                 const ::fbthrift::calc::cpp2::AddRequest& req);
	virtual void add(apache::thrift::RpcOptions& rpcOptions,
	                 std::unique_ptr<apache::thrift::RequestCallback> callback,
	                 const ::fbthrift::calc::cpp2::AddRequest& req);

private:
	void addImpl(
	    apache::thrift::RpcOptions& rpcOptions,
	    std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx,
	    apache::thrift::RequestClientCallback::Ptr callback,
	    const ::fbthrift::calc::cpp2::AddRequest& req);

public:
	virtual void sync_add(::fbthrift::calc::cpp2::AddResponse& _return,
	                      const ::fbthrift::calc::cpp2::AddRequest& req);
	virtual void sync_add(apache::thrift::RpcOptions& rpcOptions,
	                      ::fbthrift::calc::cpp2::AddResponse& _return,
	                      const ::fbthrift::calc::cpp2::AddRequest& req);
	virtual folly::Future<::fbthrift::calc::cpp2::AddResponse> future_add(
	    const ::fbthrift::calc::cpp2::AddRequest& req);
	virtual folly::SemiFuture<::fbthrift::calc::cpp2::AddResponse>
	semifuture_add(const ::fbthrift::calc::cpp2::AddRequest& req);
	virtual folly::Future<::fbthrift::calc::cpp2::AddResponse> future_add(
	    apache::thrift::RpcOptions& rpcOptions,
	    const ::fbthrift::calc::cpp2::AddRequest& req);
	virtual folly::SemiFuture<::fbthrift::calc::cpp2::AddResponse>
	semifuture_add(apache::thrift::RpcOptions& rpcOptions,
	               const ::fbthrift::calc::cpp2::AddRequest& req);
	virtual folly::Future<
	    std::pair<::fbthrift::calc::cpp2::AddResponse,
	              std::unique_ptr<apache::thrift::transport::THeader>>>
	header_future_add(apache::thrift::RpcOptions& rpcOptions,
	                  const ::fbthrift::calc::cpp2::AddRequest& req);
	virtual folly::SemiFuture<
	    std::pair<::fbthrift::calc::cpp2::AddResponse,
	              std::unique_ptr<apache::thrift::transport::THeader>>>
	header_semifuture_add(apache::thrift::RpcOptions& rpcOptions,
	                      const ::fbthrift::calc::cpp2::AddRequest& req);

#if FOLLY_HAS_COROUTINES
	template <int = 0>
	folly::coro::Task<::fbthrift::calc::cpp2::AddResponse> co_add(
	    const ::fbthrift::calc::cpp2::AddRequest& req) {
		co_return co_await semifuture_add(req);
	}
	template <int = 0>
	folly::coro::Task<::fbthrift::calc::cpp2::AddResponse> co_add(
	    apache::thrift::RpcOptions& rpcOptions,
	    const ::fbthrift::calc::cpp2::AddRequest& req) {
		co_return co_await semifuture_add(rpcOptions, req);
	}
#endif  // FOLLY_HAS_COROUTINES
	virtual void add(
	    folly::Function<void(::apache::thrift::ClientReceiveState&&)> callback,
	    const ::fbthrift::calc::cpp2::AddRequest& req);
	static folly::exception_wrapper recv_wrapped_add(
	    ::fbthrift::calc::cpp2::AddResponse& _return,
	    ::apache::thrift::ClientReceiveState& state);
	static void recv_add(::fbthrift::calc::cpp2::AddResponse& _return,
	                     ::apache::thrift::ClientReceiveState& state);
	// Mock friendly virtual instance method
	virtual void recv_instance_add(::fbthrift::calc::cpp2::AddResponse& _return,
	                               ::apache::thrift::ClientReceiveState& state);
	virtual folly::exception_wrapper recv_instance_wrapped_add(
	    ::fbthrift::calc::cpp2::AddResponse& _return,
	    ::apache::thrift::ClientReceiveState& state);

private:
	template <typename Protocol_>
	void addT(
	    Protocol_* prot, apache::thrift::RpcOptions& rpcOptions,
	    std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx,
	    apache::thrift::RequestClientCallback::Ptr callback,
	    const ::fbthrift::calc::cpp2::AddRequest& req);

public:
};

}  // namespace cpp2
}  // namespace calc
}  // namespace fbthrift
