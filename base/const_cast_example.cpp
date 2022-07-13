#include <iostream>
#include <memory>
#include <vector>

class DataList {
public:
	DataList() : vct(std::make_unique<std::vector<int>>()) {
	}

	void Add(int i) {
		vct->push_back(i);
	}

	std::unique_ptr<const std::vector<int>> GetData() {
		return std::make_unique<const std::vector<int>>(*vct);
	}

private:
	std::unique_ptr<std::vector<int>> vct;
};

int main(int argc, char const *argv[]) {
	DataList list;
	list.Add(1);
	list.Add(2);

	auto datas = list.GetData();
	auto iter = datas->begin();

	while (iter != datas->end()) {
		std::cout << *iter << std::endl;
		iter++;
	}

	list.Add(3);
	auto datas2 = list.GetData();
	for (auto d : *datas2) {
		std::cout << d << std::endl;
	}

	return 0;
}
