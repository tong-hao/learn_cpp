#include <boost/fiber/all.hpp>
#include <iostream>

using namespace boost::fibers;
using namespace boost;

void fiber1(fiber::id id2) {
	std::cout << "fiber 1 started" << std::endl;
	std::cout << "fiber 1 switching to fiber 2" << std::endl;
	this_fiber::yield();
	std::cout << "fiber 1 switching back" << std::endl;
	std::cout << "fiber 1 finished" << std::endl;
}

void fiber2() {
	std::cout << "fiber 2 started" << std::endl;
	std::cout << "fiber 2 switching back to fiber 1" << std::endl;
	this_fiber::yield();
	std::cout << "fiber 2 finished" << std::endl;
}

int main() {
	fiber f1(fiber1, this_fiber::get_id());
	fiber f2(fiber2);
	f1.join();
	f2.join();
	return 0;
}
