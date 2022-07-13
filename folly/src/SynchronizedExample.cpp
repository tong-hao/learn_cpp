#include <folly/Synchronized.h>
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main(int argc, char const* argv[]) {
	folly::Synchronized<std::map<int, std::string>> map;

	// write lock
	auto m = map.wlock();
	m->emplace(std::make_pair(1, "a"));
	m->emplace(std::make_pair(2, "b"));
	m.unlock();

	// read lock
	auto m2 = map.rlock();
	for (auto& e : *m2) {
		std::cout << e.first << "," << e.second << std::endl;
	}
	m2.unlock();

	return 0;
}

// link:-lfolly -lgflags -lglog -ldl -ldouble-conversion