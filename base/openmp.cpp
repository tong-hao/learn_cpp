#include <omp.h>
#include <iostream>

int main(int argc, char const *argv[]) {
#pragma omp parallel for
	for (size_t i = 0; i < 10; i++) {
		int thread_id = omp_get_thread_num();
		std::cout << thread_id << std::endl;
	}

	return 0;
}
