#include <iostream>
#include <memory>
#include <typeinfo>

class Worker : public std::enable_shared_from_this<Worker> {
public:
	virtual void Run() {
		auto p = this->shared_from_this();
		// std::cout << (void *)(p.get());
		idx++;
		p->idx++;

		std::cout << p->idx << std::endl;
	}

private:
	int idx = 1;
};

class SubWorker1 : public Worker {};
class SubWorker2 : public Worker {};

int main(int argc, char const *argv[]) {
	auto w1 = std::make_shared<SubWorker1>();
	w1->Run();

	auto w2 = std::make_shared<SubWorker2>();
	w2->Run();

	return 0;
}
