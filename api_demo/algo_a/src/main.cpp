#include <iostream>

#include <vector>
#include "graph.h"

void print(const std::vector<int>& nbrs) {
	std::string str;
	for (size_t i = 0; i < nbrs.size(); i++) {
		str.append(std::to_string(nbrs[i]));
		if (i != nbrs.size() - 1) {
			str.append(",");
		}
	}
	std::cout << str << std::endl;
}

int main(int argc, char** argv) {
	for (int i = 0; i < 10; i++) {
		print(getNbrs(i));
	}

	return 0;
}
