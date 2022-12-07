#include <assert.h>
#include <algorithm>
#include <iostream>
#include <vector>

template <typename Container>
void print(Container c) {
	for (auto iter = c.begin(); iter < c.end(); iter++) {
		std::cout << *iter << " ";
	}

	std::cout << std::endl;
}

int main(int argc, char const* argv[]) {
	// https://en.cppreference.com/w/cpp/container/vector
	// 可变长数组
	// 优点：可变大小，随机访问
	// 缺点：删除需要移动，

	// construct
	{
		std::vector<std::string> vct1{"str1", "str2"};
		std::vector<std::string> vct2{vct1.begin(), vct1.end()};
		std::vector<std::string> vct3{vct1};
		std::vector<std::string> vct4{3};
	}
	// Element access
	{
		std::vector<int> vct{1, 2, 3};
		vct.at(0) = 100;
		vct[1] = 101;
		vct.back() == 3;
		vct.front() == 100;
		int* p = vct.data();
	}
	// iterators
	{
		std::vector<int> vct{1, 2, 3};
		vct.begin();
		vct.end();
		vct.cbegin();
		vct.cend();
		vct.crbegin();
		vct.crend();
	}
	// capacity
	{
		std::vector<int> vct{1, 2, 3};
		vct.empty();
		vct.size();
		vct.max_size();  // 最多元素可能数量
		vct.capacity();
		vct.reserve(10);
		vct.shrink_to_fit();
	}
	// modifiers
	{
		std::vector<int> vct{1, 2, 3};
		vct.clear();
		vct.insert(vct.begin(), 100);
		vct.emplace(vct.begin(), 101);
		vct.emplace_back(102);
		vct.push_back(103);
		vct.emplace(vct.begin(), 104);
		vct.erase(vct.begin(), vct.end());
		vct.pop_back();
		vct.resize(3);

		std::vector<int> vct2;
		vct.swap(vct2);
	}

	// find & delete
	{
		std::vector<int> vct{1, 2, 3};
		auto found = std::find(vct.begin(), vct.end(), 3);
		if (found != vct.end()) {
			vct.erase(found);
		}
		print(vct);
	}

	// update
	{
		std::vector<int> vct{1, 2, 3};
		auto found2 = std::find(vct.begin(), vct.end(), 3);
		if (found2 != vct.end()) {
			int* p = &(*found2);
			*p = *found2 + 100;
		}
		print(vct);
	}

	return 0;
}
