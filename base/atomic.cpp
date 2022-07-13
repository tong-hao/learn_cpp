#include <atomic>
#include <iostream>

int main(int argc, char const *argv[]) {
	std::atomic<bool> is_timer_event_{true};

	bool expected = false;
	bool r =
	    std::atomic_compare_exchange_weak(&is_timer_event_, &expected, true);
	std::cout << r;
	return 0;
}
