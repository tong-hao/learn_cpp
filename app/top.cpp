#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> data;

void printTopN(double n) {
	double percent = n / 100.0;
	std::cout << "top" << n << ":" << data[percent * data.size()] << std::endl;
}

int main(int argc, char const *argv[]) {
	std::string file = "./test2.cpp";
	std::string filter = "";
	if (argc == 3) {
		file = argv[1];
		filter = argv[2];
	} else {
		std::cerr << "Must input two paraments. " << std::endl;
		return 1;
	}

	std::cout << "file:" << file << std::endl;
	std::cout << "filter:" << filter << std::endl;

	std::fstream fs(file);
	// std::stringstream fs("a 1 23345ms\nb 10ms");

	std::smatch m;
	std::regex e("[0-9]{1,9}ms");

	std::string line;
	while (std::getline(fs, line, '\n')) {
		if (line.find(filter) == std::string::npos) {
			continue;
		}
		if (std::regex_search(line, m, e)) {
			data.push_back(std::stoi(m[0]));
		}
	}
	std::sort(data.begin(), data.end());

	printTopN(10);
	printTopN(50);
	printTopN(80);
	printTopN(90);
	printTopN(99);
	printTopN(99.9);

	return 0;
}