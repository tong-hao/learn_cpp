/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "MyHandler.h"

#include <folly/dynamic.h>
#include <folly/json.h>
#include <iostream>
#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>
#include <string>

namespace test {
// using proxygen;

std::map<int, Vertex> MyHandler::vertex_map{};

void MyHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> req) noexcept {
	LOG(INFO) << "onRequest: " << std::endl;
	method_ = req->getMethodString();

	LOG(INFO) << req->getClientIP() << ":" << req->getClientPort();
	LOG(INFO) << req->getMethod().value();
	LOG(INFO) << req->getPath();
	LOG(INFO) << req->getQueryString();
}

void MyHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept {
	LOG(INFO) << "onBody: " << std::endl;
	if (body_) {
		body_->prependChain(std::move(body));
	} else {
		body_ = std::move(body);
	}
}

void MyHandler::onGet(std::string& response) {
	folly::dynamic vertices = folly::dynamic::array;
	for (auto iter = vertex_map.begin(); iter != vertex_map.end(); iter++) {
		auto id = iter->second.id_;
		folly::dynamic props = folly::dynamic::object;
		for (auto p = iter->second.props_.begin();
		     p != iter->second.props_.end(); p++) {
			props.insert(p->first, p->second);
		}
		folly::dynamic vertex =
		    folly::dynamic::object("id", id)("props", props);
		vertices.push_back(vertex);
	}

	folly::dynamic res = folly::dynamic::object("code", 0)("msg", "success")(
	    "vertices", vertices);

	response = folly::toJson(res);
}

void MyHandler::onPost(std::string& response) {
	const char* p = reinterpret_cast<const char*>(body_->data());
	folly::dynamic parsed = folly::parseJson(std::string(p, body_->length()));
	Vertex v = Vertex();
	v.id_ = parsed["id"].getInt();

	for (auto p : parsed["props"].items()) {
		v.props_[p.first.getString()] = p.second.getString();
	}
	vertex_map[v.id_] = v;

	folly::dynamic res = folly::dynamic::object("code", 0)("msg", "success");
	response = folly::toJson(res);
}

void MyHandler::onDelete(std::string& response) {
	const char* p = reinterpret_cast<const char*>(body_->data());
	folly::dynamic parsed = folly::parseJson(std::string(p, body_->length()));
	auto id = parsed["id"].getInt();
	vertex_map.erase(id);

	folly::dynamic res = folly::dynamic::object("code", 0)("msg", "success");
	response = folly::toJson(res);
}

void MyHandler::onEOM() noexcept {
	LOG(INFO) << "onEOM: " << std::endl;
	std::string response;
	if (method_ == "GET") {
		onGet(response);
	} else if (method_ == "POST") {
		onPost(response);
	} else if (method_ == "PUT") {
		onPost(response);
	} else if (method_ == "DELETE") {
		onDelete(response);
	} else {
		response.append("Can not support ").append(method_).append(" method. ");
	}

	proxygen::ResponseBuilder(downstream_)
	    .status(200, "OK")
	    .body(response)
	    .sendWithEOM();
}

void MyHandler::onUpgrade(proxygen::UpgradeProtocol /*protocol*/) noexcept {
	LOG(INFO) << "onUpgrade: ";

	// handler doesn't support upgrades
}

void MyHandler::requestComplete() noexcept {
	LOG(INFO) << "requestComplete: ";

	delete this;
}

void MyHandler::onError(proxygen::ProxygenError /*err*/) noexcept {
	LOG(INFO) << "onError: ";

	delete this;
}
}  // namespace test
