#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

double mem_bootup = 0.0;

void resetMemBase(std::string mem) {
	// std::string mem;
	// std::getline(std::cin, mem);
	double mem_d = std::stod(mem);
	if (mem[mem.length() - 1] == 'M') {
		mem_bootup = mem_d / 1024.0;

	} else if (mem[mem.length() - 1] == 'G') {
		mem_bootup = mem_d;
	}
	std::cout << "mem_bootup: " << mem_bootup << "G" << std::endl;
}

void bootup() {
	std::string line;
	int cpu_left_min = 100;
	double mem_max = 0;
	int network_recv_max = 0;
	int network_send_max = 0;
	int used_time = 0;

	std::string output;
	auto reset = [&]() {
		cpu_left_min = 100;
		mem_max = 0;
		network_recv_max = 0;
		network_send_max = 0;
		used_time = 0;
	};

	while (std::getline(std::cin, line)) {
		output.append(line).append("\n");
		if (line.empty() || line[0] == '#') {
			continue;
		} else if (line[0] == '/' && line[1] == '/' && line[2] == 'c') {
			resetMemBase(line.substr(4, line.size()));
			continue;
		} else if (line[0] == '/' && line[1] == '/') {
			// 输出统计结果并重置数据
			output.append("内存: ")
			    .append(std::to_string(mem_max - mem_bootup))
			    .append("\n");
			output.append("cpu: ")
			    .append(std::to_string(100 - cpu_left_min))
			    .append("\n");
			output.append("网络: ")
			    .append(std::to_string(network_recv_max))
			    .append("M ")
			    .append(std::to_string(network_send_max))
			    .append("M ")
			    .append("\n");
			output.append("用时: ")
			    .append(std::to_string(used_time))
			    .append("\n");

			reset();
			continue;
		} else if (line == "print") {
			std::cout << "------------------\n" << output;
			reset();
			output.clear();
			continue;
		} else if (line == "q" || line == "quite") {
			break;
		}

		std::string cpu_left = line.substr(23, 3);
		cpu_left_min = std::min(cpu_left_min, std::stoi(cpu_left));

		std::string mem = line.substr(39, 5);
		double mem_d = std::stod(mem);
		if (mem[4] == 'M') {
			mem_d = mem_d / 1024.0;
			mem_max = std::max(mem_max, mem_d);
		} else if (mem[4] == 'G') {
			mem_max = std::max(mem_max, mem_d);
		}

		std::string network_recv = line.substr(63, 5);
		std::string network_send = line.substr(69, 5);
		auto network_recv_i = std::stoi(network_recv);
		auto network_send_i = std::stoi(network_send);
		if (network_recv[4] == 'B') {
			network_recv_i = network_recv_i / 1024 / 1024;
		} else if (network_recv[4] == 'k') {
			network_recv_i = network_recv_i / 1024;
		} else if (network_recv[4] == 'M') {
		} else {
			network_recv_i = 0;
		}

		if (network_send[4] == 'B') {
			network_send_i = network_send_i / 1024 / 1024;
		} else if (network_send[4] == 'k') {
			network_send_i = network_send_i / 1024;
		} else if (network_send[4] == 'M') {
		} else {
			network_send_i = 0;
		}

		network_recv_max = std::max(network_recv_max, network_recv_i);
		network_send_max = std::max(network_send_max, network_send_i);

		used_time++;
	}
}

int main() {
	// resetMemBase();
	bootup();
	return 0;
}

// link:-std=c++11
