#include "Server.h"

void HttpConnection::start() {
	read_request();
}

void HttpConnection::read_request() {
	auto self(shared_from_this());
	boost::asio::async_read_until(
	    socket_, request_, "\r\n\r\n",
	    [this, self](boost::system::error_code ec, std::size_t length) {
		    if (!ec) {
			    std::cout << "body:"
			              << boost::asio::buffer_cast<const char*>(
			                     request_.data())
			              << std::endl;

			    std::istream stream(&request_);
			    std::string line;
			    getline(stream, line);

			    std::vector<std::string> tokens;
			    boost::split(tokens, line, boost::is_any_of(" "));

			    if (tokens.size() != 3) {
				    write_response(400, "Bad Request", "");
				    return;
			    }

			    method_ = tokens[0];
			    path_ = tokens[1];
			    http_version_ = tokens[2];
			    boost::trim(path_);

			    std::cout << "recv a request, path:" << path_
			              << ", method:" << method_
			              << ", version:" << http_version_ << std::endl;

			    read_headers();
		    }
	    });
}

std::map<std::string, std::string> HttpConnection::parse_get() {
	std::map<std::string, std::string> params;
	std::string decoded_uri = url_decode(path_);
	std::size_t query_pos = decoded_uri.find('?');
	if (query_pos != std::string::npos) {
		std::string query_string = decoded_uri.substr(query_pos + 1);

		std::vector<std::string> items;
		boost::algorithm::split(items, query_string,
		                        boost::algorithm::is_any_of("&"));
		for (const std::string& item : items) {
			std::vector<std::string> parts;
			boost::algorithm::split(parts, item,
			                        boost::algorithm::is_any_of("="));
			if (parts.size() == 2) {
				std::string key = url_decode(parts[0]);
				std::string value = url_decode(parts[1]);
				params.emplace(key, value);
			}
		}
	}
	return params;
}

void HttpConnection::parse_post() {
	std::istreambuf_iterator<char> begin(&request_), end;
	std::string body(begin, end);
	std::cout << "post body:" << body << std::endl;
	if (!body.empty()) {
		if (headers_.count("ContentType") &&
		    headers_["Content-Type"] == "application/json") {
			// 解析 JSON 数据
			try {
				std::cout << "post body:" << body << std::endl;
				// nlohmann::json json_body = nlohmann::json::parse(body);
			} catch (const std::exception& ex) {
				std::cerr << "Failed to parse JSON body: " << ex.what()
				          << std::endl;
			}
		}
	}
	// ...
}

void HttpConnection::read_headers() {
	auto self(shared_from_this());
	boost::asio::async_read_until(
	    socket_, request_, "\r\n",
	    [this, self](boost::system::error_code ec, std::size_t length) {
		    if (!ec) {
			    std::istream stream(&request_);
			    std::string header;

			    while (getline(stream, header) && header != "\r") {
				    size_t pos = header.find(':');
				    if (pos != std::string::npos) {
					    std::string key = header.substr(0, pos);
					    boost::trim(key);

					    std::string value = header.substr(pos + 1);
					    boost::trim(value);

					    headers_.insert(std::make_pair(key, value));
					    std::cout << "key=" << key << ", value=" << value
					              << std::endl;
				    }
			    }

			    handle_request();
		    }
	    });
}

void HttpConnection::handle_request() {
	std::string body;
	std::ostringstream response_stream;

	if (method_ != "GET" && method_ != "POST") {
		write_response(405, "Method Not Allowed", "");
		return;
	}

	if (method_ == "GET") {
		auto params = parse_get();
		std::cout << "get params:";
		for (auto& item : params) {
			std::cout << item.first << "=" << item.second << std::endl;
		}
	} else {
		parse_post();
	}

	auto path = path_;
	auto pos = path.find("?");
	if (pos != std::string::npos) {
		path = path.substr(0, pos);
	}
	std::cout << "path:" << path << std::endl;

	if (path == "/ping") {
		write_response(200, "OK", "pong");
	} else if (path == "/hello") {
		write_response(200, "OK", "Hello, World!");
	} else {
		write_response(404, "Not Found", "");
	}
}

void HttpConnection::write_response(int status,
                                    const std::string& status_message,
                                    const std::string& body) {
	std::ostringstream response_stream;

	response_stream << "HTTP/1.1 " << status << " " << status_message << "\r\n";
	response_stream << "Content-Type: application/json\r\n";
	response_stream << "Content-Length: " << body.length() << "\r\n";
	response_stream << "Connection: close\r\n\r\n";

	if (!body.empty()) {
		response_stream << body;
	}

	std::string response_str = response_stream.str();

	auto self(shared_from_this());
	boost::asio::async_write(
	    socket_, boost::asio::buffer(response_str),
	    [this, self](boost::system::error_code ec, std::size_t length) {
		    if (!ec) {
			    boost::system::error_code ignored_ec;
			    socket_.shutdown(tcp::socket::shutdown_both, ignored_ec);
		    }
	    });
}

std::string HttpConnection::url_decode(const std::string& str) {
	std::string decoded;
	for (std::size_t i = 0; i < str.size(); ++i) {
		if (str[i] == '%') {
			if (i + 2 < str.size() && isxdigit(str[i + 1]) &&
			    isxdigit(str[i + 2])) {
				int code = strtol(str.substr(i + 1, 2).c_str(), nullptr, 16);
				decoded += static_cast<char>(code);
				i += 2;
			} else {
				decoded += str[i];
			}
		} else if (str[i] == '+') {
			decoded += ' ';
		} else {
			decoded += str[i];
		}
	}
	return decoded;
}

HttpServer::HttpServer(boost::asio::io_service& io_service,
                       const std::string& address, unsigned short port)
    : acceptor_(io_service), socket_(io_service) {
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(address, std::to_string(port));
	tcp::endpoint endpoint = *resolver.resolve(query);

	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(boost::asio::socket_base::reuse_address(true));
	acceptor_.bind(endpoint);
	acceptor_.listen();

	accept_connection();
	io_service.run();
}

void HttpServer::accept_connection() {
	acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
		if (!ec) {
			std::make_shared<HttpConnection>(std::move(socket_))->start();
		}

		accept_connection();
	});
}

int main(int argc, char* argv[]) {
	try {
		// if (argc != 3) {
		// 	std::cerr << "Usage: http_server <address> <port>\n";
		// 	return 1;
		// }
		boost::asio::io_service io_service;
		std::thread([&]() {
			try {
				HttpServer server(io_service, "0.0.0.0", 8080);
			} catch (std::exception& e) {
				std::cerr << "Exception: " << e.what() << "\n";
			}
		}).detach();

		while (true) {
		}

		// io_service.run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
