#include <deque>
#include <iostream>
#include <algorithm>
#include <assert.h>
// 双向队列，
// 支持头和尾插入，便利速度快
// 缺点：扩容比较麻烦


template<typename Container>
void print(Container c){
	for(auto iter = c.begin(); iter != c.end(); iter++) {
		std::cout << *iter << " ";
	}

	std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
	std::deque<int> deque;
	for(int i = 0; i < 10; i++) {
		if(i % 3 == 0) {
			deque.push_back(i);
		} else {
			deque.push_front(i);
		}
	}
	print(deque);
	
}