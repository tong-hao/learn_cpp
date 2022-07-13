/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "NoFoundHandler.h"

#include <iostream>
#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>
#include <string>

namespace test {
// using proxygen;

void NoFoundHandler::onRequest(
    std::unique_ptr<proxygen::HTTPMessage> req) noexcept {
}

void NoFoundHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept {
}

void NoFoundHandler::onEOM() noexcept {
	proxygen::ResponseBuilder(downstream_)
	    .status(404, "OK")
	    .body("Can not handler this request. The url may be error.")
	    .sendWithEOM();
}

void NoFoundHandler::onUpgrade(
    proxygen::UpgradeProtocol /*protocol*/) noexcept {
	// handler doesn't support upgrades
}

void NoFoundHandler::requestComplete() noexcept {
	delete this;
}

void NoFoundHandler::onError(proxygen::ProxygenError /*err*/) noexcept {
	delete this;
}
}  // namespace test
