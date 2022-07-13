#include <iostream>
#include <sstream>
#include <stdio.h>

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cerr << "Please input params." << std::endl;
		return 1;
	}

	std::string cmd = "cat " + std::string(argv[1]);
	std::cout << cmd << std::endl;
	std::stringstream stream;

	FILE* f = popen(cmd.c_str(), "r");
	char buffer[10];
	size_t len = 0;
	do {
		len = fread(buffer, 1, 10, f);
		for (int i = 0; i < len; i++) {
			stream << buffer[i];
		}
	} while (len == 10);

	if (ferror(f)) {
		fclose(f);
	}
	pclose(f);

	std::cout << stream.str() << std::endl;
}
