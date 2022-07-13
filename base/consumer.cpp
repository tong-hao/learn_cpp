#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>

using namespace std::chrono_literals;
using namespace std;

std::queue<size_t> q;
bool finished{false};
std::mutex mut;
std::condition_variable cv;

void producer(size_t num) {
	for (auto i = 0; i < num; i++) {
		while (q.size() > 100) {
			std::this_thread::sleep_for(1ms);
		}

		{
			std::lock_guard<std::mutex> lk{mut};
			std::cout << "producer-begin:" << std::endl;
			q.push(i);
			std::cout << "producer:" << i << std::endl;
			std::cout << "producer-end:" << std::endl;
		}
		cv.notify_all();
	}

	{
		lock_guard<mutex> lk{mut};
		finished = true;
	}
	cv.notify_all();
}

void consumer() {
	while (q.empty() || !finished) {
		while (q.empty()) {
			std::this_thread::sleep_for(1ms);
		}

		{
			std::cout << "consumer-begin:" << std::endl;
			std::unique_lock<std::mutex> l{mut};
			cv.wait(l, [] { return !q.empty() || finished; });  //

			while (!q.empty()) {
				std::cout << "got: " << q.front() << std::endl;
				q.pop();
			}
			std::cout << "consumer-end:" << std::endl;
		}

		if (finished && q.empty()) {
			break;
		}
	}
}

int main(int argc, char const *argv[]) {
	std::thread t2{consumer};
	std::thread t1{producer, 3000};

	t1.join();
	t2.join();

	std::cout << "finished!" << std::endl;

	return 0;
}