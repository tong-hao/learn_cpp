#include <numa.h>
#include <iostream>

int main(int argc, char const *argv[]) {
	int sockets_ = numa_num_configured_nodes();
	int threads_ = numa_num_configured_cpus();

	std::cout << "socket num:" << sockets_ << ", thread num:" << sockets_
	          << std::endl;

	return 0;
}
