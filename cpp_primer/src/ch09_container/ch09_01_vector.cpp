#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
// 可变长数组
// 优点：可变大小，随机访问
// 缺点：删除需要移动，


template<typename Container>
void print(Container c){
	for(auto iter = c.begin(); iter < c.end(); iter++) {
		std::cout << *iter << " ";
	}

	std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
	// add 
	std::vector<int> vct;
	vct.push_back(1);
	vct.push_back(3);
	vct.push_back(5);
	vct.push_back(3);
	print(vct);

	// find & delete
	auto found = std::find(vct.begin(), vct.end(), 3);
	if(found != vct.end()) {
		vct.erase(found);
	}
	print(vct);

	// update
	auto found2 = std::find(vct.begin(), vct.end(), 3);
	if(found2 != vct.end()) {
		int* p = &(*found2);
		*p = *found2 + 100;
	}
	print(vct);

	// other
	assert(!vct.empty());
	assert(vct.size() > 0);

	return 0;
}