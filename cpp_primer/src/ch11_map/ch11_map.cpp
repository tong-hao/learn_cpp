#include <map>
#include <set>
#include <iostream>
#include <unordered_map>

template<typename SET>
void printSet(SET set){
	for(auto iter = set.cbegin(); iter != set.cend(); iter++){
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
}

template<typename MAP>
void printMap(MAP map){
	for(auto iter = map.cbegin(); iter != map.cend(); iter++){
		std::cout << iter->first << "," << iter->second << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
	// set
	std::set<int> set1{2,1,5};
	set1.emplace(4);
	printSet(set1);

	// map
	std::map<int,double> map1{};
	map1.emplace(1, 1.0); 
	printMap(map1);

	// multimap
	std::multimap<int,double> map2{};

	// unordered_map
	std::unordered_map<int,double> map3{};

	
	return 0;
}