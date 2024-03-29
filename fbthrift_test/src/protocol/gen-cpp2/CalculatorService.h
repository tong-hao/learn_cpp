/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/gen/service_h.h>

#include "protocol/gen-cpp2/CalculatorServiceAsyncClient.h"
#include "protocol/gen-cpp2/calc_types.h"

namespace folly {
class IOBuf;
class IOBufQueue;
}  // namespace folly
namespace apache {
namespace thrift {
class Cpp2RequestContext;
class BinaryProtocolReader;
class CompactProtocolReader;
namespace transport {
class THeader;
}
}  // namespace thrift
}  // namespace apache

namespace fbthrift {
namespace calc {
namespace cpp2 {

class CalculatorServiceSvAsyncIf {
public:
	virtual ~CalculatorServiceSvAsyncIf() {
	}
	virtual void async_tm_add(
	    std::unique_ptr<apache::thrift::HandlerCallback<
	        std::unique_ptr<::fbthrift::calc::cpp2::AddResponse>>>
	        callback,
	    std::unique_ptr<::fbthrift::calc::cpp2::AddRequest> req) = 0;
	virtual folly::Future<std::unique_ptr<::fbthrift::calc::cpp2::AddResponse>>
	future_add(std::unique_ptr<::fbthrift::calc::cpp2::AddRequest> req) = 0;
	virtual folly::SemiFuture<
	    std::unique_ptr<::fbthrift::calc::cpp2::AddResponse>>
	semifuture_add(std::unique_ptr<::fbthrift::calc::cpp2::AddRequest> req) = 0;
};

class CalculatorServiceAsyncProcessor;

class CalculatorServiceSvIf : public CalculatorServiceSvAsyncIf,
                              public apache::thrift::ServerInterface {
public:
	typedef CalculatorServiceAsyncProcessor ProcessorType;
	std::unique_ptr<apache::thrift::AsyncProcessor> getProcessor() override;
	virtual void add(
	    ::fbthrift::calc::cpp2::AddResponse& /*_return*/,
	    std::unique_ptr<::fbthrift::calc::cpp2::AddRequest> /*req*/);
	folly::Future<std::unique_ptr<::fbthrift::calc::cpp2::AddResponse>>
	future_add(
	    std::unique_ptr<::fbthrift::calc::cpp2::AddRequest> req) override;
	folly::SemiFuture<std::unique_ptr<::fbthrift::calc::cpp2::AddResponse>>
	semifuture_add(
	    std::unique_ptr<::fbthrift::calc::cpp2::AddRequest> req) override;
	void async_tm_add(
	    std::unique_ptr<apache::thrift::HandlerCallback<
	        std::unique_ptr<::fbthrift::calc::cpp2::AddResponse>>>
	        callback,
	    std::unique_ptr<::fbthrift::calc::cpp2::AddRequest> req) override;
};

class CalculatorServiceSvNull : public CalculatorServiceSvIf {
public:
	void add(
	    ::fbthrift::calc::cpp2::AddResponse& /*_return*/,
	    std::unique_ptr<::fbthrift::calc::cpp2::AddRequest> /*req*/) override;
};

class CalculatorServiceAsyncProcessor
    : public ::apache::thrift::GeneratedAsyncProcessor {
public:
	const char* getServiceName() override;
	void getServiceMetadata(
	    apache::thrift::metadata::ThriftServiceMetadataResponse& response)
	    override;
	using BaseAsyncProcessor = void;

protected:
	CalculatorServiceSvIf* iface_;

public:
	void process(apache::thrift::ResponseChannelRequest::UniquePtr req,
	             std::unique_ptr<folly::IOBuf> buf,
	             apache::thrift::protocol::PROTOCOL_TYPES protType,
	             apache::thrift::Cpp2RequestContext* context,
	             folly::EventBase* eb,
	             apache::thrift::concurrency::ThreadManager* tm) override;

protected:
	bool isOnewayMethod(
	    const folly::IOBuf* buf,
	    const apache::thrift::transport::THeader* header) override;
	std::shared_ptr<folly::RequestContext> getBaseContextForRequest() override;

private:
	static std::unordered_set<std::string> onewayMethods_;

public:
	using ProcessFunc =
	    GeneratedAsyncProcessor::ProcessFunc<CalculatorServiceAsyncProcessor>;
	using ProcessMap = GeneratedAsyncProcessor::ProcessMap<ProcessFunc>;
	static const CalculatorServiceAsyncProcessor::ProcessMap&
	getBinaryProtocolProcessMap();
	static const CalculatorServiceAsyncProcessor::ProcessMap&
	getCompactProtocolProcessMap();

private:
	static const CalculatorServiceAsyncProcessor::ProcessMap binaryProcessMap_;
	static const CalculatorServiceAsyncProcessor::ProcessMap compactProcessMap_;

private:
	template <typename ProtocolIn_, typename ProtocolOut_>
	void _processInThread_add(
	    apache::thrift::ResponseChannelRequest::UniquePtr req,
	    std::unique_ptr<folly::IOBuf> buf,
	    apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb,
	    apache::thrift::concurrency::ThreadManager* tm);
	template <typename ProtocolIn_, typename ProtocolOut_>
	void process_add(apache::thrift::ResponseChannelRequest::UniquePtr req,
	                 std::unique_ptr<folly::IOBuf> buf,
	                 apache::thrift::Cpp2RequestContext* ctx,
	                 folly::EventBase* eb,
	                 apache::thrift::concurrency::ThreadManager* tm);
	template <class ProtocolIn_, class ProtocolOut_>
	static folly::IOBufQueue return_add(
	    int32_t protoSeqId, apache::thrift::ContextStack* ctx,
	    ::fbthrift::calc::cpp2::AddResponse const& _return);
	template <class ProtocolIn_, class ProtocolOut_>
	static void throw_wrapped_add(
	    apache::thrift::ResponseChannelRequest::UniquePtr req,
	    int32_t protoSeqId, apache::thrift::ContextStack* ctx,
	    folly::exception_wrapper ew,
	    apache::thrift::Cpp2RequestContext* reqCtx);

public:
	CalculatorServiceAsyncProcessor(CalculatorServiceSvIf* iface)
	    : iface_(iface) {
	}

	virtual ~CalculatorServiceAsyncProcessor() {
	}
};

}  // namespace cpp2
}  // namespace calc
}  // namespace fbthrift
