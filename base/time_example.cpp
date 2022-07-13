#include <ctime>
#include <iostream>
#include <unistd.h>

int main() {
	time_t t1 = time(0);
	// usleep(1000000);  // 1s = 1000ms = 1000000us
	sleep(3);
	time_t t2 = time(0);

	std::cout << t1 << std::endl;
	std::cout << t2 << std::endl;

	tm* tm1 = localtime(&t1);
	std::cout << "start: " << tm1->tm_hour << ":" << tm1->tm_min << ":"
	          << tm1->tm_sec << std::endl;
	tm* tm2 = localtime(&t2);
	std::cout << "end: " << tm2->tm_hour << ":" << tm2->tm_min << ":"
	          << tm2->tm_sec << std::endl;

	return 0;
}