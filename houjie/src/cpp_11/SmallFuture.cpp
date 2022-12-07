#include <list>
#include <vector>

int main(int argc, char const *argv[]) {
	// 1. Space in Template
	std::list<std::vector<int>> list;

	// 2. nullptr instead of 0 or NULL
	//<cstddef>
	// std::nullptr;

	// 3. auto type
	auto i = 42;
	auto f = [](int x) -> bool {};
	return 0;
}
