#include <deque>
#include <stack>
#include <queue>
#include <iostream>


template<typename Container>
void print(Container c) {
	for (auto iter = c.begin(); iter != c.end(); iter++) {
		std::cout << *iter << " ";
	}

	std::cout << std::endl;
}


int main(int argc, char const *argv[]) {
	// stack
	std::stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);
	std::cout << stack.top() << std::endl;
	stack.pop();
	std::cout << stack.top() << std::endl;
	stack.pop();
	std::cout << stack.top() << std::endl;
	stack.pop();

	// deque
	std::deque<int> deque;
	deque.push_back(11);
	deque.push_back(12);
	deque.push_back(13);
	print(deque);
	deque.pop_front();
	print(deque);
	deque.pop_back();
	print(deque);

	//
	{
		std::priority_queue<int> q;
		q.push(26);
		q.push(27);
		q.push(23);
		std::cout << q.top() << std::endl; // 27
		q.pop();
		std::cout << q.top() << std::endl; // 26
		q.pop();
		std::cout << q.top() << std::endl; // 23
		q.pop();
		
	}

	return 0;
}