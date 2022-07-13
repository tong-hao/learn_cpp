#pragma once

#include <folly/Memory.h>
#include <proxygen/httpserver/RequestHandler.h>

namespace proxygen {
class ResponseHandler;
}

namespace test {

class NoFoundHandler : public proxygen::RequestHandler {
public:
	void onRequest(
	    std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;

	void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;

	void onEOM() noexcept override;

	void onUpgrade(proxygen::UpgradeProtocol proto) noexcept override;

	void requestComplete() noexcept override;

	void onError(proxygen::ProxygenError err) noexcept override;
};

}  // namespace test
