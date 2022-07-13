#include <fmt/format.h>
#include <cstdlib>
#include <iostream>

const int kVertexSize = 15000;

int random(int min, int max) {
	return rand() % (max - min + 1) + min;
}

int main(int argc, char const *argv[]) {
	// generate vertices
	for (int i = 0; i < kVertexSize; i++) {
		auto nql =
		    fmt::format("INSERT VERTEX t1(name) VALUES {}:(\"{}\");", i, i);
		std::cout << nql << std::endl;
	}

	// generate edges
	for (int i = 0; i < kVertexSize - 1; i++) {
		auto nql = fmt::format("INSERT EDGE e1 (weight) VALUES {}->{}:(0.1);",
		                       i, i + 1);
		std::cout << nql << std::endl;
	}

	// rand edges
	for (int i = 0; i < kVertexSize * 0.2; i++) {
		auto src = random(0, kVertexSize);
		auto dst = random(0, kVertexSize);
		auto nql = fmt::format("INSERT EDGE e1 (weight) VALUES {}->{}:(0.1);",
		                       src, dst);
		std::cout << nql << std::endl;
	}

	return 0;
}

// link: -lfmt