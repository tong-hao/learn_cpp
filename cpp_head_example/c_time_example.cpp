#include <ctime>
#include <iostream>

int main() {
	// clock_t
	clock_t c = clock_t();
	std::cout << c << std::endl;

	// time_t
	std::time_t now = std::time(nullptr);
	std::cout << now << std::endl;  // 1659928756

	char* str_now = std::ctime(&now);
	std::cout << str_now << std::endl;  // Mon Aug  8 11:15:09 2022

	std::tm* my_tm = std::gmtime(&now);
	std::cout << my_tm->tm_year + 1900 << std::endl;
	std::cout << my_tm->tm_mon + 1 << std::endl;
	std::cout << my_tm->tm_mday << std::endl;

	my_tm = std::localtime(&now);

	double diff = std::difftime(now, time(nullptr));
	std::cout << diff << std::endl;

	// tm
	time_t t2 = std::mktime(my_tm);
	std::cout << t2 << std::endl;  // 1659928756

	char* str_tm = std::asctime(my_tm);
	std::cout << str_tm << std::endl;
}
