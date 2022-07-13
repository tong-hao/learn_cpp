#include <folly/ThreadLocal.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>


int main(int argc, char const *argv[])
{

	// threadlocal
	class NewTag1;
	folly::ThreadLocalPtr<int, NewTag1> my_int;

	// thread1
	my_int.reset(new int(1));
	std::cout << "thread1: reset to 1" << std::endl;

	// thread2
	std::thread th2([&my_int]() {
		my_int.reset(new int(2));
		std::cout << "thread2: reset to 2" << std::endl;
		std::cout <<  "thread2: read" << *(my_int.get()) << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	});
	std::cout <<  "thread1: read" << *(my_int.get()) << std::endl;


	// read all threads
	for (auto& e : my_int.accessAllThreads()) {
		std::cout << e << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));


	return 0;
}