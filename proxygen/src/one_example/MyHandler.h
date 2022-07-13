#pragma once

#include <folly/Memory.h>
#include <proxygen/httpserver/RequestHandler.h>

namespace proxygen {
class ResponseHandler;
}

namespace test {

class Vertex {
public:
	int id_;
	std::map<std::string, std::string> props_;
};

class MyHandler : public proxygen::RequestHandler {
public:
	void onRequest(
	    std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;

	void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;

	void onEOM() noexcept override;

	void onUpgrade(proxygen::UpgradeProtocol proto) noexcept override;

	void requestComplete() noexcept override;

	void onError(proxygen::ProxygenError err) noexcept override;

public:
	static std::map<int, Vertex> vertex_map;

private:
	void onPost(std::string&);
	void onPut(std::string&);
	void onGet(std::string&);
	void onDelete(std::string&);

private:
	std::unique_ptr<folly::IOBuf> body_;
	std::string method_;
};

}  // namespace test

// clang-format off
// add: curl -X POST -d '{"id":100, "props":{"pin_no":"ht", "create_time":"2020-08-01"}}' "localhost:8080/"
// update: curl -X PUT -d '{"id":100, "props":{"pin_no":"ht"}}' "localhost:8080/"
// list: curl localhost:8080
// del: curl -X DELETE -d '{"id":100}' "localhost:8080/"
