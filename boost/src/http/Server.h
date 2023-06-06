#ifndef SERVER
#define SERVER

#include <iostream>

#include "boost/algorithm/string.hpp"
#include "boost/asio.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"

using boost::asio::ip::tcp;
using namespace boost::property_tree;

class HttpConnection : public std::enable_shared_from_this<HttpConnection> {
public:
	HttpConnection(tcp::socket socket) : socket_(std::move(socket)) {
	}

	void start();

private:
	void read_request();

	std::string url_decode(const std::string& str);

	std::map<std::string, std::string> parse_query_string(
	    const std::string& query_string);

	std::map<std::string, std::string> parse_get();

	void parse_post();

	void read_headers();

	void handle_request();

	void write_response(int status, const std::string& status_message,
	                    const std::string& body);

private:
	tcp::socket socket_;
	boost::asio::streambuf request_;
	std::string method_;
	std::string path_;
	std::string http_version_;
	std::map<std::string, std::string> headers_;
};

class HttpServer {
public:
	HttpServer(boost::asio::io_service& io_service, const std::string& address,
	           unsigned short port);

private:
	void accept_connection();

private:
	tcp::acceptor acceptor_;
	tcp::socket socket_;

	boost::asio::io_service io_service_;
};
#endif
