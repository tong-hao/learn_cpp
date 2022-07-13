#include <arpa/inet.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

bool CheckPortTCP(const char *ip_addr, int port) {
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip_addr);
	int ns = (int)socket(AF_INET, SOCK_STREAM, 0);

	auto u_alarm_handler = [](int) {};
	sigset(SIGALRM, u_alarm_handler);
	alarm(1);
	int result = connect(ns, (struct sockaddr *)&addr, sizeof(addr));
	alarm(0);
	sigrelse(SIGALRM);

	std::cout << result << std::endl;
	if (result != -1) {
		close(ns);
		return true;
	} else {
		return false;
	}
}

int main(int count, char **param) {
	std::string ip = "172.23.236.1";
	ip = "127.23.236.1";

	int port = 221;
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