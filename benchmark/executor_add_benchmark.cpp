#include <folly/SharedMutex.h>
#include <folly/Synchronized.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <atomic>
#include <memory>
#include <queue>

template <typename T>
class IngestQueue {
public:
	IngestQueue(size_t max_num = 10000);

	template <typename T2>
	void Push(T2&& d);

	T Pop(bool auto_incr_consumer_num = true);

	bool IsFull();
	bool Empty();
	size_t Size();

	void SetProducerFinished();
	bool IsProducerFinished();
	bool IsConsumerFinished();

	void IncrConsumerSuccessNum();
	void IncrConsumerFailNum();
	void IncrProducerFailNum();

	long ConsumerSuccessNum();
	long ConsumerFailNum();
	long ProducerSuccessNum();
	long ProducerFailNum();

private:
	// call in method of `Push`
	void IncrProducerSuccessNum();

private:
	size_t max_num_;
	std::atomic_long producer_success_num_{0};
	std::atomic_long producer_fail_num_{0};
	std::atomic_long consumer_success_num_{0};
	std::atomic_long consumer_fail_num_{0};

	std::atomic_bool producer_finished_{false};
	folly::Synchronized<std::queue<T>, std::mutex> queue_;
	std::condition_variable cv_produce;
	std::condition_variable cv_consume;
};

template <typename T>
IngestQueue<T>::IngestQueue(size_t max_num) : max_num_(max_num) {
}

template <typename T>
template <typename T2>
void IngestQueue<T>::Push(T2&& data) {
	auto locked = queue_.lock();
	cv_produce.wait(locked.getUniqueLock(),
	                [&locked, this]() { return locked->size() < max_num_; });
	locked->push(std::forward<T2>(data));
	IncrProducerSuccessNum();
	cv_consume.notify_one();
}

template <typename T>
T IngestQueue<T>::Pop(bool auto_incr_consumer_num) {
	auto locked = queue_.lock();
	cv_consume.wait(locked.getUniqueLock(),
	                [&locked]() { return !locked->empty(); });

	T data = std::move(locked->front());
	locked->pop();
	if (auto_incr_consumer_num) {
		IncrConsumerSuccessNum();
	}
	cv_produce.notify_one();
	return data;
}

template <typename T>
size_t IngestQueue<T>::Size() {
	return queue_.withLock([this](auto& Q) { return Q.size(); });
}

template <typename T>
bool IngestQueue<T>::IsFull() {
	return queue_.withLock([this](auto& Q) { return Q.size() >= max_num_; });
}

template <typename T>
bool IngestQueue<T>::Empty() {
	return queue_.withLock([this](auto& Q) { return Q.empty(); });
}

template <typename T>
void IngestQueue<T>::SetProducerFinished() {
	producer_finished_.store(true);
}
template <typename T>
bool IngestQueue<T>::IsProducerFinished() {
	return producer_finished_.load();
}
template <typename T>
bool IngestQueue<T>::IsConsumerFinished() {
	return producer_finished_.load() &&
	       producer_success_num_.load() ==
	           (consumer_success_num_.load() + consumer_fail_num_.load());
}
template <typename T>
void IngestQueue<T>::IncrConsumerSuccessNum() {
	consumer_success_num_.fetch_add(1);
}
template <typename T>
void IngestQueue<T>::IncrConsumerFailNum() {
	consumer_fail_num_.fetch_add(1);
}
template <typename T>
void IngestQueue<T>::IncrProducerSuccessNum() {
	producer_success_num_.fetch_add(1);
}
template <typename T>
void IngestQueue<T>::IncrProducerFailNum() {
	producer_fail_num_.fetch_add(1);
}
template <typename T>
long IngestQueue<T>::ConsumerSuccessNum() {
	return consumer_success_num_.load();
}
template <typename T>
long IngestQueue<T>::ConsumerFailNum() {
	return consumer_fail_num_.load();
}
template <typename T>
long IngestQueue<T>::ProducerSuccessNum() {
	return producer_success_num_.load();
}
template <typename T>
long IngestQueue<T>::ProducerFailNum() {
	return producer_fail_num_.load();
}

//==========================================

#include <fmt/format.h>
#include <folly/Benchmark.h>
#include <folly/container/Foreach.h>
#include <folly/init/Init.h>
#include <folly/portability/GFlags.h>
#include <folly/stop_watch.h>
#include <memory>
#include <string>

class OneClass {
public:
	std::string s1;
	std::string s2;
	std::string s3;
	std::string s4;
	std::string s5;
	std::string s6;
};

void testPush() {
	size_t num = 8000000;
	IngestQueue<OneClass> q(num);

	folly::stop_watch<std::chrono::milliseconds> w;
	for (size_t i = 0; i < num; i++) {
		OneClass a;
		a.s1 = "abcdefghijklmnopqrszuvwxyz0123456789";
		a.s2 = "abcdefghijklmnopqrszuvwxyz0123456789";
		q.Push(std::move(a));
	}
	LOG(INFO) << fmt::format("testPush, used_time:{}ms", w.elapsed().count());
}
// used_time:7902ms
void testPop() {
	size_t num = 8000000;
	IngestQueue<OneClass> q(num);
	for (size_t i = 0; i < num; i++) {
		OneClass a;
		a.s1 = "abcdefghijklmnopqrszuvwxyz0123456789";
		q.Push(std::move(a));
	}
	folly::stop_watch<std::chrono::milliseconds> w;
	for (size_t i = 0; i < num; i++) {
		auto a = q.Pop();
	}
	LOG(INFO) << fmt::format("testPop, used_time:{}ms", w.elapsed().count());
}

// used_time:47040ms
void testPopThenAdd() {
	size_t num = 8000000;
	IngestQueue<OneClass> q(num);
	for (size_t i = 0; i < num; i++) {
		OneClass a;
		a.s1 = "abcdefghijklmnopqrszuvwxyz0123456789";
		a.s2 = "abcdefghijklmnopqrszuvwxyz0123456789";
		q.Push(std::move(a));
	}
	auto executors = std::make_shared<folly::CPUThreadPoolExecutor>(2);

	folly::stop_watch<std::chrono::milliseconds> w;
	for (size_t i = 0; i < num; i++) {
		auto a = q.Pop();
		executors->add([a = std::move(a)]() {});
	}
	LOG(INFO) << fmt::format("testPopThenAdd, used_time:{}ms",
	                         w.elapsed().count());
}

// testAdd, used_time:39895ms
void testAdd() {
	size_t num = 8000000;
	auto executors = std::make_shared<folly::CPUThreadPoolExecutor>(2);

	folly::stop_watch<std::chrono::milliseconds> w;
	for (size_t i = 0; i < num; i++) {
		OneClass a;
		a.s1 = "abcdefghijklmnopqrszuvwxyz0123456789";
		a.s2 = "abcdefghijklmnopqrszuvwxyz0123456789";
		executors->add([a = std::move(a)]() {});
	}
	LOG(INFO) << fmt::format("testAdd, used_time:{}ms", w.elapsed().count());
}

int main(int argc, char** argv) {
	FLAGS_logtostderr = 1;
	folly::init(&argc, &argv);

	// testPush();
	// testPop();
	// testAdd();
	testPopThenAdd();

	return 0;
}

/**

============================================================================
queue_benchmark.cpp                             relative  time/iter  iters/s
============================================================================
queue_push                                                 160.45ns    6.23M
queue_pop                                                  105.69ns    9.46M
queue_push_8000k                                              3.27s  305.68m
queue_pop_8000k                                               2.38s  419.78m
queue_push_8000k_object                                       8.01s  124.78m
queue_pop_8000k_object                                        1.89s  529.52m
queue_pop_8000k_object[增加：executors->add]                   51.53s   19.40m
============================================================================
 */

// link:-lfolly -lglog -lgflags -lpthread -ldl -ldouble-conversion
// link:-lfollybenchmark  -lboost_regex -liberty -lfmt