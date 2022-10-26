#include <iostream>

#include "hello/hello.h"

int main(int argc, char** argv) {
	for (int i = 0; i < 10; i++) {
		std::cout << next_id() << std::endl;
	}

	return 0;
}
