#include <algorithm>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Edge {
public:
	Edge() {
	}
	Edge(int a, std::unique_ptr<std::string> b) : i(a), s(std::move(b)) {
	}

	Edge(const Edge&) = default;
	Edge(Edge&& other) : i(other.i), s(std::move(other.s)) {
	}
	~Edge() {
	}

	int i;
	std::unique_ptr<std::string> s;
};

int main() {
	{
		auto t1 = clock();
		Edge e;
		for (size_t i = 0; i < 1000000; i++) {
			e = std::move(Edge{1, std::make_unique<std::string>("Hello")});
		}
		auto t2 = clock();

		std::cout << (t2 - t1) << "ms" << std::endl;
	}

	{
		auto t3 = clock();
		Edge e;
		for (size_t i = 0; i < 1000000; i++) {
			e = Edge{1, std::make_unique<std::string>("Hello")};
		}
		auto t4 = clock();

		std::cout << (t4 - t3) << "ms" << std::endl;
	}

	return 0;
}
