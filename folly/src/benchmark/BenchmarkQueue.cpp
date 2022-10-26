#include <folly/Benchmark.h>
#include <folly/container/Foreach.h>
#include <iostream>
#include <queue>

BENCHMARK(std_queue_10000, n) {
	folly::BenchmarkSuspender s;
	int existedNum = 10000;
	std::queue<int> q;
	for (int i = 0; i < existedNum; i++) {
		q.emplace(i);
	}
	CHECK(q.size() == existedNum);
	s.dismiss();

	FOR_EACH_RANGE(i, 0, n) {
		if (q.size() >= existedNum) {
			auto old = q.back();
			q.pop();

			q.emplace(i);
		}
	}
}

BENCHMARK_RELATIVE(std_queue_1000, n) {
	folly::BenchmarkSuspender s;
	int existedNum = 1000;
	std::queue<int> q;
	for (int i = 0; i < existedNum; i++) {
		q.emplace(i);
	}
	CHECK(q.size() == existedNum);
	s.dismiss();

	FOR_EACH_RANGE(i, 0, n) {
		if (q.size() >= existedNum) {
			auto old = q.back();
			q.pop();

			q.emplace(i);
		}
	}
}

BENCHMARK_RELATIVE(std_queue_50000, n) {
	folly::BenchmarkSuspender s;
	int existedNum = 50000;
	std::queue<int> q;
	for (int i = 0; i < existedNum; i++) {
		q.emplace(i);
	}
	CHECK(q.size() == existedNum);
	s.dismiss();

	FOR_EACH_RANGE(i, 0, n) {
		if (q.size() >= existedNum) {
			auto old = q.back();
			q.pop();

			q.emplace(i);
		}
	}
}

BENCHMARK_RELATIVE(std_queue_100000, n) {
	folly::BenchmarkSuspender s;
	int existedNum = 100000;
	std::queue<int> q;
	for (int i = 0; i < existedNum; i++) {
		q.emplace(i);
	}
	CHECK(q.size() == existedNum);
	s.dismiss();

	FOR_EACH_RANGE(i, 0, n) {
		if (q.size() >= existedNum) {
			auto old = q.back();
			q.pop();

			q.emplace(i);
		}
	}
}

BENCHMARK_RELATIVE(std_deque_10000, n) {
	folly::BenchmarkSuspender s;
	int existedNum = 10000;
	std::deque<int> q;
	for (int i = 0; i < existedNum; i++) {
		q.emplace_back(i);
	}
	CHECK(q.size() == existedNum);
	s.dismiss();

	FOR_EACH_RANGE(i, 0, n) {
		if (q.size() >= existedNum) {
			auto old = q.back();
			q.pop_front();

			q.emplace_back(i);
		}
	}
}

int main(int argc, char const *argv[]) {
	folly::runBenchmarks();
	return 0;
}
