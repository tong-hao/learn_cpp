#include <string>
#include <vector>

class C {
public:
	C(std::string& s) {
	}
};

int main(int argc, char const* argv[]) {
	// range-based for statement
	for (int i : {1, 2, 3}) {
	}

	std::vector<int> vct{1, 2, 3};
	for (auto& e : vct) {
	}

	// 注意
	std::vector<std::string> vct2;
	for (C c : vct2)  // string不一定能转成C
	{
	}

	return 0;
}
