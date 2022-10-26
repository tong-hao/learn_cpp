#include <dlfcn.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
	std::string path = "../lib/libsum.so";

	void* handler = dlopen(path.c_str(), RTLD_NOW);
	if (!handler) {
		std::cerr << dlerror() << std::endl;
	}

	int (*f_sum)(int, int) = (int (*)(int, int))dlsym(handler, "sum");
	if (!f_sum) {
		std::cerr << dlerror() << std::endl;
	}
	auto result = f_sum(101, 235);
	std::cout << "result:" << result << std::endl;

	dlclose(handler);

	return 0;
}
