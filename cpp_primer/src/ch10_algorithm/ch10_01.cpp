#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>      // std::accumulate

int main(int argc, char const *argv[])
{
	
	std::vector<int> vct{1,3,5,7,8,9, 7, 1, 7, 6};
	
	// find
	auto found = std::find(vct.cbegin(), vct.cend(), 7);
	if(found != vct.end()) {
		std::cout << "found it." << std::endl;
	}

	// count
	auto num = std::count(vct.cbegin(), vct.cend(), 7); // 别写成了cout了哦～
	std::cout << "num of 7 : " << num << std::endl;

	// accumulate
	int sum = std::accumulate(vct.cbegin(), vct.cend(), 0);
	std::cout << "sum : " << sum << std::endl;

	// equal
	bool eq = std::equal(vct.cbegin(), vct.cend(), vct.cbegin(), vct.cend());
	std::cout << "eq:" << eq << std::endl;

	// fill
	std::fill(vct.begin(), vct.end(), 1);
	std::fill_n(vct.begin(), 3, 1);

	// back_inserter
	auto iter = std::back_inserter(vct);
	*iter = 4;
	++iter;
	*iter = 5;

	// for each
	std::for_each(vct.cbegin(), vct.cend(), [](int i){ std::cout << i << " ";});
	std::cout << std::endl;

	// copy
	std::vector<int> vct2(vct.size());
	std::copy(vct.begin(), vct.end(), vct2.begin());

	// replace
	std::replace(vct.begin(), vct.end(), 7, 0);

	// sort
	std::sort(vct.begin(), vct.end());

	// unique
	auto end = std::unique(vct.begin(), vct.end());
	vct.erase(end, vct.end());
	std::for_each(vct.cbegin(), vct.cend(), [](int i){ std::cout << i << " ";});





	return 0;
}