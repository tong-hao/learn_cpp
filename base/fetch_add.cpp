#include <iostream>

int main(int argc, char const *argv[]) {
	int num = 1;

	for (size_t i = 0; i < 5; i++) {
		int curr = __sync_fetch_and_add(&num, 10);
		std::cout << "current: " << curr << ", count:" << num << std::endl;
	}

	return 0;
}