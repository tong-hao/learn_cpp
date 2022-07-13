#include <list>
#include <iostream>
#include <algorithm>
#include <assert.h>
// 双向链表，
// 优点：双向访问，插入删除速度快
// 缺点：遍历速度慢


template<typename Container>
void print(Container c){
	for(auto iter = c.begin(); iter != c.end(); iter++) {
		std::cout << *iter << " ";
	}

	std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
	std::list<int> list;
	for(int i =0; i < 10; i++) {
		if(i % 2 == 0) list.push_back(i);
		else list.push_front(i);
	}
	print(list);
}