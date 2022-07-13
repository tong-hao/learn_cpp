#include <functional>
#include <iostream>
#include <math.h>
using namespace std;

int main() {
	int8_t bit_move = 32 - log2(1024);

	for (uint32_t i = 0; i < 1024; i++) {
		cout << (i << bit_move) << std::endl;
	}

	return 0;
}