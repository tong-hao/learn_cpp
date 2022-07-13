#include <iterator>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
void print(T t) {
	for(auto& e : t) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

int main1() {
	vector<string> coll;
	copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(coll));
	sort(coll.begin(), coll.end());
	unique_copy(coll.cbegin(), coll.cend(), ostream_iterator<string>(cout, "\n"));
	return 0;
}

int main2() {
	set<int> list1;
	inserter(list1, list1.begin()) = 1;
	inserter(list1, list1.begin()) = 2;
	print(list1);
	inserter(list1, list1.begin()) = 3;
	print(list1);


	list<int> list2;
	//copy(list1.begin(), list1.end(), inserter(list2, list2.begin()));
	for(auto iter = list1.begin(); iter != list1.end(); iter++){
		inserter(list2, list2.begin()) = *iter;
	}

	print(list2);

	return 0;
}
 
int main(){
	std::vector<int> v{1,2,3,4};
	auto iter1 = find(v.begin(), v.end(), 2);
	auto iter2 = v.rbegin();
	
	vector<int>::const_reverse_iterator iter3(iter1);
	vector<int>::const_reverse_iterator iter4(iter2);
	auto print = [](auto item){
		std::cout << item << std::endl;
	};

	for_each(iter3, iter2, print);

	return 0;
}

