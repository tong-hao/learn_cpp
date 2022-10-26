#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

bool listDeviceAndIPv4s(
    std::unordered_map<std::string, std::string>& dev2ipv4s) {
	struct ifaddrs* iflist;

	if (::getifaddrs(&iflist) != 0) {
		// return Status::Error("%s", ::strerror(errno));
		return false;
	}
	for (auto* ifa = iflist; ifa != nullptr; ifa = ifa->ifa_next) {
		// Skip non-IPv4 devices
		if (ifa->ifa_addr->sa_family != AF_INET) {
			continue;
		}
		auto* addr = reinterpret_cast<struct sockaddr_in*>(ifa->ifa_addr);
		// inet_ntoa is thread safe but not re-entrant,
		// we could use inet_ntop instead when we need support for IPv6
		dev2ipv4s[ifa->ifa_name] = ::inet_ntoa(addr->sin_addr);
	}
	::freeifaddrs(iflist);
	if (dev2ipv4s.empty()) {
		// return Status::Error("No IPv4 devices found");
		return false;
	}
	return true;
}

bool GetIPv4MacAddr(std::string& mac_addrs) {
	std::unordered_map<std::string, std::string> dev2ipv4s;
	if (!listDeviceAndIPv4s(dev2ipv4s)) {
		return false;
	}

	std::vector<std::string> macList;
	// Iterate divices and retrive mac addresses
	for (auto& item : dev2ipv4s) {
		auto if_nameStr = std::string(item.first);

		// Skip virtual network adapter
		if (if_nameStr.find("docker") != std::string::npos ||
		    if_nameStr.rfind("veth", 0) == 0) {
			continue;
		}

		struct ifreq ifr;
		size_t if_name_len = strlen(if_nameStr.c_str());
		if (if_name_len < sizeof(ifr.ifr_name)) {
			memcpy(ifr.ifr_name, if_nameStr.c_str(), if_name_len);
			ifr.ifr_name[if_name_len] = 0;
		} else {
			// Interface name is too long, ignore
			std::cout << "The interface name is too long";
			continue;
		}

		int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
		// Failed to create socket using protocal
		if (fd == -1) {
			std::cout << "Failed to create socket using protocal, error: "
			          << strerror(errno);
			continue;
		}

		// Failed to collect hardware info of the device, ignore
		if (ioctl(fd, SIOCGIFHWADDR, &ifr) == -1) {
			std::cout << "Failed to collect hardware info of the device";
			close(fd);
			continue;
		}
		close(fd);

		// The interface is not an Ethernet interface, ignore
		if (ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER) {
			std::cout << "The interface is not an Ethernet interface";
			continue;
		}

		const unsigned char* mac =
		    reinterpret_cast<unsigned char*>(ifr.ifr_hwaddr.sa_data);

		char buff[20];
		snprintf(buff, sizeof(buff), "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],
		         mac[1], mac[2], mac[3], mac[4], mac[5]);
		std::string buffAsStdStr = buff;

		// Skip virtual network adapter
		if (buffAsStdStr == "00:00:00:00:00:00") {
			continue;
		}
		// append all mac address
		macList.emplace_back(buffAsStdStr);
	}
	// Use ',' as the delimeter to separate multiple mac addresses
	// auto code = folly::join(",", macList);
	for (auto mac : macList) {
		mac_addrs.append(mac).append(",");
	}
	if (mac_addrs.size() > 0) {
		mac_addrs = mac_addrs.substr(0, mac_addrs.size() - 1);
	}

	return true;
}

int main(int argc, char const* argv[]) {
	std::string mac;
	bool result = GetIPv4MacAddr(mac);
	if (result) {
		std::cout << "\nmac:" << mac << std::endl;
	}

	return 0;
}
// link:-g -Wall -std=c++11
