#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <future>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

bool CheckPortTCP(const std::string &ip, int port) {
	addrinfo *result;
	addrinfo hints{};
	hints.ai_family = AF_UNSPEC;  // either IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;
	char addressString[INET6_ADDRSTRLEN];
	const char *retval = nullptr;
	if (0 != getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hints,
	                     &result)) {
		return "";
	}
	for (addrinfo *addr = result; addr != nullptr; addr = addr->ai_next) {
		std::cout << "addr->ai_addr->sa_data: " << addr->ai_addr->sa_data
		          << std::endl;
		int handle =
		    socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
		if (handle == -1) {
			continue;
		}
		if (connect(handle, addr->ai_addr, addr->ai_addrlen) != -1) {
			switch (addr->ai_family) {
				case AF_INET:
					retval = inet_ntop(
					    addr->ai_family,
					    &(reinterpret_cast<sockaddr_in *>(addr->ai_addr)
					          ->sin_addr),
					    addressString, INET6_ADDRSTRLEN);
					break;
				case AF_INET6:
					retval = inet_ntop(
					    addr->ai_family,
					    &(reinterpret_cast<sockaddr_in6 *>(addr->ai_addr)
					          ->sin6_addr),
					    addressString, INET6_ADDRSTRLEN);
					break;
				default:
					// unknown family
					retval = nullptr;
			}
			close(handle);
			break;
		}
	}
	freeaddrinfo(result);
	return retval != nullptr;
}

int main(int count, char **param) {
	std::string ip = "10.1.1.1";
	int port = 22;
	if (count == 3) {
		ip = std::string(param[1]);
		port = std::stoi(std::string(param[2]));
	}

	std::cout << "ip:" << ip << ", port:" << port << std::endl;
	if (CheckPortTCP(ip.c_str(), port)) {
		std::cout << "server is listening" << std::endl;
	} else {
		std::cout << "server closing" << std::endl;
	}
}